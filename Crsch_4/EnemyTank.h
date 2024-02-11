#pragma once
#include "BaseObject.h"
class EnemyTank :
    public BaseObject
{
public:
    EnemyTank(float xpos, float ypos, float ang, std::string tanakModel, float size);
    virtual void tick(float tickl);
    virtual ~EnemyTank();
};

