#include "GameController.h"
#include "SceneDefines.h"
#include "ModelFilesDefines.h"
#include <random>
GameController::GameController(int* WW, int* WH) {
	time = 0.9f;
	prevTime = glfwGetTime();
	prevxpos = 0;
	prevypos = 0;
	sensivity = 1.0f;
	WinWidth = WW;
	WinHeight = WH;
	scene = new Scene();
	mypl = new PlayerTank(scene);
	BaseObject* b2 = new Skybox(scene);
	BaseObject* b3 = new Ground();
	DirLight l;
	l.ambient = { 0.9f, 0.9f, 0.9f };
	l.diffuse = { 0.0f, 0.0f, 0.0f };
	l.specular = { 0.9f, 0.9f, 0.9f };
	l.direction=  {0.0f, -1.0f, 1.0f };
	scene->setDirLight(l);
	scene->addObject(mypl);
	scene->addObject(b2);
	scene->addObject(b3);
	EnemyTank* tnk = new EnemyTank(400.0f, 0.0f, 1.0f, TIGER_TANK_MODEL_FILE, 17.0f);
	scene->addObject(tnk);
	tnk = new EnemyTank(-100.0f,400.0f, 2.0f, PZ3_TANK_MODEL_FILE, 25.0f);
	scene->addObject(tnk);
	for(int i = 0; i < 40; i++) {
		Pine* pn = new Pine(std::rand() % 4000 - 2000, std::rand() % 4000 - 2000);
		scene->addObject(pn);
	}
}

void GameController::frame() {
	scene->render(*WinWidth,*WinHeight);
	scene->tick(float(glfwGetTime() - prevTime));
	prevTime = glfwGetTime();
}

void GameController::mouseProcessor(double xpos, double ypos) {
	scene->rotateCam(float((xpos - prevxpos) / (*WinWidth)/3.14f), float((ypos - prevypos) / (*WinHeight) / 3.14f));
	mypl->rotateTurret(float((xpos - prevxpos) / (*WinWidth) / 3.14f));
	prevxpos = xpos;
	prevypos = ypos;
}

void GameController::keyboardProcessor(int key, int scancode, int action, int mods) {
 	
	if ((action == GLFW_PRESS)) {
		switch (key) {
		case GLFW_KEY_W:
			mypl->startSpeedUp(SPEEDUPPERTICK);
			break;
		case GLFW_KEY_S:
			mypl->startSpeedUp(-SPEEDUPPERTICK);
			break;
		case GLFW_KEY_A:
			mypl->startRotate(-ROTATEPERTICK);
			break;
		case GLFW_KEY_D:
			mypl->startRotate(ROTATEPERTICK);
			break;
		case GLFW_KEY_ESCAPE:
					break;
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			mypl->startSpeedUp(0);
			break;
		case GLFW_KEY_S:
			mypl->startSpeedUp(0);
			break;
		case GLFW_KEY_A:
			mypl->startRotate(0);
			break;
		case GLFW_KEY_D:
			mypl->startRotate(0);
			break;
		}
	}
}

GameController::~GameController() {
	delete scene;
}
