//
// Created by Ars Polybin on 09.12.2020.
//

#ifndef LAB3_FIGURE_HPP
#define LAB3_FIGURE_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility>
#include <limits>
#include <ios>


std::ostream& operator<<(std::ostream& out, const std::pair<float, float>& fig) {
    std::cout << "(" << fig.first << "," << fig.second << ")";
    return out;
}

template <typename T>
class Figure {
public:
    float get_area() {
        return std::abs((coordinates_[0].first*coordinates_[1].second + coordinates_[1].first*coordinates_[2].second + coordinates_[2].first*coordinates_[3].second + coordinates_[3].first*coordinates_[0].second) -
                        (coordinates_[1].first*coordinates_[0].second + coordinates_[2].first*coordinates_[1].second + coordinates_[3].first*coordinates_[2].second + coordinates_[0].first*coordinates_[3].second))/2;
    }
    std::pair<float, float> get_centre() {
        return centre_;
    }
    virtual void print(std::ofstream &fs) = 0;
    virtual void print() = 0;
    std::pair<float, float> centre_;
    std::pair<float, float> coordinates_[4];
protected:
    virtual void get_coordinates(){};
};

template <typename T>
class Square : public Figure<T> {
public:
    Square(std::pair<float, float> centre, float h) {
        this->centre_ = centre;
        h_ = h;
        get_coordinates();
    }
    void print(std::ofstream &fs){
        fs << "square" << "\n";
        fs << this->centre_.first << " " << this->centre_.second << " " << h_ << "\n";
    }
    void print(){
        std::cout << "square" << "\n";
        std::cout << this->centre_.first << " " << this->centre_.second << " " << h_ << "\n";
    }
    Square() {};
    Square(std::istream& is){
        std::cout << "Enter center coordinates and height" << "\n";
        T h;
        is >> this->centre_.first >> this->centre_.second >> h;
        h_ = h;
        if(h_ == 0) {
            throw std::logic_error("Error data\n");
        }
        get_coordinates();
        std::cout << "Sucess!\n";
        std::cout << "Enter type of command: insert/delete/clear/print/save/help/undo/exit\n";
    };
    Square(std::ifstream& is){
        T h;
        is >> this->centre_.first >> this->centre_.second >> h;
        h_ = h;
        get_coordinates();
    };
protected:
    void get_coordinates() override {
        this->coordinates_[0].first = this->centre_.first - h_/2;
        this->coordinates_[0].second = this->centre_.second + h_/2;

        this->coordinates_[1].first = this->centre_.first + h_/2;
        this->coordinates_[1].second = this->centre_.second + h_/2;

        this->coordinates_[2].first = this->centre_.first + h_/2;
        this->coordinates_[2].second = this->centre_.second - h_/2;

        this->coordinates_[3].first = this->centre_.first - h_/2;
        this->coordinates_[3].second = this->centre_.second - h_/2;
    }
private:
    float h_;
};

template <typename T>
class Rectangle : public Figure<T> {
public:
    Rectangle(std::pair<float, float> centre, float h, float wide) {
        this->centre_ = centre;
        this->h_ = h;
        wide_ = wide;
        this->get_coordinates();
    }
    void print(std::ofstream &fs){
        fs << "rectangle" << "\n";
        fs << this->centre_.first << " " << this->centre_.second << " " << wide_ << " " << h_ << "\n";
    }
    void print(){
        std::cout << "rectangle" << "\n";
        std::cout << this->centre_.first << " " << this->centre_.second << " " << wide_ << " " << h_ << "\n";
    }
    Rectangle() = default;
    Rectangle(std::istream& is){
        std::cout << "Enter center coordinates, wide and height" << "\n";
        T wide, h;
        is >> this->centre_.first >> this->centre_.second >> wide >> h;
        wide_ = wide;
        h_ = h;
        if(wide_ == 0 || h_ == 0) {
            throw std::logic_error("Error data\n");
        }
        get_coordinates();
        std::cout << "Sucess!\n";
        std::cout << "Enter type of command: insert/delete/clear/print/save/help/undo/exit\n";
    }
    Rectangle(std::ifstream& is){
        T wide, h;
        is >> this->centre_.first >> this->centre_.second >> wide >> h;
        wide_ = wide;
        h_ = h;
        get_coordinates();
    }
protected:
    void get_coordinates() override {
        this->coordinates_[0].first = this->centre_.first - wide_/2;
        this->coordinates_[0].second = this->centre_.second + h_/2;

        this->coordinates_[1].first = this->centre_.first + wide_/2;
        this->coordinates_[1].second = this->centre_.second + h_/2;

        this->coordinates_[2].first = this->centre_.first + wide_/2;
        this->coordinates_[2].second = this->centre_.second - h_/2;

        this->coordinates_[3].first = this->centre_.first - wide_/2;
        this-> coordinates_[3].second = this->centre_.second - h_/2;
    }
private:
    float h_;
    float wide_;
};

template <typename T>
class Trapeze: public Figure<T> {
public:
    Trapeze(std::pair<float, float> centre, float down_base, float up_base, float h) {
        this->centre_ = centre;
        down_base_ = down_base;
        up_base_ = up_base;
        h_ = h;
        get_coordinates();
    }
    void print(std::ofstream &fs){
        fs << "trapeze" << "\n";
        fs << this->centre_.first << " " << this->centre_.second << " " << up_base_ << " " << down_base_ << " " << h_ << "\n";
    }
    void print(){
        std::cout << "trapeze" << "\n";
        std::cout << this->centre_.first << " " << this->centre_.second << " " << up_base_ << " " << down_base_ << " " << h_ << "\n";
    }
    Trapeze() = default;
    Trapeze(std::istream &in){
        std::cout << "Coordinates of centre, up_base, down_base, h" << "\n";
        T up_base, down_base, h;
        in >> this->centre_.first >> this->centre_.second >> up_base >> down_base >> h;
        down_base_ = down_base;
        up_base_ = up_base;
        h_ = h;
        if(down_base_   == 0|| h_  == 0|| up_base_ == 0) {
            throw std::logic_error("Error data\n");
        }
        get_coordinates();
        std::cout << "Sucess!\n";
        std::cout << "Enter type of command: insert/delete/clear/print/save/help/undo/exit\n";
    }
    Trapeze(std::ifstream &in){
        T up_base, down_base, h;
        in >> this->centre_.first >> this->centre_.second >> up_base >> down_base >> h;
        down_base_ = down_base;
        up_base_ = up_base;
        h_ = h;
        get_coordinates();
    }
protected:
    void get_coordinates() override {
        this->coordinates_[0].first = this->centre_.first - up_base_/2;
        this->coordinates_[0].second = this->centre_.second + h_/2;

        this->coordinates_[1].first = this->centre_.first + up_base_/2;
        this->coordinates_[1].second = this->centre_.second + h_/2;

        this->coordinates_[2].first = this->centre_.first + down_base_/2;
        this->coordinates_[2].second = this->centre_.second - h_/2;

        this->coordinates_[3].first = this->centre_.first - down_base_/2;
        this->coordinates_[3].second = this->centre_.second - h_/2;
    }
private:
    float h_;
    float down_base_;
    float up_base_;
};

#endif //LAB3_FIGURE_HPP
