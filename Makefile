CC = g++
CFLAGS = -Wall -Wextra -std=c++20 -I include

SRCS = tests/test_main.cpp tests/test.cpp tests/assert.cpp
FORMAT_FILES = include/*.hpp tests/*.cpp tests/*.hpp
TARGET = tests

all: format $(TARGET)
	chmod +x $(TARGET)
	./$(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

format:
	clang-format -i $(FORMAT_FILES)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all clean format