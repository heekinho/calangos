#ifndef YOUNGLIZARD_H
#define YOUNGLIZARD_H

#include "lizard.h"

class YoungLizard : public Lizard {
public:
    YoungLizard(NodePath node);
    YoungLizard(const string &model);
   ~YoungLizard();

    void init();
};

#endif