#include "Reshandler.h"

ResHandler::ResHandler()
{
	this->textures = new sf::Texture[texturesSize];
	this->textures[0].loadFromFile("../Images/AluminiumTexture.png");
	this->textures[1].loadFromFile("../Images/CoalTexture.png");
	this->textures[2].loadFromFile("../Images/IronTexture.png");
	this->textures[3].loadFromFile("../Images/BaseImage.png");
	this->textures[4].loadFromFile("../Images/floor01.png");
	this->textures[5].loadFromFile("../Images/StoneTexture.png");
	this->textures[6].loadFromFile("../Images/TreeTexture.jpg");
	this->textures[7].loadFromFile("../Images/wall01.png");
	this->textures[8].loadFromFile("../Images/WaterTexture.jpg");
	this->textures[9].loadFromFile("../Images/backgroundImage.jpg");
	this->textures[10].loadFromFile("../Images/LavaTexture.png");
	this->textures[11].loadFromFile("../Images/ObsidianTexture.png");
	this->textures[12].loadFromFile("../Images/GravelTexture.png");
	this->textures[13].loadFromFile("../Images/DirtTexture.png");
	this->textures[14].loadFromFile("../Images/GrassTexture.png");
	this->textures[15].loadFromFile("../Images/CharacterSpriteSheet1.png");
	this->textures[16].loadFromFile("../Images/TestSword.png");
	this->textures[17].loadFromFile("../Images/CharacterSpriteSheet2.png");
	this->textures[18].loadFromFile("../Images/smokeSheet.png");
	this->textures[19].loadFromFile("../Images/InventoryBackground.jpg");
	this->textures[20].loadFromFile("../Images/IronBarTexture.png");
	this->textures[21].loadFromFile("../Images/AluminiumBarTexture.png");
	this->textures[22].loadFromFile("../Images/PieceOfCoalTexture.png");
	this->textures[23].loadFromFile("../Images/StoneBlockTexture.jpg");
	this->textures[24].loadFromFile("../Images/LogsTexture.jpg");
	this->textures[25].loadFromFile("../Images/BucketTexture.png");
	this->textures[26].loadFromFile("../Images/TreeStumpTexture.png");
	this->textures[27].loadFromFile("../Images/BatteryTexture.png");
	this->textures[28].loadFromFile("../Images/AxeTexture.png");
	this->textures[29].loadFromFile("../Images/FurnaceTexture.png");
	this->textures[30].loadFromFile("../Images/PickaxeTexture.png");
	this->textures[31].loadFromFile("../Images/MacheteTexture.jpg");
	this->textures[32].loadFromFile("../Images/NailGunTexture.png");
	this->textures[33].loadFromFile("../Images/WoodenBucketTexture.png");
	this->textures[34].loadFromFile("../Images/WaterPurifierTexture.png");
	this->textures[35].loadFromFile("../Images/LitFurnaceTexture.png");
	this->textures[36].loadFromFile("../Images/AOE.png");
	this->textures[37].loadFromFile("../Images/BedRockTexture.png");
	this->textures[38].loadFromFile("../Images/BrickTexture.png");
	this->textures[39].loadFromFile("../Images/CactusTexture.png");
	this->textures[40].loadFromFile("../Images/EmeraldOreTexture.png");
	this->textures[41].loadFromFile("../Images/DiamondOreTexture.png");
	this->textures[42].loadFromFile("../Images/ClayTexture.png");
	this->textures[43].loadFromFile("../Images/PoisonedWaterTexture.jpg");
}

ResHandler::~ResHandler()
{
	delete[]this->textures;
}

sf::Texture ResHandler::getTexture(const int index)
{
	return this->textures[index];
}


