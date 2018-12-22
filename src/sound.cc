#include "sound.hh" 

Sound::Sound(std::string file_path)
{
    load_sound(file_path);
}


void Sound::load_sound(std::string file_path)
{
    _buffer.loadFromFile(file_path);
	_sound.setBuffer(_buffer);
}