// blok4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "HashTable.h"

int main()
{
    setlocale(LC_ALL, "Rus");

    HashTable<int> table(4);
    table.insertElement(2, 5); 
    table.insertElement(2, 6);
    table.insertElement(1, 1);
    table.insertElement(2, 9);
    table.insertElement(1, 0);
    table.printTable();
    table.printIterator();
    table.printLinkedIterator();

    int key = table.findElement(6);
    std::cout << "key = " << key << "\n";

    table.deleteElement(key, 6);
    table.printTable();
    table.printIterator();
    table.printLinkedIterator();
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
