CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bin/mini-container

all: $(TARGET)

$(TARGET): src/main.c
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(TARGET) src/main.c

clean:
	rm -rf bin
