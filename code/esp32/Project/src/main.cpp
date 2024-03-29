#include "SensorsConfig.h"
#include "ModelInterpreter.h"
#include "models.h"

String words_labels[] = {"bad", "deaf", "fine", "good", "goodbye", "hello", 
"hungry", "me", "no", "please", "sorry", "thankyou", "yes", "you"};
String characters_labels[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 
"k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

ModelInterpreter* mi;

void setup() {
  Serial.begin(115200);
  connectToMPU();
  mi = new ModelInterpreter(words_tflite);
  // mi = new ModelInterpreter(characters_tflite);
}

void loop() {
  Serial.println("Begin reading data");
  float** data = getData();
  Serial.println("Done reading data");
  mi->setInput(data);
  if (!mi->predict()) {
    Serial.println("Failed to predict");
    return;
  }

  String word = words_labels[mi->getPrediction()];
  Serial.print("Predicted word: ");
  Serial.println(word);
  
  // String character = characters_labels[mi->getPrediction()];
  // Serial.print("Predicted character: ");
  // Serial.println(character);

  for (int i = 0; i < 150; i++) {
    delete[] data[i];
  }
  delete[] data;
}
