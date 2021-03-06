#include "sound.hh"
#include <iostream>

Sound::Sound(std::string file_path) {
	load_sound(file_path);
}
void Sound::load_sound(std::string file_path) {
	if(!_buffer.loadFromFile(file_path)){
		std::cerr<< "Invalid sound file." << std::endl;
		exit(0);
	}
	_sound.setBuffer(_buffer);
}