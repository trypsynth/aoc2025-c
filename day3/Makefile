CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS =
TARGET = main

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
