import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get user's cash
    user_data = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]
    cash = user_data["cash"]
    
    # Get user's holdings
    holdings = db.execute("""
        SELECT symbol, shares FROM holdings 
        WHERE user_id = ? AND shares > 0
    """, session["user_id"])
    
    # Calculate current values
    portfolio = []
    total_stock_value = 0
    
    for holding in holdings:
        stock = lookup(holding["symbol"])
        if stock:
            current_value = stock["price"] * holding["shares"]
            total_stock_value += current_value
            
            portfolio.append({
                "symbol": holding["symbol"],
                "name": stock["name"],
                "shares": holding["shares"],
                "price": stock["price"],
                "total": current_value
            })
    
    # Grand total
    grand_total = cash + total_stock_value
    
    return render_template("index.html", 
                         portfolio=portfolio, 
                         cash=cash, 
                         total_stock_value=total_stock_value,
                         grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get form data
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")
        
        # Validate symbol
        if not symbol:
            return apology("must provide symbol", 400)
        
        # Validate shares
        if not shares_input:
            return apology("must provide number of shares", 400)
        
        try:
            shares = int(shares_input)
            if shares <= 0:
                return apology("shares must be positive integer", 400)
        except ValueError:
            return apology("shares must be positive integer", 400)
        
        # Look up stock
        stock = lookup(symbol.upper())
        if stock is None:
            return apology("symbol not found", 400)
        
        # Calculate total cost
        total_cost = stock["price"] * shares
        
        # Check user's cash
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        
        if user_cash < total_cost:
            return apology("insufficient funds", 400)
        
        # Update user's cash
        new_cash = user_cash - total_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])
        
        # Record transaction
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, ?)
        """, session["user_id"], stock["symbol"], shares, stock["price"], "BUY")
        
        # Update or insert holdings
        existing_holding = db.execute("""
            SELECT shares FROM holdings WHERE user_id = ? AND symbol = ?
        """, session["user_id"], stock["symbol"])
        
        if existing_holding:
            # Update existing holding
            new_shares = existing_holding[0]["shares"] + shares
            db.execute("""
                UPDATE holdings SET shares = ? WHERE user_id = ? AND symbol = ?
            """, new_shares, session["user_id"], stock["symbol"])
        else:
            # Create new holding
            db.execute("""
                INSERT INTO holdings (user_id, symbol, shares)
                VALUES (?, ?, ?)
            """, session["user_id"], stock["symbol"], shares)
        
        # Flash success message
        flash(f"Successfully bought {shares} shares of {stock['symbol']} for {usd(total_cost)}!")
        
        # Redirect to home page
        return redirect("/")
    
    # GET request - show buy form
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get all user's transactions
    transactions = db.execute("""
        SELECT symbol, shares, price, type, timestamp
        FROM transactions 
        WHERE user_id = ?
        ORDER BY timestamp DESC
    """, session["user_id"])
    
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Get symbol from form
        symbol = request.form.get("symbol")
        
        # Validate symbol
        if not symbol:
            return apology("must provide symbol", 400)
        
        # Look up stock quote
        stock = lookup(symbol.upper())
        
        # Check if stock exists
        if stock is None:
            return apology("symbol not found", 400)
        
        # Render result template with stock data
        return render_template("quoted.html", stock=stock)
    
    # GET request - show quote form
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Get form data
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate input
        if not username:
            return apology("must provide username", 400)
            
        if not password:
            return apology("must provide password", 400)
            
        if not confirmation:
            return apology("must confirm password", 400)
            
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Hash password and try to insert new user
        hash_password = generate_password_hash(password)
        
        try:
            # Try to insert new user - will raise ValueError if username exists
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_password)
        except ValueError:
            # Username already exists due to UNIQUE constraint
            return apology("username already exists", 400)

        # Log user in automatically
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        # Redirect to home page
        return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Get form data
        symbol = request.form.get("symbol")
        shares_input = request.form.get("shares")
        
        # Validate symbol
        if not symbol:
            return apology("must select stock", 400)
        
        # Validate shares
        if not shares_input:
            return apology("must provide number of shares", 400)
        
        try:
            shares = int(shares_input)
            if shares <= 0:
                return apology("shares must be positive integer", 400)
        except ValueError:
            return apology("shares must be positive integer", 400)
        
        # Check if user owns this stock
        holding = db.execute("""
            SELECT shares FROM holdings 
            WHERE user_id = ? AND symbol = ?
        """, session["user_id"], symbol)
        
        if not holding or holding[0]["shares"] < shares:
            return apology("not enough shares", 400)
        
        # Look up current stock price
        stock = lookup(symbol)
        if stock is None:
            return apology("symbol not found", 400)
        
        # Calculate sale value
        sale_value = stock["price"] * shares
        
        # Update user's cash
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        new_cash = current_cash + sale_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])
        
        # Record transaction
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, ?)
        """, session["user_id"], stock["symbol"], -shares, stock["price"], "SELL")
        
        # Update holdings
        new_shares = holding[0]["shares"] - shares
        if new_shares == 0:
            # Remove holding if no shares left
            db.execute("""
                DELETE FROM holdings WHERE user_id = ? AND symbol = ?
            """, session["user_id"], symbol)
        else:
            # Update shares
            db.execute("""
                UPDATE holdings SET shares = ? WHERE user_id = ? AND symbol = ?
            """, new_shares, session["user_id"], symbol)
        
        # Flash success message
        flash(f"Successfully sold {shares} shares of {stock['symbol']} for {usd(sale_value)}!")
        
        # Redirect to home page
        return redirect("/")
    
    # GET request - show sell form with user's stocks
    else:
        # Get user's holdings for dropdown
        holdings = db.execute("""
            SELECT symbol FROM holdings 
            WHERE user_id = ? AND shares > 0
            ORDER BY symbol
        """, session["user_id"])
        
        return render_template("sell.html", holdings=holdings)
