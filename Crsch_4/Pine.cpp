#include "Pine.h"
#include "ModelFilesDefines.h"
Pine::Pine(float xpos, float ypos)
{
	mypos = glm::vec3(0.0f, 0.0f, 0.0f);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, { xpos,0.0f,ypos });
	mytrf = glm::scale(mytrf, { 2.0f,2.0f,2.0f });
	LoadFromOBJ(PINE_MODEL_FILE, subObjects, materials);
}

void Pine::tick(float tickl)
{
}

Pine::~Pine()
{
	for (int i = 0; i < subObjects->size(); i++)
		delete subObjects->at(i);
	delete subObjects;
	for (int i = 0; i < materials->size(); i++)
		if (materials->at(i).haveTexture)
			glDeleteTextures(1, &(materials->at(i).texture));
	delete materials;
}
