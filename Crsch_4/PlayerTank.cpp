#include "PlayerTank.h"
#include "SceneDefines.h"

PlayerTank::PlayerTank( Scene* sc){
	myang= 0.0f;
	rpt=spt = 0;
	mypos = { 0.0f,25.0f,0.0f };
	mysc = sc;
	mytrf = glm::mat4(1.0f);
	//pos = pos + glm::vec3(0.0f, -1.6f, -2.8f);
	mytrf = glm::rotate(mytrf, glm::radians(90.0f), { 0.0f,1.0f,0.0f });
		subObjects = new std::vector<SubObject*>;
		materials = new std::vector<Material>;
		LoadFromOBJ(PLAYERTANK_MODEL_FILE,subObjects, materials);
	rtspeed =1.0f;
	speed = 0.1f;
	/*SpotLight s;
	s.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	s.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	s.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	s.position = glm::vec3(5.0f, 0.0f, 0.0f);
	s.linear = 0.01f;
	s.constant = 1.0f;
	s.quadratic = 0.00f;
	s.cutOff = 0.95f;
	s.outerCutOff = 1.0;
	s.direction= glm::vec3(7.0f, 0.0f, 0.0f);
	frwLamp = mysc->addSpotLight(s);*/
	myTurret = new PlayerTankTurret();
	sc->addObject(myTurret);
}

void PlayerTank::tick(float tickl)
{
	myang += rpt* tickl;
	speed += spt * tickl;
	if (speed >= 30.0f)
		speed = 30.0f;
	if (speed <= -30.0f)
		speed = -30.0f;
	mytrf = glm::mat4(1.0f);
	glm::vec3 mv = glm::vec3(cos(myang), 0.0f, sin(myang));
	mv *= tickl * speed;
	mypos += mv;
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::rotate(mytrf, -myang+glm::radians(90.0f), { 0.0f,1.0f,0.0f });
	myTurret->rotateImm(rpt * tickl);
	mytrf = glm::scale(mytrf, { 100.0f,100.0f,100.0f });
	mysc->moveCam(mv);
	mysc->rotateCam(rtspeed * rpt * tickl, 0.0f);
	mv /= tickl * speed;
	mv *= 10;
	//frwLamp->position =mypos+mv;
	//frwLamp->direction = mv;
	myTurret->move(mypos);
}

void PlayerTank::rotateTurret(float ang)
{
	myTurret->rotate(ang);
}

PlayerTank::~PlayerTank(){

		for (int i = 0; i < subObjects->size(); i++)
			delete subObjects->at(i);
		delete subObjects;
		for (int i = 0; i < materials->size(); i++)
			if (materials->at(i).haveTexture)
				glDeleteTextures(1, &(materials->at(i).texture));
		delete materials;
}

void PlayerTank::startRotate(float proll)
{
	rpt = proll;
}

void PlayerTank::startSpeedUp(float spd){
	spt = spd;
}