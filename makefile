# the compiler: define as g++ for C++
CC = g++

# compiler flags:
# -g    adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
CFLAGS = -Wall

# the build target executable
TARGET = src/*
OUTPUT = bin/main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(OUTPUT) $(TARGET).cpp

clean:
	$(RM) $(OUTPUT)
