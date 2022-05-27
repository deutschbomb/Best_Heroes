#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <string>

#include "Extra1_head.h"

using namespace std;

vector<Create_Character> get_characters(int charactersCount) {
	vector<Create_Character> __Characters;	// создание вектора для добавления персонажей
	for (int i = 0; i < charactersCount; i++) {	// цикл добавления персонажей в вектор
		Create_Character newCharacter = Create_Character();
		__Characters.push_back(newCharacter);
	}
	print_characters(0, charactersCount, __Characters);	// вывод всех персонажей и их характеристик
	return __Characters;
}	// функция создания вектора персонажей

void print_characters(int first, int charactersCount, vector<Create_Character> __Characters) {
	for (int i = first; i < charactersCount; i++) {	// цикл прохода по вектору персонажей
		COORD coords = get_CursorCoords();	// запоминание координат курсора
		if ((charactersCount - first != 1) && i % 2 != 0) {	// если индекс персонажа нечётный, то переместить курсор в соседний столбик
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { coords.X += 56, coords.Y -= 7 });
		}
		cout << " Персонаж " << i + 1 << ":\n ";
		__Characters[i].getAll_stats(i, coords);	// вывод характеристик персонажа
		cout << endl;
		Sleep(500);
	}
}	// функция вывода персонажей и их характеристик

void beating_character(vector<Create_Character>& Characters, int enemy, int hero, COORD stats, string character) {
	if (character == "enemy") {	// если выбран противник, то вывести его здоровье с учётом нанесённого урона
		Characters[enemy].damage(Characters[hero].get_damage());
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
			{ stats.X, stats.Y });
		Characters[enemy].get_stats(1);	// вывод характеристик противника
	}
	if (character == "hero") {	// если выбран герой, то вывести его здоровье с учётом нанесённого урона
		Characters[hero].damage(Characters[enemy].get_damage());
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
			{ stats.X, stats.Y });
		Characters[hero].get_stats(1);	// вывод характеристик героя
	}
}	// функция нанесения урона персонажу

void clear_Status(SHORT x, SHORT y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		{ x, y });	// установка курсора на нужную позицию
	for (int i = 0; i <= x; i++) {	// стирание строки в консоли заданной длины
		cout << "\b \b";
	}
}	// функция для стирания строки с информацией о поединке

void stunning(vector<Create_Character> Characters,
	int& enemy_stunLoading, int& enemy_InStun, int& hero_stunLoading, int& hero_InStun, int enemy, int hero,
	string character) {
	if (character == "hero") {	// если выбран герой, то оглушить героя на соответствующее характеристикам противника время
		hero_InStun = Characters[enemy].get_stunTime() + 1;	// время в оглушении у героя
		enemy_stunLoading = Characters[enemy].get_stunDelay() + 1;	// время "перезарядки" оглушения у противника
	}
	if (character == "enemy") {// если выбран противник, то оглушить противника на соответствующее характеристикам героя время
		enemy_InStun = Characters[hero].get_stunTime() + 1;	// время в оглушении у противника
		hero_stunLoading = Characters[hero].get_stunDelay() + 1;	// время "перезарядки" оглушения у героя
	}
}	// функция учитывания оглушения персонажа

int choose_sort() {
	cout << " ВЫБЕРИТЕ СПОСОБ РАНЖИРОВАНИЯ ПОБЕДИТЕЛЕЙ:\n";
	cout << " [1] По количеству оставшегося здоровья\n";
	cout << " [2] По времени боя\n";
	cout << " Ввод: "; int choice = choice_test();
	return choice;
}	// функция выбора пользователем способа сортировки победителей

void printWinners(vector<pair<int, int>> Winners, int sort) {
	if (sort == 1) {
		for (int i = 0; i < Winners.size(); i++) {
			cout << " Персонаж " << Winners[i].first << " - Количество здоровья: " << Winners[i].second << endl;
		}
	}
	if (sort == 2) {
		for (int i = 0; i < Winners.size(); i++) {
			cout << " Персонаж " << Winners[i].first << " - Время боя: " << Winners[i].second << endl;
		}
	}
}	// функция вывода всех персонажей-победителей соответственно выбранной сортировке

void bubble_sort(vector <pair<int, int>>& Winners) {
	int i = -1;
	bool Flag;
	do {
		i++; // увеличение итератора
		Flag = false; // присвоение флагу значения "False"
		for (int j = Winners.size() - 1; j > i; j--) {
			if (Winners[j - 1].second < Winners[j].second) {
				swap(Winners[j - 1], Winners[j]);
				Flag = true;
			}
		}
	} while (Flag == true); // выполнять цикл пока флаг не будет равен значению "True"
	int stop_sort = clock(); // время окончания сортировки
}	// сортировка персонажей-победителей методом пузырька

COORD get_CursorCoords() {
	CONSOLE_SCREEN_BUFFER_INFO CurPos; // структура, содержащая сведения о буфере экрана консоли
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurPos); // получение информации из заданной структуры
	return CurPos.dwCursorPosition; // возвращение координат
}	// функция для передачи координат текущей позиции курсора

int choice_test() {
	bool Flag;	// переменная флага
	string NUM;	// переменная строки
	do {
		Flag = true; // "поднятие" флага
		COORD coords = get_CursorCoords(); // запоминание текущей позиции курсора
		cin >> NUM; // ввод строки пользователем
		if ((int)NUM[0] < 49 || (int)NUM[0] > 50 || NUM.length() != 1) {// если в строке найден символ, не являющийся числом,
			Flag = false;												// то флаг "опускается",
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
				{ coords.X += NUM.length(), coords.Y });				// курсор перемещается на позицию перед введённой на экран строкой,
			for (int i = 0; i < NUM.size(); i++) {						// чтобы стереть с экрана введённую строку,
				cout << "\b \b";
			}
			break;														// и происходит выход из цикла
		}
	} while (Flag == false); // данная процедура повторяется, пока флаг будет оставаться "опущенным" к моменту завершения цикла
	return stoi(NUM); // возвращение введённой строки, преобразованной в целочисленный тип
}	// функция для проверки введённого числа (является ли оно числом)
