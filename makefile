CC = g++
CFLAGS = -Wall -pthread -std=c++20

TARGET = matmult
SRC = runner.cpp Matrix.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o *.out