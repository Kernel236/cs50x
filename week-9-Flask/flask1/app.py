import sqlite3 as SQL
from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS =  [
    "Basketball",
    "Soccer",
    "Fresbee",
]

db = SQL("sqlite3:///registrants.db")

@app.route("/", methods=["GET", "POST"])
def index():
        return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():

    name = request.form.get("name")
    if not name:
          return render_template("error.html", message="Missing name")
    
    sport = request.form.get("sport")
    if not sport:
          return render_template("error.html", message="Missing sport")
    
    if sport not in SPORTS:
          return render_template("error.html", message="Invalid sport")
    
    db.execute("INSERT INTO registrants (name, sport) VALUE (?, ?)", name, sport)
    
    return render_template("success.html")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT name, sport FROM registrants")
    return render_template("registrants.html", registrants=registrants)
