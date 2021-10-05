#ifndef PAQ8PX_MIXERFACTORY_HPP
#define PAQ8PX_MIXERFACTORY_HPP

#include "utils.hpp"
#include "Mixer.hpp"
#include "Shared.hpp"
#include "SimdMixer.hpp"

class MixerFactory {
private:
  const Shared* const shared;
public:
  Mixer* createMixer(int n, int m, int s, int promoted) const;
  MixerFactory(const Shared* const sh);
};

#endif //PAQ8PX_MIXERFACTORY_HPP
