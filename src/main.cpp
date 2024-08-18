#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ShapesRA.h"

std::vector<std::string> single_shape(const std::string& line, const char separator = ' '){
    unsigned int begin{0};
    unsigned int final{0};
    bool flag_separation{false};
    std::vector<std::string> words;
    for(int i = 0; i < line.size(); ++i) {
        if(i+1!=line.size()) {
            if(line[i] == separator) {  // Check if there is a whitespace
                if(flag_separation==false) {    //Check if there are consecutive whitespaces
                    words.push_back(line.substr(begin, final));
                    //line.erase(begin, i);
                    flag_separation = true;
                    begin =i+1;
                    final = 0;
                }else {
                    ++begin;
                }
            }
            else {
                flag_separation = false;
                ++final;
            }
        }
        else words.push_back(line.substr(begin, std::string::npos));
    }
    return words;
}
int main()
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    auto window = sf::RenderWindow{ { SCREEN_WIDTH, SCREEN_HEIGHT }, "CMake SFML Project" };
    window.setFramerateLimit(60);

    // Open file
    std::fstream fs;
    fs.open("/home/rodrigo/Documents/Code/Cpp/GameDev/cmake-sfml-project-master/config_file.txt", std::ios::in);
    std::vector<std::vector<std::string>> shapes;
    std::string line;
    unsigned int sh_id{0};
    std::vector<sf::RectangleShape> all_rec_shapes;
    std::vector<sf::CircleShape> all_cir_shapes;
    std::vector<float> sx_r;
    std::vector<float> sy_r;
    std::vector<float> sx_c;
    std::vector<float> sy_c;

    float x_pos{0};
    float y_pos{0};
    // Read information from configuration file
    while(!fs.eof() && fs.is_open()) {

        std::getline(fs, line);
        shapes.push_back(single_shape(line));
        if(shapes[sh_id][0] == "Rectangle") {
            sf::RectangleShape shape_temp(sf::Vector2f(std::stof(shapes[sh_id][3]),std::stof(shapes[sh_id][4])));
            shape_temp.setPosition(sf::Vector2f(std::stof(shapes[sh_id][1]),std::stof(shapes[sh_id][2])));
            sf::Color color(std::stoi(shapes[sh_id][5]),std::stoi(shapes[sh_id][6]),std::stoi(shapes[sh_id][7]));
            shape_temp.setFillColor(color);
            sx_r.push_back(std::stof(shapes[sh_id][9]));
            sy_r.push_back(std::stof(shapes[sh_id][10]));
            all_rec_shapes.push_back(shape_temp);
        }
        else {
            sf::CircleShape shape_temp(std::stof(shapes[sh_id][3]));
            shape_temp.setPosition(sf::Vector2f(std::stof(shapes[sh_id][1]),std::stof(shapes[sh_id][2])));
            sf::Color color(std::stoi(shapes[sh_id][4]),std::stoi(shapes[sh_id][5]),std::stoi(shapes[sh_id][6]));
            shape_temp.setFillColor(color);
            sx_c.push_back(std::stof(shapes[sh_id][8]));
            sy_c.push_back(std::stof(shapes[sh_id][9]));
            all_cir_shapes.push_back(shape_temp);
        }

        ++sh_id;
    }
    fs.close();


    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout<<"Game Over"<<std::endl;
                window.close();
            }
        }

        window.clear();

        // Draw the shapes
        for(unsigned int i=0;i<all_rec_shapes.size();++i) {
            x_pos = all_rec_shapes[i].getPosition().x+sx_r[i];
            y_pos = all_rec_shapes[i].getPosition().y+sy_r[i];

            if(x_pos <= 0 ||x_pos+all_rec_shapes[i].getSize().x >= SCREEN_WIDTH) {
                sx_r[i] *=-1;

            }

            if(y_pos <= 0 ||y_pos+all_rec_shapes[i].getSize().y >= SCREEN_HEIGHT) {
                sy_r[i] *=-1;

            }
            x_pos = all_rec_shapes[i].getPosition().x+sx_r[i];
            y_pos = all_rec_shapes[i].getPosition().y+sy_r[i];
            all_rec_shapes[i].setPosition(x_pos, y_pos);
            window.draw(all_rec_shapes[i]);
        }
        for(unsigned int i=0;i<all_cir_shapes.size();++i) {
            x_pos = all_cir_shapes[i].getPosition().x+sx_c[i];
            y_pos = all_cir_shapes[i].getPosition().y+sy_c[i];

            if(x_pos <= 0 ||x_pos+all_cir_shapes[i].getRadius()*2 >= SCREEN_WIDTH) {
                sx_c[i] *=-1;

            }

            if(y_pos <= 0 ||y_pos+all_cir_shapes[i].getRadius()*2>= SCREEN_HEIGHT) {
                sy_c[i] *=-1;

            }
            x_pos = all_cir_shapes[i].getPosition().x+sx_c[i];
            y_pos = all_cir_shapes[i].getPosition().y+sy_c[i];

            all_cir_shapes[i].setPosition(all_cir_shapes[i].getPosition().x+sx_c[i], all_cir_shapes[i].getPosition().y+sy_c[i]);
            window.draw(all_cir_shapes[i]);
        }


        window.display();
    }
}
