//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
//#include "windows.h"

using namespace std;
//Описать структуру с именем  PUBLISH, содержащую следующие поля : название статьи; авторы(массив из 5 элементов); журнал; год издания;.
//Написать программу, выполняющую следующие действия :
//Построение списка, ввод данных(файл, клавиатура на выбор пользователя); записи в списке должны быть упорядочены по названию журнала.
//Вывод на экран информации о публикациях автора К.
//Вывод на экран информации о публикациях, вышедших за последние K лет.
//Если  нет  таких книг, вывести соответствующее сообщение. // 
//Предусмотреть возможность редактирования элементов массива – удаление, добавление, изменение.


struct PUBLISH {
	string PublishTitle; 
	string Author[5]; 
	string MagazineTitle; 
	int YearPublication; 
	PUBLISH* PublishNext; 
};

struct WorkWtithList {
	PUBLISH* WorkerList = NULL;
	// Добавление журнала
	void AddPublication(PUBLISH*& list, string _PublishTitle, string _Author[5], string _MagazineTitle, int _YearPublication)
	{
		
		PUBLISH
			* prev = NULL,
			* next = list;
		// ищем место для вставки (сравниваем названия Журналов):
		while (next != NULL && _MagazineTitle > next->MagazineTitle)
		{
			prev = next;
			next = next->PublishNext;

		}

		PUBLISH* pub = new PUBLISH;
				
		pub->PublishTitle = _PublishTitle;
		for (int i = 0; i < 5; i ++)
		pub->Author[i] = _Author[i];
		pub->MagazineTitle = _MagazineTitle;
		pub->YearPublication = _YearPublication;		
		pub->PublishNext = next;

		// вставляем элемент в начало списка (также в случае, если он изначально пустой)
		if (prev == NULL)
		{
			list = pub;
		}
		// вставляем в середину или в конец (между prev и next)
		else
		{
			prev->PublishNext = pub;
		}

	}
	//Добавить новую публикацию
	void InputPublication(istream& istr, PUBLISH*& list)
	{
		int CountPublish; // кол-во публикаций
		string PublishTitle; 
		int CountAuthor;
		string Author[5];
		string MagazineTitle; //Название журнала		
		int YearPublication;
		istr >> CountPublish;
		istr.get();
		for (int i = 0; i < CountPublish; i++)
		{
			getline(istr, PublishTitle);
			//
			istr >> CountAuthor;
			for (int j = 0; j < CountAuthor; j++)
			{
				istr >> Author[j];
			}
			istr.get();
			getline(istr, MagazineTitle);
			istr >> YearPublication;
			istr.get();
			AddPublication(list, PublishTitle, Author, MagazineTitle, YearPublication );

		} 
	}
	// вывод данных на консоль
	void OutputPublication(PUBLISH* list)
	{
		while (list != NULL)
		{
			cout << endl << list->PublishTitle << endl;
			for (int i = 0; i < 5; i++)
			{
				cout << list->Author[i] << " ";
			}
			cout << endl;
			cout << list->MagazineTitle << endl;
			cout << list->YearPublication << endl;
			list = list->PublishNext;
		}
		

	}

	void ClearPublishList(PUBLISH*& list)
	{
		PUBLISH* temp;
		while (list != NULL)
		{
			temp = list;
			list = list->PublishNext;
			delete temp;
		}
	}

