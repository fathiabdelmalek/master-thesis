from flask import Flask, request
import pyttsx3


app = Flask(__name__)


@app.route('/', methods=['POST'])
def receive_word():
    json = request.get_json()
    rows = json['data']
    print(rows)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

