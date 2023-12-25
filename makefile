CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = hangman.c
TARGET = hangman
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS)

f-clean: clean
	rm -f $(TARGET)

run: $(TARGET)
	./$<