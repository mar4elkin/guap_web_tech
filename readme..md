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

## libpqxx
git clone https://github.com/jtv/libpqxx.git

### libpqxx libs
sudo apt-get install libpq-dev
sudo apt-get install pkg-config

### libpqxx isntall
cmake ..
sudo make install .

## stb_image
mkdir stb
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
