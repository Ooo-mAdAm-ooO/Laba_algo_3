#include <iostream>

template<typename T>
class List
{
public:
	List();
	~List();
	void push_back(T data, uint8_t priority = 0);
	void push_front(T data, uint8_t priority = 3);
	void pop_back();
	void pop_front();
	void removeAt(const int index);
	void clear();
	int getSize() { return Size; }

	void push_priority(T data, uint8_t priority);

	T& operator[](const int index);
	bool isEmpty() { return Size == 0; }

private:
	template<typename U>
	class Node
	{
	public:
		U data;
		Node<U>* pNext;
		uint8_t priority;
		Node(U data = U(), uint8_t priority = 0, Node<U>* pNext = nullptr)
			: data(data), pNext(pNext), priority(priority) {
		}
	};
	int Size;
	Node<T>* head;
};

template<typename T>
List<T>::List() : Size(0), head(nullptr) {}

template<typename T>
List<T>::~List() { clear(); }

template<typename T>
void List<T>::push_back(T data, uint8_t priority)
{
	if (head == nullptr)
		head = new Node<T>(data, priority);
	else
	{
		Node<T>* current = head;
		while (current->pNext != nullptr)
			current = current->pNext;
		current->pNext = new Node<T>(data, priority);
	}
	Size++;
}

template<typename T>
void List<T>::push_front(T data, uint8_t priority)
{
	head = new Node<T>(data, priority, head);
	Size++;
}

template<typename T>
void List<T>::pop_back()
{
	if (!head) { std::cout << "Список пуст.\n"; return; }

	if (!head->pNext)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Node<T>* previous = head;
		while (previous->pNext->pNext != nullptr)
			previous = previous->pNext;
		delete previous->pNext;
		previous->pNext = nullptr;
	}
	Size--;
}

template<typename T>
void List<T>::pop_front()
{
	if (!head) { std::cout << "Список пуст.\n"; return; }
	Node<T>* toDelete = head;
	head = head->pNext;
	delete toDelete;
	Size--;
}

template<typename T>
void List<T>::push_priority(T data, uint8_t priority)
{
	Node<T>* newNode = new Node<T>(data, priority);

	if (!head || priority >= head->priority)
	{
		newNode->pNext = head;
		head = newNode;
	}
	else
	{
		Node<T>* current = head;
		while (current->pNext && current->pNext->priority > priority)
			current = current->pNext;

		newNode->pNext = current->pNext;
		current->pNext = newNode;
	}
	Size++;
}

template<typename T>
void List<T>::removeAt(const int index)
{
	if (index < 0 || index >= Size) { std::cout << "Некорректный индекс.\n"; return; }

	if (index == 0) { pop_front(); return; }

	Node<T>* previous = head;
	for (int i = 0; i < index - 1; i++)
		previous = previous->pNext;
	Node<T>* toDelete = previous->pNext;
	previous->pNext = toDelete->pNext;
	delete toDelete;
	Size--;
}

template<typename T>
void List<T>::clear()
{
	while (Size > 0)
		pop_front();
}

template<typename T>
T& List<T>::operator[](const int index)
{
	int count = 0;
	Node<T>* current = head;
	while (current != nullptr)
	{
		if (count == index)
			return current->data;
		current = current->pNext;
		count++;
	}
	throw std::out_of_range("Индекс вне диапазона");
}

template<typename T>
class Queue {
	List<T> list;
public:
	void enqueue(T data) { list.push_back(data); }
	void dequeue() { list.pop_front(); }
	T& front() { return list[0]; }
	bool empty() { return list.isEmpty(); }
	int size() { return list.getSize(); }
	void print()
	{
		if (list.isEmpty()) { std::cout << "Очередь пуста.\n"; return; }
		for (int i = 0; i < list.getSize(); i++)
			std::cout << "[" << i << "] " << list[i] << "\n";
	}
};

template<typename T>
class Stack {
	List<T> list;
public:
	void push(T data) { list.push_back(data); }
	void pop() { list.pop_back(); }
	T& top() { return list[list.getSize() - 1]; }
	bool empty() { return list.isEmpty(); }
	int size() { return list.getSize(); }
	void print()
	{
		if (list.isEmpty()) { std::cout << "Стек пуст.\n"; return; }
		for (int i = 0; i < list.getSize(); i++)
			std::cout << "[" << i << "] " << list[i] << "\n";
	}
};

void queueMenu(Queue<int>& queue)
{
	int sub = -1;
	while (sub != 0)
	{
		std::cout << "\n--- Очередь ---\n"
			<< "1. Добавить элемент\n"
			<< "2. Удалить элемент\n"
			<< "3. Показать очередь\n"
			<< "0. Назад\n"
			<< "Выберите пункт: ";
		std::cin >> sub;

		if (sub == 1) { int v; std::cout << "Введите число: "; std::cin >> v; queue.enqueue(v); }
		else if (sub == 2) queue.dequeue();
		else if (sub == 3) queue.print();
	}
}

void stackMenu(Stack<int>& stack)
{
	int sub = -1;
	while (sub != 0)
	{
		std::cout << "\n--- Стек ---\n"
			<< "1. Добавить элемент\n"
			<< "2. Удалить элемент\n"
			<< "3. Показать стек\n"
			<< "0. Назад\n"
			<< "Выберите пункт: ";
		std::cin >> sub;

		if (sub == 1) { int v; std::cout << "Введите число: "; std::cin >> v; stack.push(v); }
		else if (sub == 2) stack.pop();
		else if (sub == 3) stack.print();
	}
}

void menu()
{
	List<int> plist;
	Queue<int> queue;
	Stack<int> stack;

	plist.push_priority(10, 2);
	plist.push_priority(5, 3);
	plist.push_priority(42, 1);

	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);

	stack.push(7);
	stack.push(8);
	stack.push(9);

	int choice;
	do
	{
		std::cout << "\n===== Главное меню =====\n"
			<< "1. Добавить элемент в приоритетный список\n"
			<< "2. Удалить элемент из приоритетного списка по индексу\n"
			<< "3. Показать приоритетный список\n"
			<< "4. Работа с очередью\n"
			<< "5. Работа со стеком\n"
			<< "0. Выход\n"
			<< "=======================\n"
			<< "Выберите пункт: ";

		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Некорректный ввод! Попробуйте снова.\n";
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			int value, pr;
			std::cout << "Введите число: "; std::cin >> value;
			std::cout << "Введите приоритет (0-3): "; std::cin >> pr;
			plist.push_priority(value, pr);
			break;
		}
		case 2:
		{
			if (plist.getSize() == 0)
				std::cout << "Список пуст.\n";
			else
			{
				int index;
				std::cout << "Введите индекс элемента для удаления: ";
				std::cin >> index;
				plist.removeAt(index);
			}
			break;
		}
		case 3:
		{
			std::cout << "\nПриоритетный список:\n";
			if (plist.getSize() == 0) std::cout << "Список пуст.\n";
			else
				for (int i = 0; i < plist.getSize(); i++)
					std::cout << "[" << i << "] " << plist[i] << "\n";
			break;
		}
		case 4: queueMenu(queue); break;
		case 5: stackMenu(stack); break;
		case 0: std::cout << "Выход из программы.\n"; break;
		default: std::cout << "Некорректный пункт меню! Попробуйте снова.\n"; break;
		}
	} while (choice != 0);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	menu();
	return 0;
}
