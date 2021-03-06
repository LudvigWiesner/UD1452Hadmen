#include "Ranged.h"

Ranged::Ranged(const int index, ResHandler* resourceHandler, int nrOfRows, int nrOfColumns, std::string monsterName, float posX, float posY, float speed, int hp, int atk)
	:Entity(index, resourceHandler, nrOfRows, nrOfColumns, speed), name(monsterName), atk(atk), playerDetector(false), attackCD(sf::Time::Zero), target(nullptr), detectRNG(600), atkRNG(500), atkFlag(true), tgtChangeCD(sf::Time::Zero), tgtChangeFlag(true)
{
	this->setCoordinates(posX, posY);
	this->target = nullptr;
	

}

Ranged::~Ranged()
{
}

bool Ranged::ifPlayerDetected(PlayerCharacter* player)
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
				//std::cout << distance << std::endl;
				if (-atkRNG <(px-mx) && (px-mx) <0)
				{
					if (distance < 150)
					{
						this->moveEntityTo(sf::Vector2f(this->getPosition().x + 50, this->getPosition().y), 0);
						//std::cout << "move back to right" << std::endl;
					}
					else
					{
						if (distance < atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y), 3);
							this->attack(player);
						}
						else if(distance > atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 0);
						}
						
					}
					

				}
				else if (atkRNG > (px-mx) && (px-mx)>0)
				{
					
					if (distance < 150)
					{
						this->moveEntityTo(sf::Vector2f(this->getPosition().x - 50.0f, this->getPosition().y), 0);
						//std::cout << "move back to left" << std::endl;
					}
					else
					{
						if (distance < atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y), 2);
							this->attack(player);
						}
						else if (distance > atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 0);
						}
						
					}
				}
				if (-atkRNG < (py-my)&& (py-my) <0)
				{
					if (distance < 150)
					{
						this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y+50), 0);
						//std::cout << "move back to Down" << std::endl;
					}
					else {
						if (distance < atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y), 3);
							this->attack(player);
						}
						else if (distance > atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 0);
						}
						
					}
					
				}
				else if (atkRNG > (py-my) && (py-my)>0)
				{
					if (distance < 150)
					{
						this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y - 50), 0);
						//std::cout << "move back to UP" << std::endl;
					}
					else
					{
						if (distance < atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(this->getPosition().x, this->getPosition().y), 2);
							this->attack(player);
						}
						else if (distance > atkRNG)
						{
							this->moveEntityTo(sf::Vector2f(player->getPosition().x, player->getPosition().y), 0);
						}
						
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

void Ranged::attack(PlayerCharacter* player)
{
	if (this->atkFlag == true)
	{
		this->makeAttack(*player, this->atk);
		this->atkFlag = false;
	}

}

PlayerCharacter* Ranged::targetSelection(PlayerCharacter* player1, PlayerCharacter* player2)
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



void Ranged::atkCounter(sf::Time elapstime)
{
	if ((this->atkFlag == false))
	{
		this->attackCD += elapstime;
	}

	if (this->attackCD >= sf::seconds(1) && this->tgtChangeFlag == false)
	{
		this->atkFlag = true;
		this->attackCD = sf::Time::Zero;
	}
}

void Ranged::targetChangeCD(sf::Time elapstime)
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
