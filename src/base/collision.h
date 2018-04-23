/*
 * File:   collision.h
 * Author: tassalon
 *
 * Created on 11 de Junho de 2010, 15:04
 */

#ifndef COLLISION_H
#define	COLLISION_H

#include "collisionHandlerPusher.h"
#include "collisionNode.h"
#include "collisionSphere.h"
#include "pandaFramework.h"
#include "timeControl.h"


class collision {

public:
    collision();
    collision(const collision& orig);
    virtual ~collision();

    void collisionNpcFast(NodePath* no, float x, float y, float z, float raio);
    void collisionNpcSlow(NodePath* no, float x, float y, float z, float raio);

    void esferaCollision(NodePath* no, float x, float y, float z, float raio);

    void playerCollision(NodePath* no);

    //SingleTon
    static collision* get_instance();

    void detectaColisaoFps();
     void detectaColisaoSeg();
     bool get_colisao();
      void set_colisao(bool c);

      static void event_pframe_collision(const Event *, void *data);
    static void event_psegundo_collison(const Event *, void *data);


private:
    static bool instanceFlag;
    static collision *single;
    static bool colisao;
};

#endif	/* COLLISION_H */

