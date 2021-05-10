// B=Tree.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "BTree.h"
int main()
{
    BTree* t = new BTree(1);

    bool stop = false;

    while (!stop)
    {
        char command;
        int inputValue;
        std::cin >> command;

        //ignore line
        if (command == '#')continue;

        //print command doesnt provide value
        if (command != 'P') 
            std::cin >> inputValue;


        //check for input wrong format
        if (std::cin.fail())
        {
            std::cin.clear();
            continue;
        }

        switch (command)
        {
        case '?': (t->search(inputValue) != NULL) ? std::cout << "+" : std::cout << "-"; break;
        case 'A': (t->insert(inputValue)); break; 
        case 'I': (t = new BTree(inputValue)); break;
        case 'P': (t->print()); break;
        case 'X': (stop = true); break;
        default:
            break;
        }
        std::cout << std::endl;
    } 

}

