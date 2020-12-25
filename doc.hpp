//
// Created by Ars Polybin on 09.12.2020.
//

#ifndef LAB3_DOC_HPP
#define LAB3_DOC_HPP

#include <iostream>
#include "Factory.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <string>

template <typename T>
class Document
{
private:
    Factory<T> factory;
public:
    void save(std::string const&, Factory<T> const& );
    void load(std::string const&, std::vector<std::shared_ptr<Figure<T>>>&);
};

template <typename T>
void Document<T>::save(std::string const& filename, Factory<T> const& factory)
{
    std::ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) { throw std::runtime_error("File is not opened"); }
    fout << factory.vec.size() << '\n';
    for (auto& el: factory.vec) { el->print(fout); }
}

template <typename T>
void Document<T>::load(std::string const& filename, std::vector<std::shared_ptr<Figure<T>>>& vct)
{
    std::ifstream finp;
    size_t size = 0;
    vct.clear();
    finp.open(filename);
    if (!finp.is_open()) { throw std::runtime_error("File is not opened"); }
    finp >> size;
    for(size_t i = 0; i < size; ++i) { vct.push_back(factory.create(finp)); }
}

template < typename T >
void command(std::istream & is, Factory < T > & factory) {
    std::string name = "start";
    std::cout << "Enter type of command: insert/delete/clear/print/save/load/help/undo/exit\n";
    while (name != "exit" && !is.eof()) {
        is >> name;
        if (name == "help") {
            std::cout << "insert: square/rectangle/trapeze\n";
            std::cout << "delete index\n";
            std::cout << "print\n";
            std::cout << "undo\n";
            std::cout << "exit\n";
        } else if (name == "insert") {
            std::cout << "Enter type of figure: square/rectangle/trapeze\n";
            try {
                factory.vec.push_back(factory.create(is));
                std::pair p {factory.vec.back(), "a"};
                factory.command_vec.push_back(p);
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';

            }
        } else if (name == "delete") {
            try {
                size_t ind = 0;
                std::cout << "Enter index of figure\n";
                is >> ind;
                if (ind >= factory.vec.size()) {
                    throw std::exception();
                }
                std::pair p {factory.vec.back(), "d"};
                factory.command_vec.push_back(p);
                factory.vec.erase(factory.vec.begin() + ind);
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';
            }
            std::cout << "Sucess!";
            std::cout << "Enter type of figure: square/rectangle/trapeze\n";
        } else if (name == "clear") {
            try {
                for (auto & el: factory.vec) {
                    factory.command_vec.push_back({el,"d"});
                }
                factory.vec.clear();
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';
            }
            std::cout << "Enter type of figure: square/rectangle/trapeze\n";
        } else if (name == "undo") {
            try {
                if (!factory.command_vec.empty()) {
                    if (factory.command_vec.back().second == "a") {
                        factory.vec.pop_back();
                    } else if (factory.command_vec.back().second == "d") {
                        factory.vec.push_back(factory.command_vec.back().first);
                    } else {
                        throw std::logic_error("No such command");
                    }
                    factory.command_vec.pop_back();
                } else {
                    throw std::logic_error("No operations for undo");
                }
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';
            }

        } else if (name == "print") {
            try {
                if (factory.vec.empty()) {
                    throw std::logic_error("No figures");
                }
                for (auto & el: factory.vec) {
                    el -> print();
                    std::cout << "centre " << el -> get_centre() << "\n";
                    std::cout << "area:" << el -> get_area() << "\n\n";
                }
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';
            }
        } else if (name == "save") {
            try {
                std::string filename;
                std::cout << "Input save filename\n";
                std::cin >> filename;
                Document < T > doc;
                doc.save(filename, factory);
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';
            }
           std::cout << "file saved!\n";
            std::cout << "Enter type of figure: square/rectangle/trapeze\n";
        } else if (name == "load") {
            try {
                std::string filename;
                std::cout << "Input load filename\n";
                std::cin >> filename;
                Document < T > doc;
                doc.load(filename, factory.vec);
            } catch (const std::exception & e) {
                std::cerr << e.what() << '\n';
            }
            std::cout << "file loaded!\n";
            std::cout << "Enter type of figure: square/rectangle/trapeze\n";
        }
    }
    std::cout << "Enter type of command: insert/delete/clear/print/save/help/undo/exit\n";
}
#endif //LAB3_DOC_HPP
