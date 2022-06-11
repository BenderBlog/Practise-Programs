# Usage: make

# Use clang as compilor, and lld as linker.
CC = clang++
target = bus

# Get the *.cpp file, and then generate *.o file.
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

# Link object file into executable file.
$(target):$(OBJ)
	$(CC) $^ -o $@

# Compile every cpp file to object file.
# aka *.o file in *Linux*
%.o:%.cpp
	$(CC) -o $@ -c $^

# Delete everything other than source code.
.PHONY:clean
clean:
	rm -rf *.o out
