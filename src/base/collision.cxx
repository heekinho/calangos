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
//para desativar a colisão no jogo basta colocar false neste variável:
bool collision::colisao = true;


collision::collision() {
   
     collTravPlayer = new CollisionTraverser();  //tratamento de colisões para o jogador e a siriema
     collTravSlow  = new CollisionTraverser();  //tratamento de colisões para animais lentos como os lizards

    event_handler->add_hook("EV_SEGUNDO_REAL", event_psegundo_collison, this);
    event_handler->add_hook("EV_PASSFRAME", event_pframe_collision, this);
   
}

 void collision::event_pframe_collision(const Event *, void *data){
       get_instance()->detectaColisaoFps();
}


 void collision::event_psegundo_collison(const Event *, void *data){
         get_instance()->detectaColisaoSeg();
        }
 
collision::collision(const collision& orig) {

}

collision::~collision() {
       event_handler->remove_hooks_with(this);
}

//ADICIONA NÓ DE COLISÃO AO JOGADOR, UM HANDLER E UM TRAVERSER PARA TRATAR AS COLISÕES
//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE player DENTRO DO MÉTODO load_player().
void collision::playerCollision(NodePath* node){
    if(get_colisao()){
          
        CollisionNode* cNode = new CollisionNode("Player"); //cria nó de colisão
        cNode->add_solid(new CollisionSphere(0, 0, -20, 180.0)); //cria solido colisão (esfera) e add ao nó de colisão
        NodePath cplayer = node->attach_new_node(cNode);
      //  player.show();
        pusher.add_collider(cplayer, *node);
        collTravPlayer->add_collider(cplayer , &pusher);
    }
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
  //exemplo de como usar o método: --> collision::get_instance()->collisionNpcFast(&node, 0, 0, 0, 10.0);
void collision::collisionNpcFast(NodePath* node, float x, float y, float z, float raio){
      if(get_colisao()){

      CollisionNode* cNode = new CollisionNode("NPC");
      cNode->add_solid(new CollisionSphere(x, y, z, raio));
      NodePath npc = node->attach_new_node(cNode);
      //npc.show();
      pusher.add_collider(npc, *node);
      collTravPlayer->add_collider(npc , &pusher);
   }
}
   //sendo usado na classe lizard no método construtor.
void collision::collisionNpcSlow(NodePath* node, float x, float y, float z, float raio){
    if(get_colisao()){

    CollisionNode* cNode = new CollisionNode("NPC");
    cNode->add_solid(new CollisionSphere(x, y, z, raio));
    NodePath npc = node->attach_new_node(cNode);
     //  npc.show();
      pusher.add_collider(npc, *node);
      collTravSlow->add_collider(npc , &pusher);

    }
  }

//Adiciona sólido de colisão aos vegetais, sendo usado na classe vegetal
//Exemplo de como usar esse método: collision::get_instance()->esferaCollision(&node,x,y,z,raio);
void collision::esferaCollision(NodePath* node, float x, float y, float z, float raio){
   if(get_colisao()){//verifica se a colisão foi ativada pelo jogador

       CollisionNode* cNode = new CollisionNode("no");
      cNode->add_solid(new CollisionSphere(x, y, z, raio));
      NodePath no = node->attach_new_node(cNode);
    //  no.show();
  }
}

//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE timeControl NO MÉTODO event_pframe(parâmetros);
//ele é responsável por realizar o tratamento de colisões do jogador e da Sirema (animais rápidos)
//devendo, por tanto, ser utilizado a cada frame.
void collision::detectaColisaoFps(){
    if(get_colisao() &&   collTravPlayer->get_num_colliders() > 1  ){//verifica se a colisão foi ativada pelo jogador
    collTravPlayer->traverse(render);
    }
}
//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE timeControl NO MÉTODO event_psegundo_real()
//ele é responsável por realizar o tratamento de colisões dos lagartos NPCs. (animais lentos)
void collision::detectaColisaoSeg(){
    if(get_colisao() &&   collTravSlow->get_num_colliders() > 1){//verifica se a colisão foi ativada pelo jogador
    collTravSlow->traverse(render);
    }
}

bool collision::get_colisao() {
    return colisao;
}

void collision::set_colisao(bool c) {
    colisao = c;
}

