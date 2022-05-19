#ifndef EXTRA1_HEAD_H_
#define EXTRA1_HEAD_H_

#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class Create_Character {
	/*------------------------------------------------------------------------------------------\
	|	Персонаж обладает несколькими характеристиками:											|
	|		− Количество наносимого им урона противнику в секунду.								|
	|	Персонаж наносит урон все время, кроме времени, на которое он выведен из строя.			|
	|	Если персонаж наносит урон нескольким соперникам, указанный урон наносится каждому.		|
	|		− Количество соперников, которым наносится урон. Не более 3.						|
	|		− Здоровье персонажа.																|
	|	Наносимый урон вычитается из текущего здоровья,											|
	|	при достижении значения 0 персонаж выбывает.											|
	|		− Способность выводить из строя одного соперника.									|
	|	Задается двумя значениями в секундах:													|
	|		1) На которое соперник выводится из строя,											|
	|		2) Интервал вывода из строя.														|
	|	Второе как минимум в двое больше первого.												|
	|	Персонаж выходит из строя, как только удается это сделать.								|
	\------------------------------------------------------------------------------------------*/
public:
	void getAll_stats(int i, COORD coords) {
		if (i % 2 == 0) {
			get_stats(0);
		}
		else {
																	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coords.X += 5, coords.Y += 1 });
			cout << "\tЗдоровье: " << hp;							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coords.X, coords.Y += 1 });
			cout << "\tНаносимый урон: " << damage_perSecond;		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coords.X, coords.Y += 1 });
			cout << "\tКоличество соперников: " << enemies_count;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coords.X, coords.Y += 1 });
			cout << "\tВремя оглушения: " << stunTime << " сек";	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coords.X, coords.Y += 1 });
			cout << "\tПерезарядка: " << stunDelay << " сек" << endl;
		}
	}
	int damage(int damage_perSecond) {
		dynamic_hp = dynamic_hp - damage_perSecond;
		if (dynamic_hp < 0) return dynamic_hp = 0;
		return dynamic_hp;
	}
	void get_stats(bool check) {
		int health;
		if (check == 0) health = hp;
		else health = dynamic_hp;
		cout << "\tЗдоровье: " << health << "   " << endl;
		cout << "\tНаносимый урон: " << damage_perSecond << "   " << endl;
		cout << "\tКоличество соперников: " << enemies_count << endl;
		cout << "\tВремя оглушения: " << stunTime << " сек" << endl;
		cout << "\tПерезарядка: " << stunDelay << " сек" << endl;
	}
	int get_damage() {
		return damage_perSecond;
	}
	int get_stunTime() {
		return stunTime;
	}
	int get_stunDelay() {
		return stunDelay;
	}
	int restore() {
		dynamic_hp = hp;
		return dynamic_hp;
	}
	int health_point() {
		return dynamic_hp;
	}
private:
	int damage_perSecond = rand() % 11 + 5;
	int enemies_count = rand() % 3 + 1;
	int hp = rand() % 101 + 100;	int dynamic_hp = hp;
	int stunTime = rand() % 3 + 1;
	int stunDelay = rand() % (stunTime + 1) + (stunTime * 2);
};

vector<Create_Character> get_characters(int charactersCount);
void print_characters(int first, int charactersCount, vector<Create_Character> __Characters);
void beating_character(vector<Create_Character>& Characters, int enemy, int hero, COORD stats, string character);
void clear_Status(SHORT x, SHORT y);
void stunning(vector<Create_Character> Characters,
	int& enemy_stunLoading, int& enemy_InStun, int& hero_stunLoading, int& hero_InStun, int enemy, int hero,
	string character);
int choose_sort();
void bubble_sort(vector <pair<int, int>>& Winners);
void printWinners(vector<pair<int, int>> Winners, int sort);
COORD get_CursorCoords();
int choice_test();

#endif