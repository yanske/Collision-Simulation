#include <iostream>
//class contains exception handling to ensure variables entered by user are valid
bool errorHandling(char input, char condition1, char condition2)
    {
        if(std::cin.fail() || input!='y' && input!='n')
        {
            std::cin.clear();
            std::cin.ignore(9999, '\n');
            std::cout<<"Try again: ";
            return true;
        }
        else
        {
            std::cin.ignore(9999, '\n');
            return false;
        }
    }
bool errorHandling(double input)
    {
        if(std::cin.fail() || input<=0)
        {
            std::cin.clear();
            std::cin.ignore(9999, '\n');
            std::cout<<"Try again: ";
            return true;
        }
        else
        {
            std::cin.ignore(9999, '\n');
            return false;
        }
    }
bool errorHandling()
    {
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(9999, '\n');
            std::cout<<"Try again: ";
            return true;
        }
        else
        {
            std::cin.ignore(9999, '\n');
            return false;
        }
}
