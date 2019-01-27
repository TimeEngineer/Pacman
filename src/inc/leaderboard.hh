#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "resources.hh"

class Leaderboard {
    public: 
        Leaderboard(std::string file_path, sf::Vector2i offset, float scale);
        ~Leaderboard();

        struct Score {
            std::string name;
            int score;
        };
        void reopen();
        void draw(sf::RenderWindow& window);
        std::vector<struct Leaderboard::Score> get_top(int n);
    private:
        const sf::Vector2i _offset;
        const sf::Vector2i _name_offset;
        const sf::Vector2i _score_offset;
        std::string _file_path;
        std::vector<struct Score> _scores;
        float _scale;
        sf::Font _font;
};