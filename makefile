CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
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

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS)

f-clean: clean
	rm -f $(TARGET)

run: $(TARGET)
	./$< $(RUN_ARGS)