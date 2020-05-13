#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>

using namespace std;

template <typename T1, typename T2>
struct Element {
	T1 Fio;
	T1 doljn;
	T2 data_in_work;
	T2 n_otdela;
	struct Element* next;
	struct Element* prev;
};

template <typename T1, typename T2>
class Sotrudnik {
public:
	Element<T1, T2>* Head;
	Element<T1, T2>* Tail;
	int Count;

	Sotrudnik();

	int GetCount();

	void AddHead(T1 Fio, T1 doljn, T2 data_in_work, T2 n_otdela);
	void AddTail(T1 Fio, T1 doljn, T2 data_in_work, T2 n_otdela);
	void Print();

	void Sort(int Props);
	void swap(Element<string, int>* q, Element<string, int>* p);
	void SotrudnikSincen_otdela(int n_otdela);

	friend ostream& operator << (ostream& out, const Sotrudnik<T1, T2>& p) {

		out << "всего вв сотрудников: " << p.Count << endl;

		return out;
	}

	int& operator[](const int index);
};

template<typename T1, typename T2>
Sotrudnik<T1, T2>::Sotrudnik()
{
	Head = Tail = nullptr;
	Count = 0;
}

template<typename T1, typename T2>
int Sotrudnik<T1, T2>::GetCount()
{
	return Count;
}

template<typename T1, typename T2> 
void Sotrudnik<T1, T2>::AddHead(T1 Fio, T1 doljn, T2 data_in_work, T2 n_otdela)
{
	Element<T1, T2>* temp = new Element<T1, T2>;
	temp->prev = 0;
	temp->Fio = Fio;
	temp->doljn = doljn;
	temp->n_otdela = n_otdela;
	temp->data_in_work = data_in_work;
	temp->next = Head;

	if (Head != 0)
		Head->prev = temp;

	if (Count == 0)
		Head = Tail = temp;
	else
		Head = temp;
	Count++;
}

template<typename T1, typename T2>
void Sotrudnik<T1, T2>::AddTail(T1 Fio, T1 doljn, T2 data_in_work, T2 n_otdela)
{
	try {
		Element<T1, T2>* temp = new Element<T1, T2>;
		temp->prev = Tail;
		temp->Fio = Fio;
		temp->doljn = doljn;
		temp->n_otdela = n_otdela;
		temp->data_in_work = data_in_work;
		temp->next = 0;

		if (Tail != 0)
			Tail->next = temp;

		if (Count == 0)
			Head = Tail = temp;
		else
			Tail = temp;
		Count++;
	}
	catch (bad_alloc ex) {
		cout << "Error. Cannot allocate memory." << endl;
		cout << ex.what() << endl;
	}
}

template<typename T1, typename T2>
void Sotrudnik<T1, T2>::Print()
{
	int i = 1;
	Element<T1, T2>* temp = this->Head;
	while (temp != NULL) {
		cout.setf(ios::left);
		cout.setf(ios::uppercase);
		cout.setf(ios::skipws);
		cout << i << ". " << setw(10)
			<< temp->Fio << setw(10)
			<< temp->doljn << setw(10);
		cout.setf(ios::right);
			cout<< temp->data_in_work << setw(10)
			<< temp->n_otdela << endl;
		temp = temp->next;
		cout.unsetf(ios::right);
		i++;
	}
}

template<typename T1, typename T2>
int& Sotrudnik<T1, T2>::operator[](const int index)
{
	int counter = 0;
	Element<T1, T2>* current = this->Head;

	while (current != nullptr) {
		if (counter == index) {
			return current->Fio;
		}
		current = current->next;
		counter++;
	}
}

template <typename T1, typename T2, typename T3>
ostream& operator << (ostream& str, const Sotrudnik<T1, T2>& ov) {
	Element<T1, T2>* current = ov.Head;
	while (current != NULL) {
		str << current->Fio << " "
			<< current->doljn << " "
			<< current->data_in_work << " "
			<< current->n_otdela
			<< endl;
		current = current->next;
	}
	return str;
}

template <typename T1, typename T2>
class textFile {
public:
	void static writeInFile(Sotrudnik<T1, T2> element)
	{
		cout << "Попытка записать данные в файл.";
		try {
			string path = "fdata.txt";
			ofstream fout(path);
			if (!fout.is_open()) {
				throw "Ошибка открытия файла!";
			}

			cout << "\nФайл успешно открыт!" << endl;

			Element<string, int>* current = element.Head;
			while (current != NULL) {
				fout << current->Fio << " "
					<< current->doljn << " "
					<< current->data_in_work << " "
					<< current->n_otdela
					<< endl;
				current = current->next;
			}
			fout.close();

			cout << "Данные записаны." << endl;
		}
		catch (char* str) {
			cout << str << endl;
		}
	}

