#include <iostream>
#include <windows.h>
#include <conio.h> // для _getch 
#include <string>
#include <vector>

using namespace std;

const int N = 10;// размер массива
const int Num_Ships = 10;// колличество кораблей

int Ships_id = 1;
int Ships[11] = { 0 };

struct ship {
	int x = 0, y = 0; // кординаты цели

	int temp_x = x;
	int temp_y = y;

	int dir = 0; // направление
	int temp_dir = dir;

	int map_player[N][N] = { 0 }; // поле игрока

	int mask_player[N][N] = { 0 };// туман войны игрока

	int ships_player[Num_Ships + 1] = { 0 }; // коробли игрока

	int semm_player = 0; // остались ли у игрока корабли

	bool player = 1; // выйграл ли игрок

	bool win_player = 0; // остались ли игрока корабли
};
// передвижения курсора
void gotox(short x, short y)
{//переставления курсора в заданные кординаты в консольном окне
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
//увеличение x и y взависимости от направления
void increase_x_y(int& x, int& y, int& dir)
{
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
//проверка возможности постановки коробля
bool ship_position_check(int x, int y, int dir, int map[N][N], int size_ship)
{
	bool setting_is_possible = 1;
	for (int i = 0; i < size_ship; i++) {
		if (x < 0 || y < 0 || x >= N || y >= N) {
			setting_is_possible = 0;
			break;
		}
		if (map[x][y] >= 1) {
			setting_is_possible = 0;
			break;
		}
		if (y < N - 1) {
			if (map[x][y + 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (y > 0) {
			if (map[x][y - 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1) {
			if (map[x + 1][y] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1 && y < N - 1) {
			if (map[x + 1][y + 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x < N - 1 && y > 0) {
			if (map[x + 1][y - 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0) {
			if (map[x - 1][y] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0 && y < N - 1) {
			if (map[x - 1][y + 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		if (x > 0 && y > 0) {
			if (map[x - 1][y - 1] >= 1) {
				setting_is_possible = 0;
				break;
			}
		}
		increase_x_y(x, y, dir);
	}
	return setting_is_possible;
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
			increase_x_y(x, y, dir);
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
		increase_x_y(x, y, dir);
	}
	return in_map;
}
//проверка возможности постановки коробля при ручной постанки
bool set_ship(int map[N][N], int x, int y, int dir, int size_ship) {
	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = 1;// пройдина ли проверка
	//проверка возможности постановки коробля
	setting_is_possible = ship_position_check(x, y, dir, map, size_ship);
	if (setting_is_possible == 1) {
		x = temp_x;
		y = temp_y;
		for (int i = 0; i < size_ship; i++) {//запись коробля в массив
			map[x][y] = Ships_id;
			increase_x_y(x, y, dir);
			x = x > 9 ? 9 : x;
			y = y > 9 ? 9 : y;
		}
		Ships[Ships_id] = size_ship;
		Ships_id += 1;
	}

	return setting_is_possible;
}
// рандомная расстановка короблей
void set_rand_ships(int map[N][N], int size_ship, int ships_id)
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
		setting_is_possible = ship_position_check(x, y, dir, map, size_ship);
		if (setting_is_possible == 1) {
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < size_ship; i++) {//запись коробля в массив
				map[x][y] = ships_id;
				increase_x_y(x, y, dir);
				//защита от переполнения
				x = x > 9 ? 9 : x;
				y = y > 9 ? 9 : y;
			}
			cout_ship += 1;
		}
	}
}
//прорисовка полей
void map_show(int map[N][N], int mask[N][N], string gemer, bool usemask)
{
	cout << gemer << endl;
	cout << "  ";
	for (int i = 0; i < N; i++)
		cout << i << " ";
	cout << endl;
	for (int i = 0; i < N; i++) {//прорисовка
		cout << i;
		for (int j = 0; j < N; j++) {
			//if (mask[j][i] == 1 || usemask == 0) {
			if (map[j][i] == 0)
				cout << " -";
			else if (map[j][i] == -1)
				cout << " O";
			else if (map[j][i] == -2)
				cout << " *";
			else
				cout << " X";
			//}
			//else
				//cout << "  ";

		}
		cout << endl;
	}
	cout << endl;
}
// выстрел
int shot(int map[N][N], int mask[N][N], int ships[Num_Ships + 1], int x, int y)
{
	int result = 0; // куда попали убит ранен или промах
	if (map[x][y] == -1 || map[x][y] == -2)
		result = 3;
	else if (map[x][y] >= 1) {
		ships[map[x][y]] --;
		if (ships[map[x][y]] <= 0)
			result = 2; // убил
		else
			result = 1; // попал
		map[x][y] = -1; 
	}
	else
		map[x][y] = -2; //промах
	mask[x][y] = 1;
	return result;
}
// заполнение массива с короблями
void array_filling(int ships[Num_Ships + 1])
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
// расстановка кораблей вручную
void manual_placement_of_ships(string& gemer, int map_human[N][N], int mask_human[N][N])
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
			x += 2;
			break;
		case 115:// s вниз
			y++;
			break;
		case 97:// a влево
			x -= 2;
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

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	ship Ship_human;
	ship Ship_computer;

	int size_ship = 4; // размер коробля
	int ch = 0; // какая нажата клавиша
	int amount_ship = 0;// количество кораблей на поле

	int resultshot = 0; // попадание в корабль

	string gemer = "Поле Игрока";
	string gemer2 = "Поле Компьютера";

	bool turn = 1; // 1 ходит человек

	// заполнение массива с короблями человека
	array_filling(Ship_human.ships_player);

	// заполнение массива с короблями бота
	array_filling(Ship_computer.ships_player);

	// расстановка кораблей человека вручную
	manual_placement_of_ships(gemer, Ship_human.map_player, Ship_human.mask_player);

	// расстановка кораблей бота рандомно
	for (int i = 1; i <= Num_Ships; i++)
		set_rand_ships(Ship_computer.map_player, Ship_computer.ships_player[i], i);

	// отвечает за стрельбу пока не будет промах
	while (Ship_computer.win_player == false && Ship_human.win_player == false) {
		do {
			map_show(Ship_human.map_player, Ship_human.mask_player, gemer, 0);
			map_show(Ship_computer.map_player, Ship_computer.mask_player, gemer2, 1);

			if (turn == 1) {
				do {
					cout << "Введите кординаты цели: ";
					cin >> Ship_human.x >> Ship_human.y;
					system("cls");
					map_show(Ship_human.map_player, Ship_human.mask_player, gemer, 0);
					map_show(Ship_computer.map_player, Ship_computer.mask_player, gemer2, 1);
				} while (Ship_human.x > 9 || Ship_human.y > 9 || Ship_human.x < 0 || Ship_human.y < 0);

				resultshot = shot(Ship_computer.map_player, Ship_computer.mask_player, Ship_computer.ships_player, Ship_human.x, Ship_human.y);
				if (resultshot == 2) {
					cout << "Убил" << endl;
					Sleep(1000);
					system("cls");
					for (int i = 1; i <= Num_Ships; i++) {
						if (Ship_computer.ships_player[i] != 0) {
							Ship_human.player = 0;
							break;
						}
					}
					if (Ship_human.player == 1)
						Ship_human.win_player = 1;
					Ship_human.player = Ship_human.semm_player <= 0 ? 1 : 0;
				}
				else if (resultshot == 1) {
					cout << "Ранен" << endl;
					Sleep(1000);
					system("cls");
				}
				else {
					cout << "Промах";
					Sleep(1000);
					system("cls");
				}
			}
			else {
				cout << "Ход компьютера: ";
				Sleep(1000);

				int mode = 0; // режим стрельбы

				vector <int> dirs = { 3, 2, 1, 0 };
				// режим 1, когда алгоритм действует случаным образом 
				if (mode == 0) {
					do {
						Ship_computer.x = rand() % N;
						Ship_computer.y = rand() % N;
						resultshot = shot(Ship_human.map_player, Ship_human.mask_player, Ship_human.ships_player, Ship_human.x, Ship_human.y);
					} while (Ship_human.map_player[Ship_computer.x][Ship_computer.y] == -2);
					if (resultshot == 1) {
						mode = 1;
						Ship_computer.temp_x = Ship_computer.x;
						Ship_computer.temp_y = Ship_computer.y;
						cout << "Ранен" << endl;

					}
					else if (resultshot == 2) {
						cout << "Убит";
					}
					else
					cout << "Промах" << endl;
				}
				// режим 2
				else if (mode == 1) {
					// блок 1 изменяе x пока не будет осуществлён промах или не упрётся в границу
					bool cheng_dir = 0; // нужно ли менять направление
					// стрельба влево
					if (Ship_computer.dir == 0) {
						if (Ship_computer.x > 0)
							Ship_computer.x--;
						else
							cheng_dir = 1;
					}
					// стрельба вправо
					else if (Ship_computer.dir == 1) {
						if (Ship_computer.x < N - 1)
							Ship_computer.x++;
						else
							cheng_dir = 1;
					}
					// стрельба вверх
					else if (Ship_computer.dir == 2) {
						if (Ship_computer.y > 0)
							Ship_computer.y--;
						else
							cheng_dir = 1;
					}
					// стрельба вниз
					else if (Ship_computer.dir == 3) {
						if (Ship_computer.y < N - 1)
							Ship_computer.y++;
						else
							cheng_dir = 1;
					}

					if (cheng_dir == 1) {
						if (!dirs.empty()) {
							Ship_computer.dir = dirs[dirs.size() - 1];
							dirs.pop_back();
						}
						Ship_computer.x = Ship_computer.temp_x;
						Ship_computer.y = Ship_computer.temp_y;
						continue;

					}
					resultshot = shot(Ship_human.map_player, Ship_human.mask_player, Ship_human.ships_player, Ship_human.x, Ship_human.y);
					// блок 2 проверка состояния цели
					if (resultshot == 1) {

						cout << "Ранен" << endl;
						Sleep(1000);
					}
					else if (resultshot == 2) {
						for (int i = 1; i <= Num_Ships; i++) {
							if (Ship_human.ships_player[i] != 0) {
								Ship_computer.player = 0;
								break;
							}
						}
						if (Ship_computer.player == 1)
							Ship_computer.win_player = 1;
						cout << "Убит" << endl;
						mode = 0;
						Sleep(1000);
					}
					else {
						Ship_human.map_player[Ship_computer.x][Ship_computer.y] = -2;
						if (!dirs.empty()) {
							Ship_computer.dir = dirs[dirs.size() - 1];
							dirs.pop_back();
						}
						Ship_computer.x = Ship_computer.temp_x;
						Ship_computer.y = Ship_computer.temp_y;
						cout << "Промах" << endl;
						Sleep(1000);
					}
				}
			}
			system("cls");
		} while (resultshot != 0);
		turn = turn == 0 ? 1 : 0;
	}
	map_show(Ship_human.map_player, Ship_human.mask_player, gemer, 0);
	map_show(Ship_computer.map_player, Ship_computer.mask_player, gemer2, 1);
	if (Ship_human.win_player == true) {
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
