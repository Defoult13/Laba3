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
	cout << "5 - Начать бой" << endl;
	cout << "6 - Выйти из игры" << endl;
	cout << "> ";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CharacterList CL = CharacterList();
	shared_ptr<Knight> knight = make_shared<Knight>();
	shared_ptr<Assassin> assassin = make_shared<Assassin>();
	shared_ptr<Berserk> berserk = make_shared<Berserk>();
	int input = 0;
	int idx;
	int c1;
	int c2;
	int type;
	while (input != 6) {
		menu();
		cin >> input;
		switch (input) {
		case 1:
			system("cls");
			CL.show_all();
			cout << "Введите индекс персонажа: ";
			cin >> idx;
			cout << "Введите тип: (0-Knight,1-Assassin,2-Berserk) ";
			cin >> type;
			switch (type) {
			case 0:
				cin >> knight;
				CL.add_character(idx, knight);
				break;
			case 1:
				cin >> assassin;
				CL.add_character(idx, assassin);
				break;
			case 2:
				cin >> berserk;
				CL.add_character(idx, berserk);
				break;
			}
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
			
		case 5:
			system("cls");
			CL.show_all();
			cout << "Введите индекс первого персонажа" << endl;
			cin >> c1;
			cout << "Введите индекс второго персонажа" << endl;
			cin >> c2;
			//CL.Fight(CL[c1], *ch2);
		}
		
		if (input != 6)
			system("pause");
	}
}
