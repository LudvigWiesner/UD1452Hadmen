#pragma once
#include <SFML/Audio.hpp>

class SoundEffect
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	SoundEffect();
	void setSoundFile(std::string soundFile);
	void playSound();
	void setVolume(int volumeNumber);
	void stopSound();
};