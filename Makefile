CXX = g++
CXXFLAGS = -std=c++17 -Wall -Ilib -D_WIN32_WINNT=0x0A00

SRCS = src/main.cpp src/client.cpp src/caisse.cpp \
       src/supermarche.cpp src/serveur.cpp

TARGET = supermarche

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lws2_32

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o