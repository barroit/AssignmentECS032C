#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CARD_PER_PLAYER 5
#define MAX_CARD_TYPE 52
#define MIN_CARD_VALUE 1
#define MAX_CARD_VALUE 13

const char *suits[] = { "Clubs", "Diamonds", "Spades", "Hearts" };
const char *ranks[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

typedef struct
{
	char suit[9];
	char rank[6];
	int value;
} Card;

typedef struct Node
{
	Card *element;
	struct Node *next;
} Node;

Node *card_buffer = NULL;
int deck_size = 0;
int card_count = 0;

int *scores = NULL;

void empty(void);

void fatal(char* msg)
{
	empty();
	free(scores);
	printf("Error: %s\n", msg);
	exit(1);
}

void usage(void)
{
	printf("drawfive <number of players> [list of cards]\n\t The number of players must be at least 2\n");
	exit(1);
}

Card *createCard(int value)
{
	if (card_count >= deck_size) fatal("Stack is full!");
	Card *card = (Card *)malloc(sizeof(Card));

	int idx = value - 1;
	strcpy(card->rank, ranks[idx % MAX_CARD_VALUE]);
	strcpy(card->suit, suits[idx / MAX_CARD_VALUE]);
	card->value = idx % MAX_CARD_VALUE + 1;

	return card;
}

void push(Card *card)
{
	if (card_count >= deck_size) fatal("Stack is full!");
	Node *node = (Node *)malloc(sizeof(Node));

	node->next = card_buffer;
	node->element = card;

	card_buffer = node;
	card_count++;
}

Card *pop(void)
{
	if (!card_buffer) fatal("Stack is empty!");
	Node *top = card_buffer;
	
	Card *card = top->element;
	card_buffer = top->next;

	card_count--;
	free(top);
	return card;
}

void empty(void)
{
	while (card_buffer)
		free(pop());
}

void fillStack(int argc, char** argv)
{
	for (int i = 2; i < argc; i++)
	{
		int value = atoi(argv[i]);

		if (value < MIN_CARD_VALUE || value > MAX_CARD_TYPE)
			fatal("Invalid card index");
	
		push(createCard(value));
	}
}

void fillStackWithRandomNumbers()
{
	srand(time(NULL));

	int i = deck_size;
	while (i--)
		push(createCard(rand() % MAX_CARD_TYPE + 1));
}

void showStack(void)
{
	if (!card_buffer) return;

	Node *current = card_buffer;
	while (current)
	{
		printf("%-4d", current->element->value);
		current = current->next;
	}
	putchar('\n');
}

void showScores(int players)
{
	for (int i = 0; i < players; i++)
		printf("Player %d scored %d\n", i + 1, scores[i]);
}

void runGame(int players)
{
	static int game_round = 1;
	for (int i = 0; i < players; i++)
	{
		Card *card = pop();
		printf("Player %d draws %s of %s with value %d as %d of %d cards\n", i + 1, card->rank, card->suit, card->value, game_round, CARD_PER_PLAYER);
		scores[i] += card->value;
		free(card);
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
		fillStackWithRandomNumbers();
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
