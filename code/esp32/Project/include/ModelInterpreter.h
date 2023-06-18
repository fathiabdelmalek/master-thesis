#include <stdint.h>

namespace tflite
{
    template <unsigned int tOpCount>
    class MicroMutableOpResolver;
    class ErrorReporter;
    class Model;
    class MicroInterpreter;
}

struct TfLiteTensor;


class ModelInterpreter {
private:
  uint8_t* tensor_arena;
  const tflite::Model* model;
  tflite::ErrorReporter* error_reporter;
  tflite::MicroInterpreter* interpreter;
  tflite::MicroMutableOpResolver<3>* resolver;
  TfLiteTensor* input;
  TfLiteTensor* output;
  bool predicted;
public:
  ModelInterpreter(const void*);
  ~ModelInterpreter();
  void setInput(float**);
  bool predict();
  float* getOutput();
  float getOutputSize();
  uint8_t getPrediction();
};
