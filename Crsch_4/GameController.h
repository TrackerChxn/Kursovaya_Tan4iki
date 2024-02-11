#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include "Scene.h"

#include "BaseObject.h"
#include "PlayerTank.h"
#include "Skybox.h"
#include "Ground.h"
#include "EnemyTank.h"
#include "Pine.h"
class GameController {
	private:
		double prevTime;
		double prevxpos;
		double prevypos;
		float sensivity;
		int *WinWidth;
		int *WinHeight;
		Scene* scene;
		PlayerTank* mypl;
		float time;
	public:
		GameController(int *WW,int *WH);
		void frame();
		void mouseProcessor(double xpos,double ypos);
		void keyboardProcessor(int key, int scancode, int action, int mods);
		~GameController();
};

