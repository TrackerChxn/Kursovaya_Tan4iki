#include "EnemyTank.h"
#include "ModelFilesDefines.h"
EnemyTank::EnemyTank(float xpos,float ypos,float ang,std::string tanakModel,float size)
{
	mypos = glm::vec3(0.0f, 0.0f, 0.0f);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, { xpos,0.0f,ypos });
	mytrf = glm::rotate(mytrf, ang, { 0.0f,1.0f,0.0f });
	mytrf = glm::scale(mytrf, { size,size,size });
	LoadFromOBJ(tanakModel, subObjects, materials);
}

void EnemyTank::tick(float tickl)
{
}

EnemyTank::~EnemyTank()
{
	for (int i = 0; i < subObjects->size(); i++)
		delete subObjects->at(i);
	delete subObjects;
	for (int i = 0; i < materials->size(); i++)
		if (materials->at(i).haveTexture)
			glDeleteTextures(1, &(materials->at(i).texture));
	delete materials;
}
