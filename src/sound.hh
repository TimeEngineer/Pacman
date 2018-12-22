#pragma once
#include <SFML/Audio.hpp>

class Sound {
public:
    Sound(std::string file_path);
    Sound() {};
    virtual ~Sound() {};
	void play() {_sound.play();}
	sf::Sound get_sound() const {return _sound;}
	void load_sound(std::string file_path);
private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
};