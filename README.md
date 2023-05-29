# Sea-battle

```c++
struct Player {

	int x = 0; // ��������� ����
	int y = 0; // ��������� ����
	int dir = 0; // �����������
	int temp_dir = dir;

	int map_player[N][N] = { 0 }; // ���� ������

	int mask_player[N][N] = { 0 };// ����� ����� ������

	int ships_player[Num_Ships + 1] = { 0 }; // ������� ������

	int semm_player = 0; // �������� �� � ������ �������

	bool player = 1; // ������� �� �����

	bool win_player = 0; // �������� �� ������ �������
};
```
��� ��������� �������� ��� ������ ���������� ��� ������

```c++
void gotox(short x, short y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
```
��� ������� ������� �� ������������ ����������� ������� � �������

```c++
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
```
��� ������� �������� �� ���������� x � y ������������ �� �����������

```c++
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
```
��� ������� �������� �� �������� ����������� ���������� �������

```c++
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
```
��� ������� �������� �� ��������� �� ����������� �������� �� ����

```c++
bool ship_in_map(int x, int y, int dir, int size_ship)
{
	bool in_map = 1;// �������� �� ��������
	for (int i = 0; i < size_ship; i++) {
		if (x < 0 || y < 0 || x >= N || y >= N) {
			in_map = 0;
			break;
		}
		increase_x_y(x, y, dir);
	}
	return in_map;
}
```
��� ������� ���������� ��������� �� ������� � �������� �����

```c++
bool set_ship(int map[N][N], int x, int y, int dir, int size_ship) {
	int temp_x = x;
	int temp_y = y;
	bool setting_is_possible = 1;// �������� �� ��������
	//�������� ����������� ���������� �������
	setting_is_possible = ship_position_check(x, y, dir, map, size_ship);
	if (setting_is_possible == 1) {
		x = temp_x;
		y = temp_y;
		for (int i = 0; i < size_ship; i++) {//������ ������� � ������
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
```
��� ������� �������� �� �������� ����������� ���������� ������� ��� ������ ��������

```c++
void set_rand_ships(int map[N][N], int size_ship, int ships_id)
{
	int x, y;
	int dir = 0;//�����������
	int cout_ship = 0;
	int temp_x = 0;
	int temp_y = 0;
	while (cout_ship < 1) {
		x = rand() % N;//��������� �������
		y = rand() % N;//��������� �������
		temp_x = x;
		temp_y = y;
		dir = rand() % 4;//�������� �����������
		bool setting_is_possible = 1;// �������� �� ��������
		//�������� ����������� ���������� �������
		setting_is_possible = ship_position_check(x, y, dir, map, size_ship);
		if (setting_is_possible == 1) {
			x = temp_x;
			y = temp_y;
			for (int i = 0; i < size_ship; i++) {//������ ������� � ������
				map[x][y] = ships_id;
				increase_x_y(x, y, dir);
				//������ �� ������������
				x = x > 9 ? 9 : x;
				y = y > 9 ? 9 : y;
			}
			cout_ship += 1;
		}
	}
}
```
��� ������� �������� �� ��������� ����������� ��������

```c++
void map_show(int map[N][N], int mask[N][N], string gemer, bool usemask)
{
	cout << gemer << endl;
	cout << "  ";
	for (int i = 0; i < N; i++)
		cout << i << " ";
	cout << endl;
	for (int i = 0; i < N; i++) {//����������
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
				cout << " -";

		}
		cout << endl;
	}
	cout << endl;
}
```
��� ������� �������� �� ���������� �����

```c++
int shot(int map[N][N], int mask[N][N], int ships[Num_Ships + 1], int x, int y)
{
	int result = 0; // ���� ������ ���� ����� ��� ������
	if (map[x][y] == -1 || map[x][y] == -2)
		result = 3;
	else if (map[x][y] >= 1) {
		ships[map[x][y]] --;
		if (ships[map[x][y]] <= 0)
			result = 2; // ����
		else
			result = 1; // �����
		map[x][y] = -1;
	}
	else
		map[x][y] = -2; //������
	mask[x][y] = 1;
	return result;
}
```
��� ������� �������� �� �������� ��������� � ����

```c++
void array_filling(int ships[Num_Ships + 1])
{
	int amount_ship = 0;
	int size_ship = 4;
	// ���������� ������� � ���������
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
```
��� ������� �������� �� ���������� ������� � ���������

```c++
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
		// �������� ���������� ��� �����������
		switch (ch) {
		case 100:// d ������
			x += 2;
			break;
		case 115:// s ����
			y++;
			break;
		case 97:// a �����
			x -= 2;
			break;
		case 119:// w �����
			y--;
			break;
		case 114:// r �������
			dir = dir == 0 ? 1 : 0;
			break;
		case 13:// enter ��������� �������
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
```
��� ������� �������� �� ������ ����������� ��������