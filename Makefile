CXX = g++
CXXFLAGS = -std=c++17 -O2
PKG_CONFIG = pkg-config
PKG_FLAGS = `$(PKG_CONFIG) --cflags --libs opencv4 tesseract`

SRC = ch7al_dy3ti.cpp
TARGET = ocr_sum

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(PKG_FLAGS)

clean:
	rm -f $(TARGET)
