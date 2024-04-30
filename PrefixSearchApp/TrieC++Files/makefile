CXX = g++
CXXFLAGS = -Wall -g -std=c++11

TARGET = trie
OBJECTS = main.o trieNode.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ 

main.o: main.cpp trieNode.h
	$(CXX) $(CXXFLAGS) -c main.cpp

trieNode.o: trieNode.cpp trieNode.h
	$(CXX) $(CXXFLAGS) -c trieNode.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
