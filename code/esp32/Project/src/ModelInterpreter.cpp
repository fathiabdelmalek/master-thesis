#include "ModelInterpreter.h"

#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

constexpr int kTensorArenaSize = 46200;


ModelInterpreter::ModelInterpreter(const void* buf) {
  error_reporter = new tflite::MicroErrorReporter();
  model = tflite::GetModel(buf);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter, 
    "Model provided is schema version %d not equal to supported version %d.", 
    model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  resolver = new tflite::MicroMutableOpResolver<3>();
  resolver->AddFullyConnected();
  resolver->AddSoftmax();
  resolver->AddUnidirectionalSequenceLSTM();

  tensor_arena = (uint8_t *)malloc(kTensorArenaSize);
  if (!tensor_arena) {
    TF_LITE_REPORT_ERROR(error_reporter, "Could not allocate arena");
    return;
  }

  interpreter = new tflite::MicroInterpreter(
      model, *resolver, tensor_arena, kTensorArenaSize, error_reporter);

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  size_t used_bytes = interpreter->arena_used_bytes();
  TF_LITE_REPORT_ERROR(error_reporter, "Used bytes %d\n", used_bytes);

  input = interpreter->input(0);
  output = interpreter->output(0);

  predicted = false;

  free(tensor_arena);
}

ModelInterpreter::~ModelInterpreter() {
  delete interpreter;
  delete resolver;
  delete error_reporter;
  if (tensor_arena) {
    free(tensor_arena);
    tensor_arena = nullptr;
  }
}

void ModelInterpreter::setInput(float** data) {
  for (int i = 0; i < 150; i++) {
    for (int j = 0; j < 11; j++) {
      input->data.f[i * 11 + j] = data[i][j];
    }
  }
}

bool ModelInterpreter::predict() {
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke() failed");
    predicted = false;
  }
  predicted = true;
  return predicted;
}

float* ModelInterpreter::getOutput() {
  return predicted ? output->data.f : nullptr;
}

float ModelInterpreter::getOutputSize() {
  return predicted ? output->dims->data[output->dims->size - 1] : -1;
}

uint8_t ModelInterpreter::getPrediction() {
  if (!predicted)
    return -1;
  float* output_data = getOutput();
  float maxPrediction = output_data[0];
  uint8_t maxIndex = 0;
  for (size_t i = 1; i < getOutputSize(); i++) {
    if (output_data[i] > maxPrediction) {
      maxPrediction = output_data[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}
