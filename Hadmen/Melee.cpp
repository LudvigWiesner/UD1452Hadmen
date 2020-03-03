#include "Melee.h"

Melee::Melee(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, std::string monsterName, float posX,float posY, float speed, int hp, int atk)
	:Entity(index,resourceHandler,nrOfRows, nrOfColumns,speed), name(monsterName), atk(atk), playerDetector(false),attackCD(sf::Time::Zero),target(nullptr),detectRNG(600),atkRNG(50),atkFlag(true),tgtChangeCD(sf::Time::Zero),tgtChangeFlag(true)
{
	this->setCoordinates(posX, posY);
	this->target = nullptr;
	
}

Melee::~Melee()
{
}

bool Melee::ifPlayerDetected(PlayerCharacter* player)
{
	if (player != nullptr)
	{
		float px = player->getPosition().x;
		float py = player->getPosition().y;
		float mx = this->getPosition().x;
		float my = this->getPosition().y;

		float distance = sqrt((px - mx) * (px - mx) + (py - my) * (py - my));

		if (this->getCurrentHP() > 0)
		{
			if ((distance < detectRNG))
			{
				this->playerDetector = true;
				this->target = player;

				if ((px - mx) >= -atkRNG && (px - mx) < 0 && distance < 75)
				{
					this->moveEntityTo(sf::Vector2f(player->getPosition().x - 50.0f, this->getPosition().y), 3);
					this->attack(player);

				}
				else if ((px - mx) <= atkRNG && (px - mx) > 0 && distance < 75)
				{
					this->moveEntityTo(sf::Vector2f(player->getPosition().x + 50.0f, this->getPosition().y), 2);

					this->attack(player);
				}
				else if (py - my >= -atkRNG && (py - my) < 0 && distance < 75)
				{
					this->moveEntityTo(sf::Vector2f(this->getPosition().x, player->getPosition().y - 50.0f), 3);
					this->attack(player);
				}
				else if (py - my <= atkRNG && (py - my) > 0 && distance < 75)
				{
					this->moveEntityTo(sf::Vector2f(this->getPosition().x, player->getPosition().y + 50.0f), 2);
					this->attack(player);
				}
				else
				{
					if (!this->getBounds().intersects(player->getBounds()))
					{
						this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 0);
					}

				}

			}
			else
			{
				this->playerDetector = false;
				this->target = nullptr;
				this->attackCD = sf::Time::Zero;
			}
		}
		else
		{
			
			this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y), 1);
		}
	}
	return this->playerDetector;
}

void Melee::attack(PlayerCharacter* player)
{
	if (this->atkFlag == true)
	{
		this->makeAttack(*player,this->atk);
		this->atkFlag = false;
	}
	
}

PlayerCharacter* Melee::targetSelection(PlayerCharacter* player1, PlayerCharacter* player2)
{
	
	if (this->tgtChangeFlag == true)
	{
		float px1 = player1->getPosition().x;
		float py1 = player1->getPosition().y;
		float px2 = player2->getPosition().x;
		float py2 = player2->getPosition().y;
		float mx = this->getPosition().x;
		float my = this->getPosition().y;

		float distance1 = sqrt((px1 - mx) * (px1 - mx) + (py1 - my) * (py1 - my));
		float distance2 = sqrt((px2 - mx) * (px2 - mx) + (py2 - my) * (py2 - my));

		if (distance1 < distance2)
		{
			if (this->tgtChangeFlag == true)
			{
				this->target = nullptr;
				this->target = player1;
				this->tgtChangeFlag = false;
			}

		}
		else
		{
			if (this->tgtChangeFlag == true)
			{
				this->target = nullptr;
				this->target = player2;
				this->tgtChangeFlag = false;
			}
		}
	}	
	
	return this->target;
}



void Melee::atkCounter(sf::Time elapstime)
{
	if ((this->atkFlag == false) )
	{
		this->attackCD += elapstime;
	}
	
	if (this->attackCD >= sf::seconds(1) && this->tgtChangeFlag == false)
	{
		this->atkFlag = true;
		this->attackCD = sf::Time::Zero;
	}
}

void Melee::targetChangeCD(sf::Time elapstime)
{
	if ((this->tgtChangeFlag == false))
	{
		this->tgtChangeCD += elapstime;
	}

	if (this->tgtChangeCD >= sf::seconds(3) && this->tgtChangeFlag == false)
	{
		this->tgtChangeFlag = true;
		this->tgtChangeCD = sf::Time::Zero;
	}
}






