#include "Music.h"



Music::Music()
{
	if (!music.openFromFile("../Sound/defaultMusic.wav"))
	{
		sf::err() << "Error loading default music file" << std::endl;
	}
}

void Music::setMusic(std::string musicFile)
{
	if (!music.openFromFile("../Sound/" + musicFile + ".wav"))
	{
		sf::err() << "Error loading " + musicFile << std::endl;
	}
}

void Music::playMusic()
{
	this->music.play();
}

void Music::stopMusic()
{
	this->music.stop();
}

void Music::changeVolume(float volumeNumber)
{
	this->music.setVolume(volumeNumber);
}
