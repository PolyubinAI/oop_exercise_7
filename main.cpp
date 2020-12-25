
//Полюбин Арсений, М80-206Б-19, Вариант 18: Трапеция, квадрат прямоугольник

#include <iostream>
#include <string>
#include <memory>
#include "Factory.hpp"
#include "doc.hpp"

int main()
{
    std::cout << "Enter command/exit\n";
    while(true)
    {
        try
        {
            std::string name;
            Factory<double> fact;
            std::cin >> name;
            if(name == "exit") { break; }
            if(name == "command")
            {
                command(std::cin, fact);
                break;
            }
            else
            {
                std::ifstream finp;
                finp.open(name);
                if (!finp.is_open()) { throw std::runtime_error("File is not opened"); }
                command(finp, fact);
                break;
            }
        }
        catch(const std::exception& e) { std::cerr << e.what() << '\n'; }
    }
    return 0;
}