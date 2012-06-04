#ifndef MALELIZARD_H
#define MALELIZARD_H

#include "lizard.h"

class MaleLizard : public Lizard {
public:
    MaleLizard(NodePath node);
    virtual ~MaleLizard();

    void init();

    static void player_did_bobbing(const Event *theEvent, void *data);
    static const double BOBBING_WAITING_TIME;// = 3.0;

    virtual void be_bited(float relative_size);
private:
    virtual void act();

    virtual void wander();
    virtual void chase();
    virtual void bite();
    virtual void bob();
    //virtual void flee();

    NodePath male_symbol;

    double last_bobbing_done;
    bool waiting_player_decide;

    float eat_thr;
};

#endif
