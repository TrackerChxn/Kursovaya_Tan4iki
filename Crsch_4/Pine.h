#pragma once
#include "BaseObject.h"
class Pine :
    public BaseObject
{
    public:
    Pine(float xpos, float ypos);
    virtual void tick(float tickl);
    virtual ~Pine();
};

