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
	int sort = choose_sort(); // выбор пользователем сортировки победителей
	Sleep(1000); system("cls");

	int charactersCount = rand() % 6 + 10;	// рандомайзинг количества персонажей (от 10 до 15)
	vector<Create_Character> Characters = get_characters(charactersCount);	// создание вектора персонажей заданного размера
	int enemy = rand() % charactersCount;	// случайный выбор индека персонажа противника
	cout << " Номер персонажа противника: " << enemy + 1 << endl;	// вывод номера персонажа противника
	system("pause"); system("cls");

	for (int hero = 0; hero < charactersCount; hero++) {	// цикл перебора персонажей для сражения с противником
		if (hero == enemy) hero++;	// если выбран персонаж противника, то пропустить его
		cout << " Противник:\n";	// вывод персонажа противника и его характеристик
		COORD enemy_stats = get_CursorCoords();
		Characters[enemy].restore();	// обновление характеристик персонажа противника для каждого нового поединка
		Characters[enemy].get_stats(0);
		Sleep(500);
		cout << "\n Персонаж ";	cout << hero + 1 << ':' << endl;	// вывод героя и его характеристик
		COORD hero_stats = get_CursorCoords();
		Characters[hero].get_stats(0);
		Sleep(500);
		int enemy_stunLoading = Characters[enemy].get_stunDelay(),		hero_stunLoading = Characters[hero].get_stunDelay();
		int enemy_InStun = 0,											hero_InStun = 0;
		int time = 0;	// создание переменных для хранения времени оглушения и "перезарядки" у персонажей, а также переменной времени боя

		while (Characters[hero].health_point() != 0 && Characters[enemy].health_point() != 0) {
	// проводить поединок, пока здоровье одного из героев не будет равно нулю
			if (enemy_stunLoading == 0 && enemy_InStun == 0) {	// если оглушение у противника "заряжено" и противник не оглушён
				stunning(Characters, enemy_stunLoading, enemy_InStun, hero_stunLoading, hero_InStun, enemy, hero,
				"hero");	// то провести оглушение героя
			}
			if (hero_InStun == 0) {	// если герой не оглушён, то нанести урон противнику
				clear_Status(43, 14);
				Sleep(1000);
				beating_character(Characters, enemy, hero, enemy_stats, "enemy");
			}
			else {	// если герой оглушён, то вывести информацию об этом и время оглушения
				hero_InStun--;
				clear_Status(0, 13);
				cout << "\n Герой оглушён! Время оглушения: " << hero_InStun << " сек" << endl;
				Sleep(200);
			}
			if (enemy_stunLoading != 0)	enemy_stunLoading--;	// если противник оглушён, то уменьшить время его оглушения
			if (Characters[enemy].health_point() != 0) {	// противник продолжает бой, если его здоровье больше нуля
				if (hero_stunLoading == 0 && hero_InStun == 0) {	// если оглушение у героя "заряжено" и герой не оглушён
					stunning(Characters, enemy_stunLoading, enemy_InStun, hero_stunLoading, hero_InStun, enemy, hero,
					"enemy");	// то провести оглушение противника
				}
				if (enemy_InStun == 0) {	// если противник не оглушён, то нанести урон герою
					clear_Status(45, 15);
					Sleep(1000);
					beating_character(Characters, enemy, hero, hero_stats, "hero");
				}
				else {	// если противник оглушён, то вывести информацию об этом и время оглушения
					enemy_InStun--;
					clear_Status(0, 14);
					cout << "\n Противник оглушён! Время оглушения: " << enemy_InStun << " сек" << endl;
					Sleep(200);
				}
				if (hero_stunLoading != 0)	hero_stunLoading--;	// если герой оглушён, то уменьшить время его оглушения
			}
			time++;	// увеличить время поединка на одну условную секунду
		}
		clear_Status(43, 14);	// очистить строки информации о поединке
		clear_Status(45, 15);	// очистить строки информации о поединке
		if (Characters[hero].health_point() > Characters[enemy].health_point()) {	// если у героя осталось больше здоровья
			clear_Status(0, 13);													// то вывести информацию, что он победил
			cout << "\n Победитель: Персонаж " << hero + 1 << endl;					// в соответствии с выбранной сортировкой
			if (sort == 1) {
				Winners.push_back(make_pair(hero + 1, Characters[hero].health_point()));
			}
			else if (sort == 2) {
				Winners.push_back(make_pair(hero + 1, time));
			}
		}
		else {	// если у противника осталось больше здоровья, то вывести информацию соответствующее сообщение об этом
			cout << "\n Победитель: персонаж противника" << endl;
		}
		cout << " Время боя: " << time << " сек\n";	// вывод времени проведённого боя
		Sleep(3000);
		system("cls");	// очистить экран для вывода следующего поединка
	}
	system("cls");	bubble_sort(Winners);	// очистить экран и отсортировать героев-победителей
	if (Winners.size() == 0) {	// если победителей среди героев не оказалос, то вывести соответствующее сообщение
		cout << " Победителей не выявлено!\n";
	}
	cout << " Список победетилей:\n";	// вывести отсортированный список победителей на экран в соответствии с выбранной сортировкой
	printWinners(Winners, sort);
}
