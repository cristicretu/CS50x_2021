from flask import Flask, render_template, request

# Flask turn the current file into an application
app = Flask(__name__)

@app.route("/index.html")
def index():
    return render_template("index.html")

@app.route("/greet", methods=["POST"])
def greet():
    return render_template("greet.html", name=request.form.get("name", "world"))
