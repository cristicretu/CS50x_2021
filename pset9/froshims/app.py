# from cs50 import SQL
# from flask import Flask, render_template, request, redirect

# app = Flask(__name__)

# db = SQL("sqlite:///froshims.db")

# SPORTS = [
#     "Dodgeball",
#     "Flag Football",
#     "Soccer",
#     "Volleyball",
#     "Ultimate Frisbee"
# ]

# @app.route("/")
# def index():
#     return render_template("index.html", sports=SPORTS)

# @app.route("/register", methods=["POST"])
# def register():
#     name = request.form.get("name")
#     if not name:
#         return render_template("error.html", message="Missing name")
#     sport = request.form.get("sport")
#     if not sport:
#         return render_template("error.html", message="Missing sport")
#     if sport not in SPORTS:
#         return render_template("error.html", message="Invalid sport")
    
#     db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

#     return redirect("/registrants")

# @app.route("/registrants")
# def registrants():
#     registrants = db.execute("SELECT * FROM registrants")
#     return render_template("registrants.html", registrants=registrants)


from flask import Flask, render_template, request, redirect, session
from flask_session import Session

app = Flask(__name__)
app.config["SESSION PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/login", methods=["POST", "GET"])
def login():
    return render_template("login.html")