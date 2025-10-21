import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Add the user's entry into the database
        name = request.form.get("name")
        if not name:
            return render_template("error.html", message="Missing name")
        
        day = request.form.get("day")
        if not day:
            return render_template("error.html", message="Missing day")
        
        month = request.form.get("month")
        if not month:
            return render_template("error.html", message="Missing month")
        
        # Convert to integers and validate ranges
        try:
            day = int(day)
            month = int(month)
            
            if not (1 <= day <= 31):
                return render_template("error.html", message="Day must be between 1 and 31")
            
            if not (1 <= month <= 12):
                return render_template("error.html", message="Month must be between 1 and 12")
                
        except ValueError:
            return render_template("error.html", message="Day and month must be numbers")
        
        db.execute("INSERT INTO birthdays (name, day, month) VALUES (?, ?, ?)", name, day, month)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


