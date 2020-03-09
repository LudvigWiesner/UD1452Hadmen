#pragma once
#include <SFML/Audio.hpp>

class Music
{
private:
	sf::Music music;
public:
	Music();
	void setMusic(std::string musicFile);
	void playMusic();
	void stopMusic();
	void changeVolume(float volumeNumber);
};