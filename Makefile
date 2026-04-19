# The Compiler to use
CC = gcc

# Compiler flags: 
# -Wall (Show all warnings)
# -g (Include debugging info)
CFLAGS = -Wall -g

# The final executable name
TARGET = lumina

# The default rule: what happens when you just type 'make'
all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

# Rule to clean up the folder (deletes the executable)
clean:
	rm -f $(TARGET)