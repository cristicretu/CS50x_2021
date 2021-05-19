from flask import Flask, render_template, request

# Flask turn the current file into an application
app = Flask(__name__)

@app.route("/index.html")
def index():
    return render_template("index.html", name=request.args.get("name", "world"))
