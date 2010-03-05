#ifndef MALELIZARD_H
#define MALELIZARD_H

#include "lizard.h"

class MaleLizard : public Lizard {
public:
    MaleLizard(NodePath node);
    MaleLizard(const string &model);
   ~MaleLizard();

    void init();

    static void player_did_bobbing(const Event *theEvent, void *data);
    static const double BOBBING_WAITING_TIME = 3.0;
private:
    virtual void act();

    virtual void wander();
    virtual void chase();
    virtual void bite();
    virtual void bob();
    virtual void flee();

    NodePath maleSymbol;

    double last_bobbing_done;
    bool waiting_player_decide;
};

#endif
