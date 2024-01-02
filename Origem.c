#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "lab.h"
#include <stdlib.h>
#include <time.h>

#define SIZE_DECK 81
#define SIZE_HAND 7

typedef struct card
{
	char naipe;
	int color;

}card;

typedef struct deck
{
	card cartas[SIZE_DECK];
	int sz;

}deck;

typedef struct hand
{
	card cartas[SIZE_HAND];
	int sz;

}hand;

typedef struct player
{
	char name[20];
	hand mao;
}player;

void trocar(card *n1, card *n2)
{
	card temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void baralhar_deck(deck* baralho_shuffle)
{
	int i, j;
	for (i = 0; i < SIZE_DECK; i++)
	{
		j = rand() % 81;
		trocar(&baralho_shuffle->cartas[i], &baralho_shuffle->cartas[j]);
	}
}

void CriarBaralho(deck* baralho)
{
	baralho->sz = 0;
	int i;
	for (int i = 0; i < 18; i++)
	{
		baralho->cartas[baralho->sz + i].naipe = 'H';
		//baralho.cartas[baralho.sz + 1].color = 1;
	}
	baralho->sz += 18;
	for (int i = 0; i < 17; i++)
	{
		baralho->cartas[baralho->sz + i].naipe = 'T';
		//baralho.cartas[baralho.sz + 1].color = 1;
	}
	baralho->sz += 18;
	for (int i = 0; i < 13; i++)
	{
		baralho->cartas[baralho->sz + i].naipe = 'W';
		//baralho.cartas[baralho.sz + 1].color = 1;
	}
	baralho->sz += 13;
	for (int i = 0; i < 15; i++)
	{
		baralho->cartas[baralho->sz + i].naipe = 'F';
		//baralho.cartas[baralho.sz + 1].color = 1;
	}
	baralho->sz += 15;
	for (int i = 0; i < 15; i++)
	{
		baralho->cartas[baralho->sz + i].naipe = 'L';
		//baralho.cartas[baralho.sz + 1].color = 1;
	}
	baralho->sz += 15;
	for (int i = 0; i < 3; i++)
	{
		baralho->cartas[baralho->sz + i].naipe = 'P';
		//baralho.cartas[baralho.sz + 1].color = 1;
	}
	baralho->sz += 3;
}

void ResetPlayer(player* jogador)
{
	int i;
	for (i = 0; i < SIZE_HAND; i++)
	{
		jogador->mao.cartas[i].naipe = ' ';
	}
	jogador->mao.sz = 0;

}

void DistribuirCartas(deck* baralho, player* jogador)
{
	int i;
	for (i = 0; i < 7; i++)
	{
		jogador->mao.cartas[i].naipe = baralho->cartas[baralho->sz - 2 - i].naipe;
		//p1.mao.cartas[i].color = baralho.cartas[baralho.sz - 2 - i].color;
	}
	baralho->sz -= 7;
	jogador->mao.sz += 7;
}

void DarCarta(player* jogador, player* mesa)
{
	int i, card;
	//card = rand() % jogador->mao.sz;
	scanf("%d", &card);
	mesa->mao.cartas[mesa->mao.sz].naipe = jogador->mao.cartas[card].naipe;
	for (i = card-1; i < jogador->mao.sz - 1; i++)
	{
		jogador->mao.cartas[i].naipe = jogador->mao.cartas[i + 1].naipe;
	}
	mesa->mao.sz++;
	jogador->mao.sz--;
}

void ShowHand(player* jogador)
{
	int i;
	char carta;
	printf("Hand: \n");
	for (i = 0; i < jogador->mao.sz; i++)
	{
		carta = jogador->mao.cartas[i].naipe;
		printf("%d- %c\n", i+1, carta);
	}
	printf("\n");
}

void ShowTable(player* mesa)
{
	int i;
	char carta;
	printf("Table: \n");
	for (i = 0; i < mesa->mao.sz; i++)
	{
		carta = mesa->mao.cartas[i].naipe;
		printf("%d- %c   ", i + 1, carta);
	}
	printf("\n\n");
}

void Bet(player* jogador1, player* jogador2, char* bet1, char* bet2)
{
	int bet, x, i, j;
	char racers[6] = {'H', 'T', 'W', 'F', 'L', '\0'};
	/*for (i = 0; i < 2; i++)
	{
		x = rand() % (5-i);
		bet1[i] = racers[x];
		for(j = x; j < sizeof(racers) / sizeof(racers[0]); j++)
		{ 
			racers[j] = racers[j + 1];
		}
	}
	
	for (i = 0; i < 2; i++)
	{
		x = rand() % (5 - i);
		bet2[i] = racers[x];
		for (j = x; j < sizeof(racers) / sizeof(racers[0]); j++)
		{
			racers[j] = racers[j + 1];
		}
	}*/

	ShowHand(jogador1);
	printf("Player 1, choose your bet.\n");
	scanf("%d", &bet);
	x = rand() % 7;
	
	bet1[3] = jogador1->mao.cartas[bet].naipe;
	for (i = bet - 1; i < jogador1->mao.sz - 1; i++)
	{
		jogador1->mao.cartas[i].naipe = jogador1->mao.cartas[i + 1].naipe;
	}
	bet2[3] = jogador2->mao.cartas[x].naipe;
	for (i = x - 1; i < jogador2->mao.sz - 1; i++)
	{
		jogador2->mao.cartas[i].naipe = jogador2->mao.cartas[i + 1].naipe;
	}
	jogador1->mao.sz--;
	jogador2->mao.sz--;


}


int main()
{
	int game_end = 0;
	int menu_option;
	int i, x;
	int round;
	char aposta1[3];
	char aposta2[3];
	deck baralho;
	player p1, p2, table;

	srand((unsigned int)time(NULL));

	ResetPlayer(&p1);
	ResetPlayer(&p2);
	ResetPlayer(&table);
	CriarBaralho(&baralho);
	baralhar_deck(&baralho);
	DistribuirCartas(&baralho, &p1);
	DistribuirCartas(&baralho, &p2);

	struct hare
	{
		int position;
		char letter;
	};

	struct tortoise
	{
		int position;
		char letter;
	};

	struct wolf
	{
		int position;
		char letter;
	};

	struct fox
	{
		int position;
		char letter;
	};
	
	struct lamb
	{
		int position;
		char letter;
	};
	

	do
	{
		printf("1- New Game\n\n");
		printf("2- Load Game\n\n");
		printf("3- Game Rules\n\n");
		printf("4- Exit\n\n");
		scanf("%d", &menu_option);
		switch (menu_option)
		{
		case 1:
			Bet(&p1, &p2, &aposta1, &aposta2);
			printf("%c", aposta1);
			//ShowTable(&table);
			//ShowHand(&p1);
			//DarCarta(&p1, &table);
			//ShowTable(&table);
			//ShowHand(&p1);
			break;

		case 2:
			printf("\nYou chose option 2\n\n");
			break;

		case 3:
			printf("\nYou chose option 3\n\n");
			break;

		case 4:
			printf("\nYou chose option 4\n\n");
			game_end = 1;
			break;
		}
	} while (game_end != 1);


	system("PAUSE");
	return 0;
}
