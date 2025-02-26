CC = g++
CFLAGS = -Wall -Wextra -O2
TARGET = maze_solver
SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
