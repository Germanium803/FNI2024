CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = resol_2024
SRC = resol_2024.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
