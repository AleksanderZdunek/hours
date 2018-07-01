TARGET = hours
SOURCE = main.cpp

VER = -std=c++11
CFLAGS = $(VER) -O3 -Wall
CXX = g++

$(TARGET): $(SOURCE)
	$(CXX) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)
