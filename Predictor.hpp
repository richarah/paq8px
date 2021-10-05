#ifndef PAQ8PX_PREDICTOR_HPP
#define PAQ8PX_PREDICTOR_HPP

#include "Models.hpp"
#include "SSE.hpp"
#include "Shared.hpp"
#include "model/ContextModel.hpp"

/**
 * A Predictor estimates the probability that the next bit of uncompressed data is 1.
 */
class Predictor {
private:
    Shared *shared;
    Models *models;
    MixerFactory* mixerFactory;
    ContextModel *contextModel;
    SSE sse;

public:
  Predictor(Shared* const sh);
  ~Predictor();

    /**
     * Returns P(1) as a 12 bit number (0-4095).
     * @return the prediction
     */
    [[nodiscard]] uint32_t p();

};

#endif //PAQ8PX_PREDICTOR_HPP
