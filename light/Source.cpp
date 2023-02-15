//метод реализован отдельно от класса
//может произойти ошибка в функции removeAt, если элемент является первым или последним в списке

#include<iostream>
using namespace std;
#include<vector>
#include<string>

template <typename T>//Шаблон
struct Node//Название структуры
{
	T value;// Полезные данные
	Node<T>* next;
	Node<T>* prev;
	Node<T>(int _value)//Контруктор
	{
		value = _value;
		next = nullptr;
		prev = nullptr;
	}

};

template <typename T>//Шаблон
struct List// Управляющая структура
{
	Node<T>* first; //Указатель на первый листок
	Node<T>* last;//Указатель на ппоследний листок
	List()
	{
		first = nullptr;
		last = nullptr;

	}
	bool is_empty()//Функция проверки есть ли листики
	{
		return first == nullptr;
	}
	void push_back(T _value)
	{
		Node<T>* p = new Node<T>(_value);
		if (is_empty())
		{
			first = p;
			last = p;
			return;
		}
		last->next = p;
		p->prev = last;
		last = p;
	}
	void print()
	{
		Node<T>* p = first;
		if (is_empty())
			return;
		while (p)
		{
			cout << p->value << "\t";
			p = p->next;

		}
		cout << "\n";
	}
	Node <T>* find(T _value)
	{
		Node<T>* p = first;
		while (p && p->value != _value)
			p = p->next;
		return (p && p->value == _value) ? p : nullptr;
	}
	void remove_first()
	{
		if (is_empty())
			return;
		Node<T>* p = first;
		first = p->next;
		delete p;
	}
	void remove_last()
	{
		if (is_empty())
			return;
		Node<T>* p = last;
		first = p->prev;
		delete p;
	}
	void reverse_print()
	{
		Node<int>* p = last;
		if (is_empty())
			return;
		while (p)
		{
			cout << p->value << "\t";
			p = p->prev;
		}
		cout << "\n";
	}
	void removeAt(T _value)
	{
		Node<T>* p = find(_value);
		if (p == nullptr)
		{
			cout << "No item with value " << _value << "\n";
			return;
		}
		Node<T>* _left = p->prev;
		Node<T>* _right = p->next;
		//p->prev->next = p->next;
		//p->next->prev = p->prev;
		_left->next = _right;
		_right->prev = _left;
		delete p;

	}
	void push_After(T _value, T _new_value)
	{

		Node<T>* current = find(_value);
		if (current == nullptr)
		{
			cout << "No item with value " << _value << "\n";
			return;
		}
		Node<T>* p = new Node<T>(_new_value);
		Node<T>* right = current->next;
		current->next = p;
		p->next = right;
		right->prev = p;
		p->prev = current;


	}
	void push_Before(T _value, T _new_value)
	{

		Node<T>* current = find(_value);
		if (current == nullptr)
		{
			cout << "No item with value " << _value << "\n";
			return;
		}
		Node<T>* p = new Node<T>(_new_value);
		Node<T>* left = current->prev;
		current->prev = p;
		p->prev = left;
		left->next = p;
		p->next = current;


	}
};

template<typename T>
void del(List<T>* list, std::vector<T>nums_to_del)
{
	for (T item : nums_to_del)
	{
		list->removeAt(item);
	}
}

int main()
{

	List<int>* new_list = new List<int>();
	new_list->push_back(10);
	new_list->push_back(5);
	new_list->push_back(15);
	new_list->print();
	new_list->print();
	new_list->push_After(10, 7);
	new_list->print();
	new_list->push_Before(7, 77);
	new_list->print();

	std::vector<int>nums_to_del{ 77,5 };
	del(new_list, nums_to_del);
	new_list->print();

	delete new_list;
	return 0;
}