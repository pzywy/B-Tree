
#include "BTree.h"
#include <iostream>
#include <string>
#include <stdlib.h>

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    BTree* tree = new BTree(1);

    bool stop = false;

    while (!stop)
    {
        char command = ' ';
        int inputValue = 0;
        std::cin >> command;

        //ignore line
        if (command == '#')continue;

        //stop program
        if(command == 'X'){ stop = true; break; }

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
        case '?': (tree->search(inputValue) != NULL) ? std::cout << inputValue << " +" << std::endl : std::cout << inputValue << " -"<<std::endl; break;
        case 'A': (tree->insert(inputValue)); break; 
        case 'I': (tree = new BTree(inputValue)); break;
        case 'P': (tree->print()); break;
        case 'L':
        {
            //dont work
            tree = new BTree(inputValue);
            std::string input;
            std::string intValue = "";

            std::getline(std::cin, input);

            for (int i = 0; i < input.length(); i++)
            {
                
                //check if int
                if (input[i] < 48 || input[i]>57)
                {
                    if (intValue != "")
                    {
                        tree->insert(std::stoi(intValue));
                        intValue = "";
                    }
                    continue;
                }
                else
                {
                    intValue += input[i];
                }
            }
            break;
        }      
        default:
            break;
        }
    } 

}

