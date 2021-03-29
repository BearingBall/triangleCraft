#ifndef DESTROYBUILDPOINTER_H
#define DESTROYBUILDPOINTER_H
#include "Triangle.h"

class DestroyBuildPointer final
{
public:
    std::shared_ptr<Triangle>* destroy;
    bool isDestroySeted = false;
    std::shared_ptr<Triangle>* build;
    bool isBuildSeted = false;
    Type buildType;
};

#endif // DESTROYBUILDPOINTER_H
