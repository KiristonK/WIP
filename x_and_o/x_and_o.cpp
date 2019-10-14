// x_and_o.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <time.h>

#define x  0
#define o 1

void computerDecision(char**, int);
void playerMove(char**, int);

int main()
{
	srand(time(NULL));
	BOOL gameOver = FALSE;

	char playerName[256];
	char** playField =	{'-','-','-',
						 '-','-','-',
						 '-','-','-'};
	int charakter;
    std::cout << "Hello!\nEnter your name please : ";
	std::cin >> playerName;

	charakter = 0 - rand() % 1;

	while (!gameOver) {
		if (charakter == x) {
			playerMove(playField, charakter);
			computerDecision(**playField, charakter);
		}
		else {
			computerDecision(**playField, charakter);
			playerMove(**playField, charakter);
		}
		system("cls");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << playField[i][j] << "\t";
			}
			std::cout << "\n";
		}
	}
}

void computerDecision(char** playField, int charakter) {
	srand(time(NULL));
	if (charakter == x) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (playField[i][j] == 'x') {
					if (playField[i][j+1] == 'x') {
						if (playField[i + 1][j] == 'x') {
							if (playField[i + 1][j + 1] == 'x') {
								continue;
							}
						}
						else {

						}
					}
					else {
						if (playField[i][j + 2] == 'x') {

						}
					}
				}
				else {
					if (playField[i][j + 1] == 'x') {
						if (playField[i + 1][j] == 'x') {
							if (playField[i + 1][j + 1] == 'x') {
								continue;
							}
						}
					}
				}
			}
		}
	}
	else {

	}
}
