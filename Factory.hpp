//
// Created by Ars Polybin on 09.12.2020.
//

#ifndef LAB3_FACTORY_HPP
#define LAB3_FACTORY_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include "Figure.hpp"
template <typename T>
class Factory
{
public:
    std::vector<std::shared_ptr<Figure<T>>> vec;
    std::vector<std::pair<std::shared_ptr<Figure<T>>, std::string>> command_vec;
    using value_type = T;
    Factory() {}
    std::shared_ptr<Figure<T>> create(std::istream& is);
    std::shared_ptr<Figure<T>> create(std::ifstream& is);
};

template <typename T>
std::shared_ptr<Figure<T>> Factory<T>::create(std::istream& is)
{
    std::string name;
    is >> name;
    if (name == "square") { return std::shared_ptr<Figure<T>> (new Square<T>(is)); }
    else if (name == "rectangle") { return std::shared_ptr<Figure<T>> (new Rectangle<T>(is)); }
    else if (name == "trapeze")  { return std::shared_ptr<Figure<T>> (new Trapeze<T>(is)); }
    else { throw std::logic_error("No such figure"); }
}
template <typename T>
std::shared_ptr<Figure<T>> Factory<T>::create(std::ifstream& is)
{
    std::string name;
    is >> name;
    if (name == "square") { return std::shared_ptr<Figure<T>> (new Square<T>(is)); }
    else if (name == "rectangle") { return std::shared_ptr<Figure<T>> (new Rectangle<T>(is)); }
    else if (name == "trapeze")  { return std::shared_ptr<Figure<T>> (new Trapeze<T>(is)); }
    else { throw std::logic_error("No such figure"); }
}
#endif //LAB3_FACTORY_HPP