	void static readFromFile()
	{
		cout << "\nПопытка считать данные из файла!" << endl;

		try {
			ifstream in("fdata.txt");
			T1 Fio;
			T1 doljn;
			T2 data_in_work;
			T2 n_otdela;

			Sotrudnik<string, int> current;
			if (!in.is_open()) {
				throw "Ошибка открытия файла!";
			}

			
			if (in.is_open()) {
				while (in >> Fio >> doljn >> data_in_work >> n_otdela) {
					current.AddTail(Fio, doljn, n_otdela, data_in_work);
				}
			}

			in.close();
			cout << "\nРезультат:" << endl;
			current.Print();

			cout << "\nСортировка по должности:" << endl;
			current.Sort(0);
			current.Print();

			cout << "\nСортировка по году:" << endl;
			current.Sort(1);
			current.Print();

		}
		catch (char* str) {
			cout << str << endl;
		}
	}

};

template<typename T1, typename T2>
void Sotrudnik<T1, T2>::Sort(int props)
{
	Element<string, int>* left = this->Head;
	Element<string, int>* right = this->Head->next;

	while (left->next)
	{
		while (right)
		{
			switch (props)
			{

			case 0:
				if (left->doljn[0] > right->doljn[0])
				{
					swap(left, right);
				}
				break;

			case 1:
				if (left->n_otdela > right->n_otdela)
				{
					swap(left, right);
				}
				break;
			}
			right = right->next;
		}
		left = left->next;
		right = left->next;
	}
}

template<typename T1, typename T2>
void Sotrudnik<T1, T2>::swap(Element<string, int>* q, Element<string, int>* p)
{
	T1 qvalue = q->Fio.substr(0, q->Fio.size());
	q->Fio = p->Fio.substr(0, p->Fio.size());
	p->Fio = qvalue;

	T1 qvalue2 = q->doljn.substr(0, q->doljn.size());
	q->doljn = p->doljn.substr(0, p->doljn.size());
	p->doljn = qvalue2;

	T2 qvalue3 = q->data_in_work;
	q->data_in_work = p->data_in_work;
	p->data_in_work = qvalue3;
	T2 qvalue4 = q->n_otdela;
	q->n_otdela = p->n_otdela;
	p->n_otdela = qvalue4;

	/*T3 qvalue5 = q->c;
	q->c = p->c;
	p->c = qvalue5;*/
}

template<typename T1, typename T2>
void Sotrudnik<T1, T2>::SotrudnikSincen_otdela(int n_otdela)
{
	Sotrudnik<string, int> SotrudnikSincen_otdela;
	Element<string, int>* elementcurrentItem = this->Head;

	int count = 0;

	for (int i = 0; i < Count; ++i)
	{
		if (elementcurrentItem->n_otdela <= n_otdela) {
			Element<T1, T2>* temp = new Element<T1, T2>;
			temp->prev = elementcurrentItem->prev;
			temp->Fio = elementcurrentItem->Fio;
			temp->doljn = elementcurrentItem->doljn;
			temp->n_otdela = elementcurrentItem->n_otdela;
			temp->data_in_work = elementcurrentItem->data_in_work;
			temp->next = 0;

			if (SotrudnikSincen_otdela.Tail != 0)
				SotrudnikSincen_otdela.Tail->next = temp;

			if (count == 0)
				SotrudnikSincen_otdela.Head = SotrudnikSincen_otdela.Tail = temp;
			else
				SotrudnikSincen_otdela.Tail = temp;
			count++;
		}
		elementcurrentItem = elementcurrentItem->next;
	}

	if (count == 0)
		cout << "Такого номера отдела нет" << endl;
	else {
		Element<string, int>* left = SotrudnikSincen_otdela.Head;
		Element<string, int>* right = SotrudnikSincen_otdela.Head->next;

		cout << endl;
		while (left->next)
		{
			while (right)
			{
				if (left->doljn[0] > right->doljn[0])
				{
					swap(left, right);
				}
				break;

				right = right->next;
			}
			left = left->next;
			right = left->next;
		}

		SotrudnikSincen_otdela.Print();
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Sotrudnik<string, int> example;
	example.AddTail("Карчмит", "прогер", 2010, 101);
	example.AddTail("Святохо", "Босс",2018, 102);
	example.AddTail("Иванов", "оператор", 2019, 106);


	textFile<string, int>::writeInFile(example);
	textFile<string, int>::readFromFile();

	int n_otdela;
	cout.setf(ios::left);
	cout << "\n номер отдела: ";
	cout.unsetf(ios::left);
	cin >> n_otdela;
	example.SotrudnikSincen_otdela(n_otdela);

	cout << endl;
	cout << example;
	cout << endl;

	system("pause");
}