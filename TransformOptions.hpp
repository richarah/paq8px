#ifndef PAQ8PX_TRANSFORMOPTIONS_HPP
#define PAQ8PX_TRANSFORMOPTIONS_HPP

struct TransformOptions
{
  bool skipRgb = false;
  bool useBruteForceDeflateDetection = false;
  TransformOptions(const Shared * const shared) {
    skipRgb = shared->GetOptionSkipRGB();
    useBruteForceDeflateDetection = shared->GetOptionBruteforceDeflateDetection();
  }
};

#endif