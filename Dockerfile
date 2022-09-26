FROM debian:latest

RUN apt-get update && apt-get -y install clang cmake build-essential git

RUN apt-get install -y zlib1g zlib1g-dev

WORKDIR /build
RUN git clone https://github.com/richarah/paq8px
WORKDIR /build/paq8px
RUN cmake .
RUN make -j $(nproc)
