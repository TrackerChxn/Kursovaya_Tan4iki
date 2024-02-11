#pragma once
#include "BaseObject.h"
#include "Scene.h"
#include "ModelFilesDefines.h"
#include "LightStructs.h"
#include "PlayerTankTurret.h"
class PlayerTank :
    public BaseObject{
    private:
       float speed;
       float rtspeed;
       float myang;
       Scene* mysc;
       float rpt;
       float spt;
       SpotLight* frwLamp;
       PlayerTankTurret* myTurret;
    public:
        PlayerTank(Scene*);
        void startRotate(float);
        void startSpeedUp(float);
        virtual void tick(float);
        void rotateTurret(float);
        virtual ~PlayerTank();
};

