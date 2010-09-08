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



class collision {

public:
    collision();
    collision(const collision& orig);
    virtual ~collision();

    void collisionNpcFast(NodePath* no, float x, float y, float z, float raio);
    void collisionNpcSlow(NodePath* no, float x, float y, float z, float raio);

    void esferaCollision(NodePath* no, float x, float y, float z, float raio);

    NodePath* playerCollision(NodePath* no);

    //SingleTon
    static collision* get_instance();

    void detectaColisaoFps();
     void detectaColisaoSeg();


private:
    static bool instanceFlag;
    static collision *single;
};

#endif	/* _COLLISION_H */

