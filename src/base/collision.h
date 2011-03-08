/*
 * File:   collision.h
 * Author: tassalon
 *
 * Created on 11 de Junho de 2010, 15:04
 */

#ifndef _COLLISION_H
#define	_COLLISION_H
#include "collisionHandlerPusher.h"
#include "collisionNode.h"
#include "collisionSphere.h"
#include "menu.h"


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


private:
    static bool instanceFlag;
    static collision *single;
    static bool colisao;
};

#endif	/* _COLLISION_H */

