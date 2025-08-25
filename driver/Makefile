CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
INCLUDES = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS = -lrashunal -lrmatrix

# Source files
SRCS = driver.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = driver

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS) -Wl,-rpath,/usr/local/lib

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
