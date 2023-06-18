from flask import Flask, request
from scipy import stats
from keras.models import load_model

import numpy as np
import tensorflow as tf
import pyttsx3


words = ['bad', 'deaf', 'fine', 'good', 'goodbye', 'hello', 'hungry', 
         'me', 'no', 'please', 'sorry', 'thankyou', 'yes', 'you']
characters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']


app = Flask(__name__)


@app.route('/', methods=['POST'])
def receive_sensor_values():
    json = request.get_json()
    rows = json['data']

    data = np.empty((150, 11), dtype=np.float32)

    for i, row in enumerate(rows):
        for j, values in enumerate(row.values()):
            for k, value in enumerate(values):
                for l, v in enumerate(value.values()):
                    data[i, j*5 + k*3 + l] = v

    data = np.expand_dims(data, axis=0)
    model = load_model('characters.h5')
    predictions = model.predict(data)
    # interpreter = tf.lite.Interpreter(model_path="words.tflite")
    interpreter = tf.lite.Interpreter(model_path="characters.tflite")
    interpreter.allocate_tensors()
    interpreter.set_tensor(interpreter.get_input_details()[0]['index'], data)
    interpreter.invoke()
    # predictions = interpreter.get_tensor(interpreter.get_output_details()[0]['index'])
    print(predictions)
    max_prediction_indices = np.argmax(predictions, axis=2)
    print(max_prediction_indices)
    most_appeared = np.squeeze(stats.mode(max_prediction_indices, axis=1).mode)
    print(most_appeared)
    # print(words[most_appeared])
    print(characters[most_appeared])
    engine = pyttsx3.init()
    # engine.say(words[most_appeared])
    engine.say(characters[most_appeared])
    engine.runAndWait()

    response = {
        'message': 'Sensor values received',
        # 'prediction': words[most_appeared]
        'prediction': characters[most_appeared]
    }
    return response, 200


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
