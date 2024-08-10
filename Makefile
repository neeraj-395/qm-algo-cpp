CC = g++
CFLAGS = -Wall -Wextra
OBJS = minterm.o parse_minterm.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS) main.cpp
	$(CC) $(CFLAGS) $(OBJS) main.cpp -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(TARGET)