/*------------------------------------------------------------------------------------------------------------------------------\
|					  Персонажи могут сражаться один против одного, и в командах по 3 персонажа.								|
|					Победой команды считается, когда все персонажи противоположной команды выбыли.								|
|		Каждого персонажа можно выбирать только один раз (не зависимо от того, в какой команде уже выбран этот персонаж).		|
\------------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <map>

#include "Extra1_head.h"

using namespace std;

/*------------------------------------------------------------------------------------------------------\
|		Оптимальный выбор 1х1.																			|
|	Дан набор персонажей с произвольно заданными характеристиками, не менее 10 персонажей.				|
|	Соперник выбрал одного персонажа. Выбрать среди оставшихся персонажей тех,							|
|	кто побеждает персонажа соперника с указанием времени сражения и процента оставшегося здоровья.		|
|	В случае если таких персонажей несколько, то ранжировать их по времени сражения						|
|	или проценту (от первоначального) оставшегося здоровья.												|
|	Вариант ранжирования (сортировки) задается как входной параметр.									|
\------------------------------------------------------------------------------------------------------*/

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned int)time(NULL));
	
	vector<pair<int,int>> Winners;
	int sort = choose_sort();
	Sleep(1000); system("cls");

	int charactersCount = rand() % 6 + 10;
	vector<Create_Character> Characters = get_characters(charactersCount);
	int enemy = rand() % charactersCount;
	cout << " Номер персонажа противника: " << enemy + 1 << endl;
	system("pause"); system("cls");

	for (int hero = 0; hero < charactersCount; hero++) {
		if (hero == enemy) hero++;
		cout << " Противник:\n";
		COORD enemy_stats = get_CursorCoords();
		Characters[enemy].restore();
		Characters[enemy].get_stats(0);
		Sleep(500);
		cout << "\n Персонаж ";	cout << hero + 1 << ':' << endl;
		COORD hero_stats = get_CursorCoords();
		Characters[hero].get_stats(0);
		Sleep(500);
		int enemy_stunLoading = Characters[enemy].get_stunDelay(),		hero_stunLoading = Characters[hero].get_stunDelay();
		int enemy_InStun = 0,											hero_InStun = 0;
		int time = 0;

		while (Characters[hero].health_point() != 0 && Characters[enemy].health_point() != 0) {
			if (enemy_stunLoading == 0 && enemy_InStun == 0) {
				stunning(Characters, enemy_stunLoading, enemy_InStun, hero_stunLoading, hero_InStun, enemy, hero,
				"hero");
			}
			if (hero_InStun == 0) {
				clear_Status(43, 14);
				Sleep(1000);
				beating_character(Characters, enemy, hero, enemy_stats, "enemy");
			}
			else {
				hero_InStun--;
				clear_Status(0, 13);
				cout << "\n Герой оглушён! Время оглушения: " << hero_InStun << " сек" << endl;
				Sleep(200);
			}
			if (enemy_stunLoading != 0)	enemy_stunLoading--;
			if (Characters[enemy].health_point() != 0) {
				if (hero_stunLoading == 0 && hero_InStun == 0) {
					stunning(Characters, enemy_stunLoading, enemy_InStun, hero_stunLoading, hero_InStun, enemy, hero,
					"enemy");
				}
				if (enemy_InStun == 0) {
					clear_Status(45, 15);
					Sleep(1000);
					beating_character(Characters, enemy, hero, hero_stats, "hero");
				}
				else {
					enemy_InStun--;
					clear_Status(0, 14);
					cout << "\n Противник оглушён! Время оглушения: " << enemy_InStun << " сек" << endl;
					Sleep(200);
				}
				if (hero_stunLoading != 0)	hero_stunLoading--;
			}
			time++;
		}
		clear_Status(43, 14);
		clear_Status(45, 15);
		if (Characters[hero].health_point() > Characters[enemy].health_point()) {
			clear_Status(0, 13);
			cout << "\n Победитель: Персонаж " << hero + 1 << endl;
			if (sort == 1) {
				Winners.push_back(make_pair(hero + 1, Characters[hero].health_point()));
			}
			else if (sort == 2) {
				Winners.push_back(make_pair(hero + 1, time));
			}
		}
		else {
			cout << "\n Победитель: персонаж противника" << endl;
		}
		cout << " Время боя: " << time << " сек\n";
		Sleep(3000);
		system("cls");
	}
	system("cls");	bubble_sort(Winners);
	if (Winners.size() == 0) {
		cout << " Победителей не выявлено!\n";
	}
	cout << " Список победетилей:\n";
	printWinners(Winners, sort);
}
