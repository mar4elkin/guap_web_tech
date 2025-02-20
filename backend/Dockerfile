FROM ubuntu:latest

ADD . /app

WORKDIR /app/include
RUN apt-get update && \
    apt-get install -y gfortran && \
    apt-get install -y \
    cmake g++ libboost-all-dev libssl-dev \
    curl \
    wget \
    libasio-dev git && \
    git clone https://github.com/CrowCpp/Crow.git && \
    curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r4.0.0/mongo-cxx-driver-r4.0.0.tar.gz && \
    tar -xzf mongo-cxx-driver-r4.0.0.tar.gz && \
    rm -r mongo-cxx-driver-r4.0.0.tar.gz

WORKDIR /app/include/Crow/build
RUN cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    make install .

WORKDIR /app/include/mongo-cxx-driver-r4.0.0/build
RUN cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_STANDARD=20 \
    && cmake --build . && \
    cmake --build . --target install

WORKDIR /app/include/stb
RUN wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h && \
    wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h

WORKDIR /app/build
RUN cmake .. && \
    cmake --build .

ENTRYPOINT ["/app/build/EShop"]