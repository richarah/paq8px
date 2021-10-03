#include "Block.hpp"

//IBlock::IBlock(Shared* const sh, Encoder* const enc) : shared(sh), encoder(enc) {}

namespace Block {

  void EncodeBlockSize(Encoder* const encoder, uint64_t blockSize) {
    while (blockSize > 0x7FU) {
      encoder->compressByte(&encoder->predictorMain, 0x80 | (blockSize & 0x7FU));
      blockSize >>= 7U;
    }
    encoder->compressByte(&encoder->predictorMain, uint8_t(blockSize));
  }

  uint64_t DecodeBlockSize(Encoder* const encoder) {
    uint64_t blockSize = 0;
    uint8_t b = 0;
    int i = 0;
    do {
      b = encoder->decompressByte(&encoder->predictorMain);
      blockSize |= uint64_t((b & 0x7FU) << i);
      i += 7;
    } while ((b >> 7U) > 0);
    return blockSize;
  }

  void EncodeBlockType(Encoder* const encoder, BlockType blocktype) {
    encoder->compressByte(&encoder->predictorMain, uint8_t(blocktype));
  }

  BlockType DecodeBlockType(Encoder* const encoder) {
    uint8_t b = encoder->decompressByte(&encoder->predictorMain);
    return (BlockType)b;
  }

  void EncodeInfo(Encoder* const encoder, int info) {
    encoder->compressByte(&encoder->predictorMain, (info >> 24) & 0xFF);
    encoder->compressByte(&encoder->predictorMain, (info >> 16) & 0xFF);
    encoder->compressByte(&encoder->predictorMain, (info >> 8) & 0xFF);
    encoder->compressByte(&encoder->predictorMain, (info) & 0xFF);
  }

  int DecodeInfo(Encoder* const encoder) {
    int info = 0;
    for (int j = 0; j < 4; ++j) {
      info <<= 8;
      info += encoder->decompressByte(&encoder->predictorMain);
    }
    return info;
  }


};