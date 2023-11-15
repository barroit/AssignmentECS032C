// includes go here
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
	int value;
	struct Node *next;
} Node;

// global defines (constants) go here
#define CARD_PER_PLAYER 5
#define MIN_CARD_VALUE 1
#define MAX_CARD_VALUE 10

// global variables go here
Node *card_buffer = NULL;
int deck_size = 0;
int card_count = 0;

int *scores = NULL;

void empty(void);

// prints an error message and exits returning an error to the OS
void fatal(char* msg)
{
	empty();
	free(scores);
	printf("Error: %s\n", msg);
	exit(1);
}

// instructs user how to use the program and exits returning an error to the os
void usage(void)
{
	printf("drawfive <number of players> [list of cards]\n\t The number of players must be at least 2\n");
	exit(1);
}

// pushes an integer onto the stack, exits with error if the stack is full
void push(int val)
{
	if (card_count >= deck_size) fatal("Stack is full!");
	Node *new_card = (Node *)malloc(sizeof(Node));

	new_card->next = card_buffer;
	new_card->value = val;

	card_buffer = new_card;
	card_count++;
}

// returns an integer from the stack, exits with error if the stack is empty
int pop(void)
{
	if (!card_buffer) fatal("Stack is empty!");
	Node *top = card_buffer;
	
	int value = top->value;
	card_buffer = top->next;

	card_count--;
	free(top);
	return value;
}

// prevent memory leak
void empty(void)
{
	while (card_buffer)
		pop();
}

// fills stack with parameters provided from the command line
void fillStack(int argc, char** argv)
{
	for (int i = 2; i < argc; i++)
	{
		int value = atoi(argv[i]);
		if (value < MIN_CARD_VALUE || value > MAX_CARD_VALUE)
			fatal("Card value out of range!");
		push(value);
	}
}

// fills stack with random numbers
void fillStackWithRandomNumbers(int _) // no need to use players
{
	srand(time(NULL));

	int i = deck_size;
	while (i--)
		push(rand() % 10 + 1);
}

// displays the stack in a space separated list. Use this for debugging. It's not necessary to call this function in a normally running program
void showStack(void)
{
	Node *current = card_buffer;
	while (current)
	{
		printf("%-2d", current->value);
		current = current->next;
	}
	putchar('\n');
}

// displays scores for all players
void showScores(int players)
{
	for (int i = 0; i < players; i++)
		printf("Player %d scored %d\n", i + 1, scores[i]);
}

// runs one game for the provided number of players reporting each card drawn by each player
void runGame(int players)
{
	static int game_round = 1;
	for (int i = 0; i < players; i++)
	{
		int value = pop();
		scores[i] += value;
		printf("Player %d draws %d as %d of %d cards\n", i + 1, value, game_round, CARD_PER_PLAYER);
	}
	game_round++;
}

int compareScores(const void *a, const void *b) {
	return *(*(int **)b) - *(*(int **)a);
}

// computes the winning player and shows the results, pay careful attention to the output, the detail does matter
void showWinners(int players)
{
	int **sorted_scores = (int **)malloc(sizeof(int *) * players);

	for (int i = 0; i < players; i++)
		sorted_scores[i] = &scores[i];

	qsort(sorted_scores, players, sizeof(int *), compareScores);
	int max_score = *sorted_scores[0];

	if (max_score != *sorted_scores[1])
	{
		printf("Player %ld won with a score of %d\n", sorted_scores[0] - scores + 1, max_score);
	}
	else
	{
		printf("Players ");
		int i = 0;
		while (i < players && *sorted_scores[i] == max_score)
		{
			if (i > 0)
			{
				if (i == players - 1 || *sorted_scores[i + 1] != max_score)
				{
					printf(i != 1 ? ", " : " ");
					printf("and ");
				}
				else
				{
					printf(", ");
				}
			}
			printf("%ld", sorted_scores[i] - scores + 1); // Calculate the index
			i++;
		}
		printf(" tied with a score of %d\n", max_score);
	}

	free(sorted_scores);
}

int main(int argc, char **argv)
{
	if (argc < 2) usage();

	int players = atoi(argv[1]);
	if (players < 2) usage();

	deck_size = players * CARD_PER_PLAYER;
	scores = (int *)calloc(players, sizeof(int));
	
	if (argc == 2)
		fillStackWithRandomNumbers(players);
	else
		fillStack(argc, argv);

	for (int i = 0; i < CARD_PER_PLAYER; i++)
		runGame(players);
	putchar('\n');

	showScores(players);
	putchar('\n');

	showWinners(players);

	empty();
	free(scores);
	return 0;
}
