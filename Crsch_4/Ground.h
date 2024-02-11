#pragma once
#include "BaseObject.h"
class Ground :
    public BaseObject{
public:
    Ground();
    virtual void tick(float tickl);
    virtual ~Ground();
};

