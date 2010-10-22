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
#include "menu.h"


bool collision::instanceFlag = false;
collision* collision::single = NULL;
CollisionHandlerPusher pusher;
CollisionTraverser* collTravPlayer;
CollisionTraverser* collTravSlow;


collision::collision() {
     collTravPlayer = new CollisionTraverser();  //tratamento de colisões para o jogador e a siriema
     collTravSlow  = new CollisionTraverser();  //tratamento de colisões para animais lentos como os lizards
}

collision::collision(const collision& orig) {

}

collision::~collision() {

}

//ADICIONA NÓ DE COLISÃO AO JOGADOR, UM HANDLER E UM TRAVERSER PARA TRATAR AS COLISÕES
//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE player DENTRO DO MÉTODO load_player().
void collision::playerCollision(NodePath* node){
    if(Menu::get_instance()->get_colisao()){

        CollisionNode* cNode = new CollisionNode("Player"); //cria nó de colisão
        cNode->add_solid(new CollisionSphere(0, 0, -20, 180.0)); //cria solido colisão (esfera) e add ao nó de colisão
        NodePath player = node->attach_new_node(cNode);
      //  player.show();
        pusher.add_collider(player, *node);
        collTravPlayer->add_collider(player , &pusher);
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
      if(Menu::get_instance()->get_colisao()){

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
    if(Menu::get_instance()->get_colisao()){

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
   if(Menu::get_instance()->get_colisao()){//verifica se a colisão foi ativada pelo jogador

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
    if(Menu::get_instance()->get_colisao()){//verifica se a colisão foi ativada pelo jogador
    collTravPlayer->traverse(Simdunas::get_window()->get_render());
    }
}
//ESSE MÉTODO ESTÁ SENDO USADO NA CLASSE timeControl NO MÉTODO event_psegundo_real()
//ele é responsável por realizar o tratamento de colisões dos lagartos NPCs. (animais lentos)
void collision::detectaColisaoSeg(){
    if(Menu::get_instance()->get_colisao()){//verifica se a colisão foi ativada pelo jogador
    collTravSlow->traverse(Simdunas::get_window()->get_render());
    }
}

