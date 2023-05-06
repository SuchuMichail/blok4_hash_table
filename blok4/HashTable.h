#pragma once
#include <iostream>

template<typename T>
class HashTable
{
private:
	template<typename N>
	struct Node {
		Node<N>* next;
		Node<N>* prev;
		Node<N>* next_linked;
		Node<N>* prev_linked;
		N data;
	};

	Node<T>* arr = nullptr;
	Node<T>* linkage;
	int size;

public:
	template<typename T>
	class Iterator {
	private:
		const HashTable<T>& table;
		Node<T>* pointer = nullptr;
		int index;

	public:
		Iterator(const HashTable<T>& tab) : table(tab), pointer(tab.getPointerStart()), index(0) {
		}
		~Iterator() {
			pointer = nullptr;
			index = 0;
		}

		void start() {
			if (table.isEmpty()) {
				std::cout << "Таблица пуста\n";
			}
			else {
				pointer = table.getPointerStart();
			}
		}

		T getCurrentData() const {
			return pointer->data;
		}

		Node<T>* getCurrentPointer() const {
			return pointer;
		}

		void moveNext() {
			//std::cout << "index = " << index << "\n";
			if (!isAll()) {
				while (pointer->next == &(table.arr[index])) {
					index++;
					if (index!=table.size) {
						pointer = &(table.arr[index]);
					}
				}
				pointer = pointer->next;
			}
			else {
				std::cout << "Двигаться некуда\n";
			}
		}

		bool isAll() const {
			return index==table.size;
		}
	};




	///////////////////////////////////////////////////////////////////////
	template<typename T>
	class LinkedIterator {
	private:
		const HashTable<T>& table;
		Node<T>* pointer = nullptr;

	public:
		LinkedIterator(const HashTable<T>& tab) : table(tab), pointer(tab.getPointerLinked()) {
		}

		~LinkedIterator() {
			pointer = nullptr;
		}

		void start() {
			if (table.isEmpty()) {
				std::cout << "Таблица пуста\n";
			}
			else {
				pointer = table.getPointerLinked();
			}
		}

		T getCurrentData() const {
			return pointer->data;
		}

		bool isAll() const {
			return pointer->next_linked==table.getPointerLinked();
		}

		void moveNext() {
			if (!isAll()) {
				pointer = pointer->next_linked;
			}
			else {
				std::cout << "Двигаться некуда\n";
			}
		}
	};




	////////////////////////////////////////////////////////////////////////////////////////

	HashTable(int s) {
		size = s;
		arr = new Node<T>[size];
		linkage = new Node<T>;
		linkage->next_linked = linkage;
		linkage->prev_linked = linkage;

		for (int i = 0; i < size; i++) {
			Node<T>* buf = &arr[i];
			buf->next = buf;
			buf->prev = buf;
		}
	}

	~HashTable() {
		makeEmptyTable();
		delete[] arr;
		arr = nullptr;
		delete linkage;
		size = 0;
	}

	Node<T>* getPointerStart() const {
		if (isEmpty()) {
			return nullptr;
		}
		return &arr[0];
	}

	Node<T>* getPointerLinked() const {
		return linkage;
	}

	void insertElement(int key, T elem) {
		Node<T>* buf = &arr[key];
		Node<T>* tmp = new Node<T>;
		tmp->data = elem;
		tmp->next = buf;
		tmp->prev = buf->prev;
		buf->prev->next = tmp;
		buf->prev = tmp;
		

		tmp->next_linked = linkage;
		tmp->prev_linked = linkage->prev_linked;
		linkage->prev_linked->next_linked = tmp;
		linkage->prev_linked = tmp;
	}

	void deleteElement(int key, T elem) {
		Node<T>* tmp = &arr[key];
		while (tmp->data!=elem && tmp->next!=&arr[key]) {
			tmp = tmp->next;
		}
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;

		tmp->next_linked->prev_linked = tmp->prev_linked;
		tmp->prev_linked->next_linked = tmp->next_linked;
		delete tmp;
	}

	int findElement(T elem) {
		int key=-1;

		for (int i = 0; i < size; i++) {
			Node<T>* buf = &arr[i];
			Node<T>* tmp = buf;
			while (tmp->next != buf) {
				if (tmp->data == elem) {
					key = i;
				}
				tmp = tmp->next;
			}
		}

		return key;
	}

	void makeEmptyTable() {
		for (int i = 0; i < size; i++) {
			Node<T>* buf = &arr[i];
			while (buf->next != buf) {
				Node<T>* tmp = buf->next;
				buf->next = buf->next->next;
				delete tmp;
			}
			buf = nullptr;
		}
	}

	bool isEmptyList(int index) const {
		return (&arr[index])->next == &arr[index];
	}

	bool isEmpty() const {
		bool res = true;
		for (int i = 0; i < size; i++) {
			if (!isEmptyList(i)) {
				res = false;
			}
		}
		return res;
	}

	void printTable() {
		std::cout << "Table\n";
		for (int i = 0; i < size; i++) {
			Node<T>* buf = &arr[i];
			Node<T>* iter = buf->next;
			while (iter != buf) {
				std::cout << iter->data << " ";
				iter = iter->next;
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void printIterator() {
		std::cout << "Print Iterator\n";
		Iterator<T> iterator(*this);
		while (!iterator.isAll()) {
			iterator.moveNext(); 
			if (!iterator.isAll()) {
				std::cout << iterator.getCurrentData() << " ";
			}
		}
		std::cout << "\n";
	}
	
	void printLinkedIterator() {
		std::cout << "Print LinkedIterator\n";
		LinkedIterator<T> iterator(*this);
		while (!iterator.isAll()) {
			iterator.moveNext();
			std::cout << iterator.getCurrentData() << " ";
			
		}
		std::cout << "\n";
	}
};

