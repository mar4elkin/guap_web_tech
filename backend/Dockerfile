FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y \
    curl \
    cmake \
    g++ \
    libboost-all-dev \
    libssl-dev \
    libasio-dev \
    git \
    libmongoc-dev \
    libbson-dev \
    && rm -rf /var/lib/apt/lists/*

RUN curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r4.0.0/mongo-cxx-driver-r4.0.0.tar.gz && \
    tar -xzf mongo-cxx-driver-r4.0.0.tar.gz && \
    cd mongo-cxx-driver-r4.0.0/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=20 && \
    cmake --build . && \
    cmake --build . --target install && \
    cd ../.. && \
    rm -rf mongo-cxx-driver-r4.0.0 mongo-cxx-driver-r4.0.0.tar.gz

COPY ./build/EShop /app/EShop

WORKDIR /app

RUN chmod +x ./EShop

ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

ENTRYPOINT ["./EShop"]