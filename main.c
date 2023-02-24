#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RANKS	     8
#define FILES	     8
#define MAXPOSITIONS 8

typedef struct gamepiece_t {
	int rank;
	int file;
} gamepiece_t;

typedef struct position_stack_t {
	gamepiece_t positions[MAXPOSITIONS];
	int	    len;
} position_stack_t;

void print_frameno(void);
void print_board(position_stack_t *p);
void print_stack(position_stack_t *p);
void print_state(position_stack_t *p);
void backtrack(position_stack_t *p);
int  threatens(gamepiece_t *x, gamepiece_t *y);
int  reject(position_stack_t *p);
int  accept(position_stack_t *p);

void print_frameno(void) {
	static unsigned long count;
	printf("frame %lu\n", ++count);
}

void print_board(position_stack_t *p) {
	char board[RANKS][FILES];

	for (int i = 0; i < RANKS; ++i) {
		for (int j = 0; j < FILES; ++j) {
			board[i][j] = (i + j) & 1 ? ' ' : '#';
		}
	}

	for (int i = 0; i < p->len; ++i) {
		board[p->positions[i].rank][p->positions[i].file] = 'Q';
	}

	for (int i = 0; i < RANKS; ++i) {
		for (int j = 0; j < FILES; ++j) {
			printf("[%c]", board[i][j]);
		}
		printf("\n");
	}
}

void print_stack(position_stack_t *p) {
	for (int i = 0; i < p->len; ++i) {
		printf("piece %d: %d, %d\n", i, p->positions[i].rank,
		       p->positions[i].file);
	}
}

void print_state(position_stack_t *p) {
	print_frameno();
	print_stack(p);
	print_board(p);
	printf("\n");
}

void backtrack(position_stack_t *p) {
	if (reject(p)) {
		return;
	}

	if (accept(p)) {
		print_state(p);
		return;
	}

	for (int rank = p->len ? p->positions[p->len - 1].rank + 1 : 0;
	     rank < RANKS; ++rank) {
		for (int file = 0; file < FILES; ++file) {
			p->positions[p->len++] =
			    (gamepiece_t){.rank = rank, .file = file};

			backtrack(p);

			--p->len;
		}
	}
}

int threatens(gamepiece_t *x, gamepiece_t *y) {
	return x->file == y->file || x->rank == y->rank ||
	       abs(x->file - y->file) == abs(x->rank - y->rank);
}

int reject(position_stack_t *p) {
	if (p->len < 2) {
		return 0;
	}

	gamepiece_t *new_move = &p->positions[p->len - 1];

	for (gamepiece_t *previous_move = p->positions;
	     previous_move != new_move; ++previous_move) {
		if (threatens(new_move, previous_move)) {
			return 1;
		}
	}

	return 0;
}

int accept(position_stack_t *p) {
	if (p->len == MAXPOSITIONS) {
		return 1;
	}

	return 0;
}

int main(void) {
	position_stack_t positions = {};

	backtrack(&positions);
}
