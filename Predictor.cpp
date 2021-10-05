#include "Predictor.hpp"

Predictor::Predictor(Shared* const sh) : shared(sh), sse(sh) {
  shared->reset();
  mixerFactory = new MixerFactory(shared);
  models = new Models(sh, mixerFactory);
  models->trainModelsWhenNeeded();
  contextModel = new ContextModel(sh, models, mixerFactory);
}

Predictor::~Predictor() {
  delete models;
  delete contextModel;
  delete mixerFactory;
}

uint32_t Predictor::p() {
  uint32_t pr = contextModel->p();
  pr = sse.p(pr);
  return pr;
}


