CC = g++
CFLAGS = -Wall -Wextra -std=c++20 -I include

SRCS = tests/test_main.cpp tests/test.cpp tests/assert.cpp
FORMAT_FILES = include/*.hpp tests/*.cpp tests/*.hpp main.cpp
TARGET = test_runner

SFML_INCLUDE = C:/Users/anham/vcpkg/installed/x64-windows/include
SFML_LIB = C:/Users/anham/vcpkg/installed/x64-windows/lib
SFML_BIN = C:/Users/anham/vcpkg/installed/x64-windows/bin

all: format $(TARGET)
	./$(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

format:
	clang-format -i $(FORMAT_FILES)

gui: copy_dll
	cl /std:c++20 /EHsc main.cpp \
		/I include \
		/I $(SFML_INCLUDE) \
		/link \
		/LIBPATH:$(SFML_LIB) \
		sfml-graphics.lib \
		sfml-window.lib \
		sfml-system.lib \
		user32.lib

copy_dll:
	cp $(SFML_BIN)/sfml-graphics-3.dll .
	cp $(SFML_BIN)/sfml-window-3.dll .
	cp $(SFML_BIN)/sfml-system-3.dll .
	cp $(SFML_BIN)/freetype.dll .
	cp $(SFML_BIN)/libpng16.dll .
	cp $(SFML_BIN)/z.dll .
	cp $(SFML_BIN)/bz2.dll .
	cp $(SFML_BIN)/brotlidec.dll .
	cp $(SFML_BIN)/brotlicommon.dll .
	cp C:/Windows/Fonts/arial.ttf .

run:
	./main.exe

clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -f *.obj *.dll arial.ttf

.PHONY: all clean format gui run copy_dll