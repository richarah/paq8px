#ifndef PAQ8PX_TRANSFORMOPTIONS_HPP
#define PAQ8PX_TRANSFORMOPTIONS_HPP

struct TransformOptions
{
  bool skipRgb = false;
  bool useBruteForceDeflateDetection = false;
  TransformOptions(const Shared * const shared) {
    skipRgb = (shared->options & OPTION_SKIPRGB) != 0u;
    useBruteForceDeflateDetection = (shared->options & OPTION_BRUTEFORCE_DEFLATE_DETECTION) != 0;
  }
};

#endif