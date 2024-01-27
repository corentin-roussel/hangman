CC = gcc
SRCS = hangman.c
TARGET = hangman
OBJS = $(SRCS:.c=.o)
# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

LDFLAGS = -L libncurses
ifeq ($(OS),Windows_NT)
	LDFLAGS += -lncursesw
else
	LDFLAGS += -lncurses
endif
INCLUDES = -I ncurses
CFLAGS = -Wall -Wextra -Werror -g $(INLCUDES)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)

f-clean: clean
	rm -f $(TARGET)

run: $(TARGET)
	./$< $(RUN_ARGS)