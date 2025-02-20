# frontend
npm/yarn install
profit

# backend

## crow
git clone https://github.com/CrowCpp/Crow.git

### crow libs
sudo apt install cmake g++ libboost-all-dev libssl-dev
sudo apt-get install libasio-dev

### crow isntall
cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF
sudo make install .

## mongodb 
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r4.0.0/mongo-cxx-driver-r4.0.0.tar.gz
tar -xzf mongo-cxx-driver-r4.0.0.tar.gz
cd mongo-cxx-driver-r4.0.0/build

## mongodb install
cmake ..                                \
    -DCMAKE_BUILD_TYPE=Release          \
    -DCMAKE_CXX_STANDARD=20

cmake --build .
sudo cmake --build . --target install


## stb_image
mkdir stb
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
