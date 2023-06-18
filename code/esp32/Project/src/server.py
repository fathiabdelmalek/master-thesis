from flask import Flask, request
import pyttsx3


app = Flask(__name__)


@app.route('/', methods=['POST'])
def receive_sensor_values():
    json = request.get_json()
    print(json)

    engine = pyttsx3.init()
    engine.say(json['word'])
    engine.runAndWait()

    response = {
        'success': 'predicted word received',
    }
    return response, 200


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
