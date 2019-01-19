#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Sound {
public:
	Sound(std::string file_path);
	Sound() {};
	virtual ~Sound() {};
	void play() {_sound.play();}
	void stop() {_sound.stop();}
	void loop() {_sound.setLoop(true);}
	sf::Sound get_sound() const {return _sound;}
	void load_sound(std::string file_path);
private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
};