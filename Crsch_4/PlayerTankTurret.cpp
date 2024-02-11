#include "PlayerTankTurret.h"
#include "ModelFilesDefines.h"
PlayerTankTurret::PlayerTankTurret()
{
	currAng = targetAng = 0.0f;
	mypos = glm::vec3(0.0f, 0.0f, 0.0f);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	LoadFromOBJ(PLAYERTANK_TURRET_MODEL_FILE, subObjects, materials);
}

void PlayerTankTurret::tick(float tickl)
{
	if (abs(targetAng - currAng) > 0.001f) {
		if (targetAng - currAng > currAng - targetAng) {
			currAng += 0.3f*tickl;
		}
		else {
			currAng -= 0.3f * tickl;
		}
	}
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::rotate(mytrf, -currAng + glm::radians(90.0f), { 0.0f,1.0f,0.0f });
	mytrf = glm::scale(mytrf, { 100.0f,100.0f,100.0f });
}

void PlayerTankTurret::rotate(float ang)
{
	targetAng += ang;
}

void PlayerTankTurret::rotateImm(float ang){
	currAng += ang;
	targetAng += ang;
}

PlayerTankTurret::~PlayerTankTurret()
{
	for (int i = 0; i < subObjects->size(); i++)
		delete subObjects->at(i);
	delete subObjects;
	for (int i = 0; i < materials->size(); i++)
		if (materials->at(i).haveTexture)
			glDeleteTextures(1, &(materials->at(i).texture));
	delete materials;
}

void PlayerTankTurret::move(glm::vec3 pos)
{
	mypos = pos + glm::vec3(0.0f, 0.5f, 0.0f);
}
