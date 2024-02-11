#pragma once
#include "BaseObject.h"
class PlayerTankTurret :
    public BaseObject
{
private:
    float currAng;
    float targetAng;
public:
    PlayerTankTurret();
    virtual void tick(float tickl);
    void rotate(float ang);
    void rotateImm(float ang);
    virtual ~PlayerTankTurret();
    void move(glm::vec3 pos);
};

