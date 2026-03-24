CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
LDFLAGS = -lm

BINS = policy_iteration value_iteration value_iteration_v2

all: $(BINS)

policy_iteration: policy_iteration_actualisation.c
	$(CC) $(CFLAGS) -o $@ policy_iteration_actualisation.c $(LDFLAGS)

value_iteration: value_iteration_actualisation.c
	$(CC) $(CFLAGS) -o $@ value_iteration_actualisation.c $(LDFLAGS)

value_iteration_v2: value_iteration_actualisation_v2.c
	$(CC) $(CFLAGS) -o $@ value_iteration_actualisation_v2.c $(LDFLAGS)

clean:
	rm -f $(BINS)

.PHONY: all clean
