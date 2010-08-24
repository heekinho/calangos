/* 
 * File:   collision.cxx
 * Author: tassalon
 * 
 * Created on 11 de Junho de 2010, 15:04
 */

#include "collision.h"
#include "collisionHandlerPusher.h"
#include "collisionNode.h"
#include "collisionSphere.h"
#include "collisionTube.h"
#include "simdunas.h"
#include "player.h"

bool collision::instanceFlag = false;
collision* collision::single = NULL;
CollisionHandlerPusher pusher;
CollisionTraverser* collTravPlayer;
CollisionTraverser* collTravSlow;
      

collision::collision() {
     collTravPlayer = new CollisionTraverser();
     collTravSlow  = new CollisionTraverser();
}

collision::collision(const collision& orig) {

}
 
collision::~collision() {
}

//ADICIONA NÓ DE COLISÃO AO JOGADOR, UM HANDLER E UM TRAVERSER PARA TRATAR AS COLISÕES
//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE player DENTRO DO MÉTODO load_player().
NodePath* collision::playerCollision(NodePath* node){
        CollisionNode* cNode = new CollisionNode("Player"); //cria nó de colisão
  
        cNode->add_solid(new CollisionSphere(0, 0, -20, 180.0)); //cria solido colisão (esfera) e add ao nó de colisão
        NodePath player = node->attach_new_node(cNode);
        //player.show();
        pusher.add_collider(player, *node);
        collTravPlayer->add_collider(player , &pusher);
}

collision* collision::get_instance() {
	if(!instanceFlag) {
        single = new collision();
        instanceFlag = true;
    }
    return single;
}
  //ADICIONA NÓS DE COLISÃO AOS NPCs
  //sendo usado na classe predator no método construtor.
  //exemplo de como usar o método: --> collision::get_instance()->npcCollision(&node, 0, 0, 0, 10.0);
void collision::collisionNpcFast(NodePath* node, float x, float y, float z, float raio){
         
      CollisionNode* cNode = new CollisionNode("NPC");      
      cNode->add_solid(new CollisionSphere(x, y, z, raio));
      NodePath npc = node->attach_new_node(cNode);
    //  npc.show();
     pusher.add_collider(npc, *node);
    collTravPlayer->add_collider(npc , &pusher);
  }
   //sendo usado na classe lizard no método construtor.
void collision::collisionNpcSlow(NodePath* node, float x, float y, float z, float raio){

      CollisionNode* cNode = new CollisionNode("NPC");
      cNode->add_solid(new CollisionSphere(x, y, z, raio));
      NodePath npc = node->attach_new_node(cNode);
    //  npc.show();
     pusher.add_collider(npc, *node);
     collTravSlow->add_collider(npc , &pusher);
  }

//Adiciona sólido de colisão aos vegetais, sendo usado na classe vegetal
//Exemplo de como usar esse método: collision::get_instance()->vegetalCollision(&node);
void collision::vegetalCollision(NodePath* node, float x, float y, float z, float raio){

      CollisionNode* cNode = new CollisionNode("vegetal");
     // cNode->add_solid(new CollisionTube(0, -3, 0, 0, -10, 5, 20));
      cNode->add_solid(new CollisionSphere(x, y, z, raio));
      NodePath vegetal = node->attach_new_node(cNode);
      //vegetal.show();
  }


//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE timeControl NO MÉTODO event_pframe(parâmetros);
//ele é responsável por realizar o tratamento de colisões do jogador e da Sirema (animais rápidos)
//devendo, por tanto, ser utilizado a cada frame.
void collision::detectaColisaoFps(){
    collTravPlayer->traverse(Simdunas::get_window()->get_render());
}
//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE timeControl NO MÉTODO event_psegundo_real()
//ele é responsável por realizar o tratamento de colisões dos lagartos NPCs. (animais lentos)
void collision::detectaColisaoSeg(){
    collTravSlow->traverse(Simdunas::get_window()->get_render());
}

