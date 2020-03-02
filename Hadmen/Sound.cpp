#include "Sound.h"



SoundEffect::SoundEffect()
{
	if (!buffer.loadFromFile("../Sound/defaultSound.WAV"))
	{
		sf::err() << "Error loading default sound file" << std::endl;
	}
	sound.setBuffer(buffer);
}

void SoundEffect::setSoundFile(std::string soundFile)
{
	if (!buffer.loadFromFile("../Sound/" + soundFile + ".wav"))
	{
		sf::err() << "Error loading " + soundFile << std::endl;
	}
}

void SoundEffect::playSound()
{
	this->sound.play();
}

void SoundEffect::setVolume(int volumeNumber)
{
	this->sound.setVolume(volumeNumber);
}

void SoundEffect::stopSound()
{
	this->sound.stop();
}

