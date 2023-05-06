#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <string>
#include <fstream>
#include <locale>
#include <vector>

using namespace std;

const int N = 10;
const int Num_Ships = 10;

int Ships_id = 1;
int Ships[11] = { 0 };
int Ships2[11] = { 0 };
//проверка возможности постановки коробля
bool ship_position_check(int x, int y, vector<vector<int> > map)
{
	bool setting_is_possible = 1;
	if (x < 0 || y < 0 || x >= N || y >= N) {
		setting_is_possible = 0;
	}
	if (map[x][y] >= 1) {
		setting_is_possible = 0;
	}
	if (y < N - 1) {
		if (map[x][y + 1] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (y > 0) {
		if (map[x][y - 1] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (x < N - 1) {
		if (map[x + 1][y] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (x < N - 1 && y < N - 1) {
		if (map[x + 1][y + 1] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (x < N - 1 && y > 0) {
		if (map[x + 1][y - 1] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (x > 0) {
		if (map[x - 1][y] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (x > 0 && y < N - 1) {
		if (map[x - 1][y + 1] >= 1) {
			setting_is_possible = 0;
		}
	}
	if (x > 0 && y > 0) {
		if (map[x - 1][y - 1] >= 1) {
			setting_is_possible = 0;
		}
	}
	return setting_is_possible;
}
// передвижения курсора
void gotox(short x, short y)
{//переставления курсора в заданные кординаты в консольном окне
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
// растановка коробля на поле
void ship_show(int x, int y, int dir, int size_ship)
{
	for (int i = 0; i < size_ship; i++) {
		gotox(x + 2, y + 2);
		cout << "#";
		if (dir == 0) {
			switch (dir) {
			case 0:
				x += 2;
				break;
			case 1:
				y++;
				break;
			case 2:
				x += 2;
				break;
			case 3:
				y--;
				break;
			}
		}
		else {
			switch (dir) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
	}
}
//находится ли корабль в пределах карты
bool ship_in_map(int x, int y, int dir, int size_ship)
{
	bool in_map = 1;// пройдина ли проверка
	for (int i = 0; i < size_ship; i++) {
		if (x < 0 || y < 0 || x >= N || y >= N) {
			in_map = 0;
			break;
		}
		switch (dir) {
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	return in_map;
}
//проверка возможности постановки коробля при ручной постанки
bool set_ship(vector<vector<int> > map, int x, int y, int dir, int size_ship)
{
	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = 1;// пройдина ли проверка
	//проверка возможности постановки коробля
	for (int i = 0; i < size_ship; i++) {
		setting_is_possible = ship_position_check(x, y, map);

		switch (dir) {
		case 0:
			x++;
			break;
		case 1:
			y++;
			break;
		case 2:
			x--;
			break;
		case 3:
			y--;
			break;
		}
	}
	if (setting_is_possible == 1) {
		x = temp_x;
		y = temp_y;
		for (int i = 0; i < size_ship; i++) {//запись коробля в массив
			map[x][y] = Ships_id;
			switch (dir) {
			case 0:
				x++;
				break;
			case 1:
				y++;

				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
			x = x > 9 ? 9 : x;
			y = y > 9 ? 9 : y;
		}
		Ships[Ships_id] = size_ship;
		Ships_id += 1;
	}

	return setting_is_possible;
}
// рандомная расстановка короблей
void set_rand_ships(vector<vector<int> > map, int size_ship, int ship_id)
{
	int x, y;
	int dir = 0;//направление
	int cout_ship = 0;
	int temp_x = 0;
	int temp_y = 0;
	while (cout_ship < 1) {
		x = rand() % N;//первичная позиция
		y = rand() % N;//первичная позиция
		temp_x = x;
		temp_y = y;
		dir = rand() % 4;//генератр напрваления
		bool setting_is_possible = 1;// пройдина ли проверка
		//проверка возможности постановки коробля
		for (int i = 0; i < size_ship; i++) {
			setting_is_possible = ship_position_check(x, y, map);

			switch (dir) {
			case 0:
				x++;
				break;
			case 1:
				y++;
				break;
			case 2:
				x--;
				break;
			case 3:
				y--;
				break;
			}
		}
		if (setting_is_possible == 1) {
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < size_ship; i++) {//запись коробля в массив
				map[x][y] = ship_id;
				switch (dir) {
				case 0:
					x++;

					break;
				case 1:
					y++;

					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
				}
				//защита от переполнения
				x = x > 9 ? 9 : x;
				y = y > 9 ? 9 : y;
			}
			cout_ship += 1;
		}
	}
}
//прорисовка полей
void map_show(vector<vector<int> > map, vector<vector<int> > mask, string gemer, bool usemask)
{
	cout << gemer << endl;
	cout << "  ";
	for (int i = 1; i <= N; i++)
		cout << i << " ";
	cout << endl;
	for (int i = 0; i < N; i++) {//прорисовка
		cout << i;
		for (int j = 0; j < N; j++) {
			if (mask[j][i] == 1 || usemask == 0) {
				if (map[j][i] == 0)
					cout << " -";
				else if (map[j][i] == -1)
					cout << " O";
				else if (map[j][i] == -2)
					cout << " *";
				else
					cout << " X";
			}
			else
				cout << "  ";

		}
		cout << endl;
	}
	cout << endl;
}
// выстрел
int shot(vector<vector<int> > map, vector<vector<int> > mask, vector<int> ships_human, int x, int y)
{
	int result = 0; // куда побали убит ранен или промах
	if (map[x][y] >= 1) {
		ships_human[map[x][y]] -= 1;
		if (ships_human[map[x][y]] <= 0)
			result = 2;
		else
			result = 1;
		map[x][y] = -1;
	}
	else
		map[x][y] = -2;
	mask[x][y] = 1;
	return result;
}
// заполнение массива с короблями
void array_filling(vector<int> ships)
{
	int amount_ship = 0;
	int size_ship = 4;
	// заполнение массива с короблями
	for (int i = 1; i <= Num_Ships; i++) {
		switch (size_ship) {
		case 4:
			if (amount_ship == 0)
				amount_ship = 1;
			if (amount_ship > 0)
				amount_ship--;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		case 3:
			if (amount_ship == 0)
				amount_ship = 2;
			if (amount_ship > 0)
				amount_ship--;
			ships[i] = size_ship;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		case 2:
			if (amount_ship == 0)
				amount_ship = 3;
			if (amount_ship > 0)
				amount_ship--;
			ships[i] = size_ship;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		case 1:
			if (amount_ship == 0)
				amount_ship = 4;
			if (amount_ship > 0)
				amount_ship--;
			ships[i] = size_ship;
			if (amount_ship == 0) {
				ships[i] = size_ship;
				size_ship--;
			}
			break;
		}
	}
}
// расстановка кораблей человека вручную
void manual_placement_of_ships(string gemer, vector<vector<int>> map_human, vector<vector<int>> mask_human)
{
	int size_ship = 4;
	int amount_ship = 0;
	int ch;
	int x = 0;
	int y = 0;
	int dir = 0;
	int temp_x = x;
	int temp_y = y;
	int temp_dir = dir;
	while (size_ship != 0) {
		map_show(map_human, mask_human, gemer, 0);
		ship_show(x, y, dir, size_ship);
		ch = _getch();
		// изменить координаты или направление
		switch (ch) {
		case 100:// d вправо
			x++;
			x++;
			break;
		case 115:// s вниз
			y++;
			break;
		case 97:// a влево
			x--;
			x--;
			break;
		case 119:// w вверх
			y--;
			break;
		case 114:// r поворот
			dir = dir == 0 ? 1 : 0;
			break;
		case 13:// enter установка коробля
			if (set_ship(map_human, x / 2, y, dir, size_ship)) {
				x = 0;
				y = 0;
				dir = 0;
				switch (size_ship) {
				case 4:
					amount_ship = amount_ship == 0 ? 1 : 0;
					if (amount_ship == 0)
						amount_ship = 1;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				case 3:
					if (amount_ship == 0)
						amount_ship = 2;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				case 2:
					if (amount_ship == 0)
						amount_ship = 3;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				case 1:
					if (amount_ship == 0)
						amount_ship = 4;
					if (amount_ship > 0)
						amount_ship--;
					if (amount_ship == 0)
						size_ship--;
					break;
				}
			}
			break;
		}
		if (!ship_in_map(x / 2, y, dir, size_ship)) {
			x = temp_x;
			y = temp_y;
			dir = temp_dir;
		}
		system("cls");
	}
}
// расстановка кораблей рандомно
void random_placement_of_ships(vector<vector<int>> map, vector<int> ships)
{
	for (int i = 1; i <= Num_Ships; i++)
		set_rand_ships(map, ships[i], i);
}

int main()
{
	setlocale(LC_CTYPE, "Russian");

	vector<vector<int>> map_human(N, vector<int>(N)); // поле человека
	vector<vector<int>> map_computer(N, vector<int>(N)); // поле бота

	vector<vector<int>> mask_human(N, vector<int>(N)); // туман войны человека
	vector<vector<int>> mask_computer(N, vector<int>(N)); // туман войны бота

	vector<int> ships_human(Num_Ships + 1); // коробли человека
	vector<int> ships_computer(Num_Ships + 1); // коробли бота

	int x = 0, y = 0; // кординаты цели
	int dir = 0; // направление
	int size_ship = 4; // размер коробля
	int ch = 0; // какая нажата клавиша
	int amount_ship = 0;// количество кораблей на поле

	int resultshot = 0; // попадание в корабль

	int semmbot = 0; // остались ли у бота корабли
	int semmhuman = 0; // остались ли у человека корабли

	int temp_x = x;
	int temp_y = y;
	int temp_dir = dir;

	string gemer = "Поле Игрока";
	string gemer2 = "Поле Компьютера";

	bool turn = 1; // 1 ходит человек

	bool computer = 1; // выйграл ли бот
	bool human = 1; // выйграл ли человек

	bool wincomputer = 0; // остались ли бота корабли
	bool winhuman = 0; // остались ли человека корабли

	array_filling(ships_human);
	array_filling(ships_computer);

	// расстановка кораблей человека вручную
	manual_placement_of_ships(gemer, map_human, mask_human);

	// расстановка кораблей бота рандомно
	random_placement_of_ships(map_computer, ships_computer);

	// отвечает за стрельбу пока не будет промах
	while (wincomputer == false && winhuman == false) {
		do {
			map_show(map_human, mask_human, gemer, 0);
			map_show(map_computer, mask_computer, gemer2, 1);

			if (turn == 1) {
				do {
					cout << "Введите кординаты цели: ";
					cin >> x >> y;
					system("cls");
					map_show(map_human, mask_human, gemer, 0);
					map_show(map_computer, mask_computer, gemer2, 1);
				} while (x > 9 || y > 9 || x < 0 || y < 0);

				resultshot = shot(map_computer, mask_computer, ships_computer, x, y);
				if (resultshot == 2) {
					cout << "Убил" << endl;
					Sleep(1000);
					system("cls");
					for (int i = 1; i <= Num_Ships; i++) {
						if (ships_computer[i] != 0) {
							human = 0;
							break;
						}
					}
					if (human == 1)
						winhuman = 1;
					human = semmhuman <= 0 ? 1 : 0;
				}
				else if (resultshot == 1) {
					cout << "Попал" << endl;
					Sleep(5000);
					system("cls");
				}
				else {
					cout << "Промах";
					Sleep(5000);
					system("cls");
				}
			}
			else {
				cout << "Ход компьютера: ";
				Sleep(5000);
				do {
					x = rand() % N;
					y = rand() % N;
				} while (map_human[x][y] < 0);
				resultshot = shot(map_human, mask_human, ships_human, x, y);

				if (resultshot == 2) {
					for (int i = 1; i <= Num_Ships; i++) {
						if (ships_human[i] != 0) {
							computer = 0;
							break;
						}
					}
					if (computer == 1)
						wincomputer = 1;
					cout << "Убил" << endl;
					Sleep(1000);
				}
				else if (resultshot == 1) {
					cout << "Попал" << endl;
					Sleep(1000);
				}
				else {
					cout << "Промах";
					Sleep(1000);
				}
			}
			system("cls");
		} while (resultshot != 0);
		turn = turn == 0 ? 1 : 0;
	}

	map_show(map_human, mask_human, gemer, 0);
	map_show(map_computer, mask_computer, gemer2, 1);
	if (winhuman == true) {
		cout << "Вы победили" << endl;
		Sleep(1000);
	}
	else {
		cout << "Вы проиграли" << endl;
		Sleep(1000);
	}
	system("pause");
	return 0;
}