	void PublishMoereK(PUBLISH* list)
	{
		bool flag = true;
		int K = 0;
		cin >> K;
		if (list == NULL)
		{
			cout << "Список публикаций пуст." << endl;
		}
		else
		{
			PUBLISH* temp = list;
			while (list != NULL)
			{
				if (list->YearPublication > 2019 - K) {
					if (flag) {
						cout << "Список публикаций вышедших за последние " << K << " лет"<< endl;
						flag = false;
					}
					cout << endl << list->PublishTitle << endl;
					for (int i = 0; i < 5; i++)
					{
						cout << list->Author[i] << " ";
					}
					cout << endl;
					cout << list->MagazineTitle << endl;
					cout << list->YearPublication << endl;
				}
				list = list->PublishNext;
			}
		}
	}
	void PublishWithAuthorK(PUBLISH* list, string _Author)
	{
		bool flag = true;
		if (list == NULL)
		{
			cout << "Список публикаций пуст." << endl;
		}
		else
		{
			while (list != NULL)
			{
				bool f = false;
				for (int i = 0; i < 5; i++)
				{
					if (_Author == list->Author[i])
						f  = true;

				}
				if (f) {
					if (flag) {
						cout << "Список публикаций которые написал: " << _Author << endl;
						flag = false;
					}
					cout << endl << list->PublishTitle << endl << list->MagazineTitle << endl
						<< list->YearPublication << endl;
				}
				list = list->PublishNext;
			}
		}
		if (flag)
			cout << "публикаций  с данным автором не найдено" << endl;
	}
	void DeletePublish(PUBLISH*& list, string _PublishTitle)
	{
		PUBLISH
			* prev = NULL,
			* next = list;
		while (next != NULL)
		{
			if (next->PublishTitle == _PublishTitle) {
				if (prev == NULL)
					list = next->PublishNext;
				else
					prev->PublishNext = next->PublishNext;
				delete next;
				cout << "публикация " << _PublishTitle << " удалена." << endl;
				return;
			}
			prev = next;
			next = next->PublishNext;
		}
		cout << "публикация с данным именем не найдены." << endl;
	}
	void ChangePublish(PUBLISH*& list)
	{
		cout << "Введите название публикации" << endl;
		PUBLISH
			* prev = NULL,
			* next = list;
		string TakeALook;
		cin >> TakeALook;
		while (next != NULL)
		{
			cin.get();
			if (next->PublishTitle == TakeALook) {
				if (prev == NULL)
					list = next->PublishNext;
				else
					prev->PublishNext = next->PublishNext;
				delete next;
				string PublishTitle; //Имя товара
				int CountAuthor;
				string Author[5];
				string MagazineTitle; //Название магазина
				int YearPublication; //Цена товара
				cout << "Введите в последующих строках:" << endl
					<< "Имя публикации" << endl
					<< "кол-во авторов в публикации" << endl
					<< "всех авторов" << endl
					<< "название журнала" << endl
					<< "дату написания публикации" << endl;
			
				getline(cin, PublishTitle);
				//
				cin >> CountAuthor;
				cin.get();
				for (int i = 0; i < CountAuthor; i++)
				{
					cin >> Author[i];
					cin.get();
				}
				getline(cin, MagazineTitle);
				cin >> YearPublication;
				AddPublication(list, PublishTitle, Author, MagazineTitle, YearPublication);
				cout << "Данные изменены" << endl;
				return;

			}
			prev = next;
			next = next->PublishNext;
		}
		cout << "Товар с данным наименованием не найден" << endl;
	}

};

int main()
{

	//SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	//SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_ALL, "Russian");
	int Case;
	ifstream fin;
	WorkWtithList list;
	cout << "Выберите способ ввода:" << endl
		<< "1 - с клавиатуры" << endl
		<< "2 - из файла" << endl;
	cin >> Case;
	switch (Case)
	{
	case 1:
		system("cls");
		cout << "Введите в последующих строках:" << endl
			<< "кол-во публикаций" << endl
			<< "Имя публикации" << endl
			<< "кол-во авторов в публикации" << endl
			<< "всех авторов" << endl
			<< "название журнала" << endl
			<< "дату написания публикации" << endl;
		list.InputPublication(cin, list.WorkerList);
		break;
	case 2:
		fin.open("input.txt");
		list.InputPublication(fin, list.WorkerList);
		fin.close();
		break;
	default:
		cout << "Введено не верное число.";
		break;

	}
	system("cls");
	do
	{
		cout << "Выберите действие:" << endl <<
			"0 - Выход" << endl <<
			"1 - Добавить публикацию" << endl <<
			"2 - Вывести список всех публикаций" << endl <<
			"3 - очистить список публикаций" << endl <<
			"4 - удалить публикацию" << endl <<
			"5 - Изменить информацию о публикации" << endl <<
			"6 - Поиск публикаций с данным автором" << endl <<
			"7 - Поиск публикаций которые были выпущены после данного года" << endl;
		cin >> Case;
		string TakeALook;
		switch (Case)
		{
		case 0:
			system("cls");
			cout << "Завершение программы" << endl;
			break;
		case 1:
			system("cls");
			cout << "Введите в последующих строках:" << endl
				<< "кол-во публикаций" << endl
				<< "Имя публикации" << endl
				<< "кол-во авторов в публикации" << endl
				<< "всех авторов" << endl
				<< "название журнала" << endl
				<< "дату написания публикации" << endl;
			list.InputPublication(cin, list.WorkerList);
			break;
		case 2:
			system("cls");
			cout << "Вывод всех публикаций" << endl;
			list.OutputPublication(list.WorkerList);
			break;
		case 3:
			system("cls");
			list.ClearPublishList(list.WorkerList);
			break;
		case 4:
			system("cls");
			cout << "Введите название публикации" << endl;
			cin.get();
			getline(cin, TakeALook);
			list.DeletePublish(list.WorkerList, TakeALook);
			break;
		case 5:
			system("cls");
			list.ChangePublish(list.WorkerList);
			break;
		case 6:
			system("cls");
			cin.get();
			cout << "Введите автора" << endl;
			getline(cin, TakeALook);
			list.PublishWithAuthorK(list.WorkerList, TakeALook);
			break;
		case 7:
			system("cls");
			cin.get();
			cout << "Введите год" << endl;
			list.PublishMoereK(list.WorkerList);
			break;
		default:
			system("cls");
			cout << "Неверный ввод" << endl;
			break;
		}
		system("pause");
		system("cls");
	} while (Case != 0);

	return 0;
}