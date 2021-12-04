#ifndef PAQ8PX_CONTEXTMODELBLOCK_HPP
#define PAQ8PX_CONTEXTMODELBLOCK_HPP

#include "../MixerFactory.hpp"

class ContextModelBlock {

private:
  Shared* const shared;
  Mixer* m;

public:
  ContextModelBlock(Shared* const sh, const MixerFactory* const mf);
  int p();

  ~ContextModelBlock();

};

#endif //PAQ8PX_CONTEXTMODELBLOCK_HPP