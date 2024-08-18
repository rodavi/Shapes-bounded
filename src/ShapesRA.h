//
// Created by rodrigo on 17/08/24.
//
#include <vector>
#include<iostream>
#include <string>
#include <SFML/Graphics.hpp>
#ifndef SHAPESRA_H
#define SHAPESRA_H

#endif //SHAPESRA_H

class Shape_RA :public sf::Shape{
    int m_x, m_y;
    int m_R, m_G, m_B;
    std::string m_name;
public:

    Shape_RA(int x, int y, int R, int G, int B, std::string& name)
        :m_x(x), m_y(y), m_R(R), m_G(G), m_B(B), m_name(name){}

    std::vector<double> get_position() {
        std::vector<double> pos {double(m_x), double(m_y)};
        return pos;
    }

    std::vector<int> color() {
        std::vector<int> color{m_R, m_G, m_B};
        return color;
    }

    std::string get_name() { return m_name; }

};

class Rectangle :public sf::RectangleShape{
    int m_width, m_height;

public:
    Rectangle(int x, int y, int width, int height, int R, int G, int B, std::string name)
        : sf::RectangleShape(), m_width(width), m_height(height) {

        sf::RectangleShape rect(sf::Vector2f(m_width, m_height));
    }
};

class Circle :public Shape_RA{
    int m_radiu;

public:
    Circle(int x, int y, int radius, int R, int G, int B, std::string name)
    : Shape_RA(x, y, R, G, B, name), m_radiu(radius) {
        sf::CircleShape circ(m_radiu);
    }
};