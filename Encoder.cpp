#include "Encoder.hpp"


Encoder::Encoder(Shared* const sh, Mode m, File *f) : shared(sh), ari(f), mode(m), archive(f), alt(nullptr), predictorMain(sh) {
  if( mode == DECOMPRESS ) {
    uint64_t start = size();
    archive->setEnd();
    uint64_t end = size();
    if( end >= (UINT64_C(1) << 31)) {
      quit("Large archives not yet supported.");
    }
    setStatusRange(0.0, static_cast<float>(end));
    archive->setpos(start);
  }
  if( shared->level > 0 && mode == DECOMPRESS ) { // x = first 4 bytes of archive
    ari.prefetch();
  }
}

auto Encoder::getMode() const -> Mode { return mode; }

auto Encoder::size() const -> uint64_t { return archive->curPos(); }

void Encoder::flush() {
  if( mode == COMPRESS && shared->level > 0 ) {
    ari.flush();
  }
}

void Encoder::setFile(File *f) { alt = f; }

void Encoder::compressByte(Predictor *predictor, uint8_t c) {
  assert(mode == COMPRESS);
  if( shared->level == 0 ) {
    archive->putChar(c);
  } else {
    for( int i = 7; i >= 0; --i ) {
      int p = predictor->p();
      int y = (c >> i) & 1;
      ari.encodeBit(p, y);
      predictor->update(y);
    }
  }
}

uint8_t Encoder::decompressByte(Predictor *predictor) {
  if( mode == COMPRESS ) {
    assert(alt);
    return alt->getchar();
  }
  if( shared->level == 0 ) {
    return archive->getchar();
  } else {
    uint8_t c = 0;
    for( int i = 0; i < 8; ++i ) {
      int p = predictor->p();
      int y = ari.decodeBit(p);
      c = c << 1 | y;
      predictor->update(y);
    }
    return c;
  }
}



void Encoder::setStatusRange(float perc1, float perc2) {
  p1 = perc1;
  p2 = perc2;
}

void Encoder::printStatus(uint64_t n, uint64_t size) const {
  fprintf(stderr, "%6.2f%%\b\b\b\b\b\b\b", (p1 + (p2 - p1) * n / (size + 1)) * 100);
  fflush(stderr);
}

void Encoder::printStatus() const {
  fprintf(stderr, "%6.2f%%\b\b\b\b\b\b\b", float(size()) / (p2 + 1) * 100);
  fflush(stderr);
}
