#include <iostream>
#include <windows.h>
#include <characters/characters.h>
#include <stdexcept>
#include <string>


void menu() {
	system("cls");
	cout << "Приветствуем вас в нашей игре" << endl;
	cout << "1 - Добавить персонажа в список по указанному индексу" << endl;
	cout << "2 - Удалить персонажа из списка по указанному индексу" << endl;
	cout << "3 - Показать список персонажей" << endl;
	cout << "4 - Найти наиболее сильного персонажа" << endl;
	cout << "5 - " << endl;
	cout << "6 - Выйти из игры" << endl;
	cout << "> ";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CharacterList CL = CharacterList();
	Character item = Character();
	int input = 0;
	int idx;
	while (input != 6) {
		menu();
		cin >> input;
		switch (input) {
		case 1:
			system("cls");
			CL.show_all();
			cout << "Введите индекс персонажа: ";
			cin >> idx;
			cin >> item;
			CL.add_character(idx, item);
			break;
		case 2:
			system("cls");
			CL.show_all();
			cout << "Введите индекс персонажа: ";
			cin >> idx;
			CL.delete_character(idx);
			break;
		case 3:
			system("cls");
			CL.show_all();
			break;
		case 4:
			system("cls");
			CL.show_all();
			idx = CL.index_of_maxdam();
			cout << "Индекс наиболее сильного персонажа: " << idx << endl;
			break;
			/*
		case 5:
			system("cls");
			CL.show_all();
			cout << "Ââåäèòå èíäåêñ: ";
			cin >> idx;
			CL[idx]->compute_salary();
			cout << "Çàðàáîòíàÿ ïëàòà: " << EL[idx]->compute_salary() << endl;
			break;
			*/
		}
		
		if (input != 6)
			system("pause");
	}
}
