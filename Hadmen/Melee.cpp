#include "Melee.h"

Melee::Melee(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, std::string monsterName, float posX,float posY, float speed, int hp, int atk)
	:Entity(index,resourceHandler,nrOfRows, nrOfColumns,speed), name(monsterName), hp(hp), atk(atk), playerDetector(false)
{
	this->setCoordinates(posX, posY);
	
}

Melee::~Melee()
{
}

void Melee::ifPlayerDetected(PlayerCharacter* player)
{
	double px = player->getPosition().x;
	double py = player->getPosition().y;
	double mx = this->getPosition().x;
	double my = this->getPosition().y;

	float distance = sqrt((px - mx)*(px - mx) + (py - my)* (py - my));

	if (this->hp > 0)
	{
		if ((distance < 600))
		{
			
			if (px - mx < -0)
			{
				
				this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 3);
			}
			else if (px -mx > 0)
			{
				this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 2);
			}
			else
			{
				this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 0);
			}
			
		}
	}
	else
	{
		this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 1);
	}

	
}


