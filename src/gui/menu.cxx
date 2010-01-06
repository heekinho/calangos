

#include "menu.h"

#include "nodePath.h"
#include "textNode.h"
#include "mouseButton.h"
#include "pgSliderBar.h"
#include "fontPool.h"
#include "eventQueue.h"

# define MINUTO_DIA_VIRTUAL 3  //valor default (se mudar mude só aqui)



TextNode* Menu::tex = NULL;
NodePath Menu::node_texto = NULL;
NodePath Menu::background_over = NULL;
bool Menu::rodar = false;
bool Menu::controle = false;
char* Menu::tecla = NULL;
Menu * Menu::instance = NULL;


//mudei de lugar
NodePath Menu::button_sair = NULL;
NodePath Menu::button_restart = NULL;
NodePath Menu::button_grafico = NULL;

NodePath Menu::logo = NULL;
Player::lizardEpecie Menu::especie=Player::eurolophosaurus;//a especie dfault



Menu::Menu(WindowFramework *window){
	this->_framework = window->get_panda_framework();
        this->minuto_dia_virtual=0;
        this->flag_stop_time_pause=false;


}

#include "auto_bind.h"
#include "animatedObjetoJogo.h"
void Menu::start_Menu(){

		Simdunas::get_window()->set_background_type(WindowFramework::BT_black);
    
		//carregando animação inicial da Tela principal
		lagarto = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(),"models/lizards/cnemidophorus/male/model");
		lagarto.set_scale(0.08,0.08,0.08);
		lagarto.set_pos(0,35,-2);
		lagarto.set_h(45);
		lagarto.set_p(20);

//		/* Animação */
		Simdunas::get_window()->load_model(lagarto, "models/lizards/cnemidophorus/male/walk");
		auto_bind(lagarto.node(), anims, PartGroup::HMF_ok_part_extra |
				PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
		anims.loop_all(false);
                
                /////Lagartos que vão ser mostrados na tela de configuração
                ////quando forem selecionados

             ////////////////////////Tropidurus////////////////////

                tropidurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(),"models/lizards/tropidurus/male/model");
		tropidurus.set_scale(0.04,0.04,0.04);
		tropidurus.set_pos(4,35,-3);
		tropidurus.set_h(45);
		tropidurus.set_p(20);


            	/* Animação */
		Simdunas::get_window()->load_model(tropidurus, "models/lizards/tropidurus/male/walk");
		auto_bind(tropidurus.node(), anims, PartGroup::HMF_ok_part_extra |
				PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
		anims.loop_all(false);
                tropidurus.hide();
    //////////////////////////Eurolophosauros/////////////////
                eurolophosasurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(),"models/lizards/eurolophosaurus/male/model");
		eurolophosasurus.set_scale(0.04,0.04,0.04);
		eurolophosasurus.set_pos(4,35,-3);
		eurolophosasurus.set_h(45);
		eurolophosasurus.set_p(20);

            	/* Animação */
		Simdunas::get_window()->load_model(eurolophosasurus, "models/lizards/eurolophosaurus/male/walk");
		auto_bind(eurolophosasurus.node(), anims, PartGroup::HMF_ok_part_extra |
				PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
		anims.loop_all(false);
                eurolophosasurus.hide();
               //////////////////Cnemidophorus////////////
                cnemidophorus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(),"models/lizards/cnemidophorus/male/model");
		cnemidophorus.set_scale(0.04,0.04,0.04);
		cnemidophorus.set_pos(4,35,-3);
		cnemidophorus.set_h(45);
		cnemidophorus.set_p(20);

//		/* Animação */
		Simdunas::get_window()->load_model(cnemidophorus, "models/lizards/cnemidophorus/male/walk");
		auto_bind(cnemidophorus.node(), anims, PartGroup::HMF_ok_part_extra |
				PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
		anims.loop_all(false);
                cnemidophorus.hide();



              ///imagem do logo
		logo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/calangos.png");
		logo.set_scale(0.1);
		logo.set_pos(0.0,0,0.6);
		

                /////imagem com o título de menu de configurações

		
		
		// informa_Inicio("  CALANGOS  ");
   
        //imagens que vão ser carregads no botao
        NodePath tela = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/iniciar");
              NodePath emcima = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/clicar");
         NodePath pos_click = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/pos_click");
         NodePath config = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/config");
       
             tela.detach_node();
             pos_click.detach_node();
             emcima.detach_node();
             config.detach_node();


           ///////////////////////criando o botao iniciar/////////////////////////////////////////////////////////////////
         botao_iniciar = new PGButton("iniciar");
    
                         
  		botao_iniciar->setup(tela,pos_click,emcima,pos_click);//colocando a imagem no botao               
  		
        
  		button_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_iniciar);
        
                     button_np.set_scale(0.25,0.25,0.25);
                   //button_np.set_color(0.2, 0.5, 0.2, 0.0);
                     button_np.set_pos(-0.5, 0.4, -0.25);
        
        //setando o frame do botao
        //as coordenadas do frame é em relação ao botao
        botao_iniciar->set_frame(-0.4 , 0.4 , -0.4, 0.4 );
        
       //////////////////////criando o botao sair//////////////////////////////////////////////////////////////
                NodePath saindo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/sair");

                saindo.detach_node();


                botao_sair = new PGButton("Sair");

                botao_sair->setup(saindo);

                nod_sair = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_sair);
                nod_sair.set_scale(0.21,0.21,0.21);
                nod_sair.set_pos(0.5, 0.4, -0.25);
                botao_sair->set_frame(-0.4, 0.4, -0.4, 0.4);

    ////////////////////////criando o botao configurações////////////////////////////////////////////////////////////////
     
          botao_configuracoes=new PGButton("configuracoes");
          botao_configuracoes->setup(config);//colocando a imagem no botão

          nod_config_egg=Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_configuracoes);
          nod_config_egg.set_scale(0.55,0.25,0.25);
	  nod_config_egg.set_pos(0.0,0.4,-0.25);
	  botao_configuracoes->set_frame(-0.4 , 0.4 , -0.4, 0.4 );
 
         //adicionando os eventos dos botões//////////////////////////
         Simdunas::get_evt_handler()->add_hook(botao_iniciar->get_click_event(MouseButton::one()),event_clik,this);
         Simdunas::get_evt_handler()->add_hook(botao_sair->get_click_event(MouseButton::one()),out,this);
         Simdunas::get_evt_handler()->add_hook(botao_configuracoes->get_click_event(MouseButton::one()),configure,this);
   
         }
        
  	 

Menu::~Menu(){}



//método estatico para mostrar informações de inicialização
//será chamado por cada objeto do mundo passando a frase de aviso
void  Menu::informa_segundos(string aviso){
    
    if(tex==NULL){

        
        tex = new TextNode("inicio");
        tex->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));
        tex->set_text(aviso);
       
        node_texto = Simdunas::get_window()->get_aspect_2d().attach_new_node(tex);
        node_texto.set_scale(0.17);
        node_texto.set_pos(-1.2, 0, 0.35);
        node_texto.set_color(0.87, 0.72, 0.52);
    }
    else
        tex->set_text(aviso);
        
   



}

void Menu::event_clik(const Event*,void *data){
    Menu * men=(Menu*)data;

	men->botao_iniciar->set_active(false);
    men->remove_tela_menu();
	if(men->minuto_dia_virtual==0){
		men->minuto_dia_virtual=3;
	}
   
    men->rodar=true;

}


void Menu::configure(const Event*,void *data){

     Menu * config=(Menu*)data;

                

                config->hide_tela_principal();//escondendo tela principal

                //verifica se eh a primeira vez q ta sendo chamado a configuração
                //se não for não será preciso ler tudo dinovo.
                if(config->title_config.is_empty()){
                     config->ratio=0;


                     ///carregando titulo do menu de configurações
                     config->title_config = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/config_jogo.png");
                     config->title_config.set_scale(0.1);
                     config->title_config.set_pos(0.0,0,0.8);


                     //relogio virtual////////////////////

                       config->tempo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/tempo");
                       config->tempo.set_scale(1,0.0,0.2);
                       config->tempo.set_pos(-0.8,0.0,0.6);

                       ///////////relogio_frse//////////////////////////////////

                       config->relogio_frase = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/relogio_frase");
                       config->relogio_frase.set_scale(1.8,0.0,0.2);
                       config->relogio_frase.set_pos(-0.1,0.0,0.4);


              /////////////////////Mostrando botão jogar////////////////////////

                     
					 
					 config->button_np.show();
					 config->button_np.set_pos(0.0,0.0,-0.8);

                     
    

                      //////Criando botão voltar
    NodePath botao_voltar=Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/voltar");
                     botao_voltar.detach_node();
                     config->botao_voltar=new PGButton("voltar");
                     config->botao_voltar->setup(botao_voltar);
                     config->nod_botao_voltar=Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_voltar);
                     config->nod_botao_voltar.set_scale(0.21,0.21,0.21);
                     config->nod_botao_voltar.set_pos(0.5,0.0,-0.8);
                     config->botao_voltar->set_frame(-0.4 , 0.4 , -0.4, 0.4 );

      ///adicionando o evento no botão voltar
     Simdunas::get_evt_handler()->add_hook(config->botao_voltar->get_click_event(MouseButton::one()),event_voltar_funcao,config);

                      
//////////////////////////////////////////Opção de configuração Tempo Virtual//////////

                                config->slid = new PGSliderBar("slid");
                                config->slid->set_range(1, 60);
                                config->nod_noid = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->slid);

                                config->slid->setup_slider(false, 1.0, 0.06, 0.01);
                                

                                config->nod_noid.set_scale(0.5,1.0,1.0);
                                config->nod_noid.set_pos(-0.84, 0.0, 0.27);


                      //criando o botão mais//////////////////////////////////////////////////////////
    NodePath botao_mais = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/mais");
    botao_mais.detach_node();
                        config->botao_mais = new PGButton("mais");
                        config->botao_mais->setup(botao_mais);
                        config->nod_mais = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_mais);
                        config->nod_mais.set_scale(0.12);
                        config->nod_mais.set_pos(-0.53, 0.0, 0.28);
                        config->botao_mais->set_frame(-0.4, 0.4, -0.4, 0.4);


                          Simdunas::get_evt_handler()->add_hook(config->botao_mais->get_click_event(MouseButton::one()),direita,config);

                          ////////o default será três? minutos então ja começa como se tivesse dado três clicks no +
						  for(int i=0; i<MINUTO_DIA_VIRTUAL;i++){
//                            const Event *ev_direita = new Event(config->botao_mais->get_click_event(MouseButton::one()));
//                            Simdunas::get_evt_queue()->queue_event(ev_direita);
                                       //  cout<<"Minuto dia virtual: "<<config->minuto_dia_virtual<<endl;

                                                      //melhor que ficar enfileirando eventos!!!
                                                      direita(NULL,config);
						  }
                         
                          //criando o botão menos///////////////////////////////
    NodePath botao_menos = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/menos");
    botao_menos.detach_node();

            config->botao_menos = new PGButton("menos");
            config->botao_menos->setup(botao_menos);
            config->nod_menos = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_menos);
            config->nod_menos.set_scale(0.12);
            config->nod_menos.set_pos(-1.15, 0.0, 0.28);
            config->botao_menos->set_frame(-0.4, 0.4, -0.4, 0.4);
            Simdunas::get_evt_handler()->add_hook(config->botao_menos->get_click_event(MouseButton::one()), esquerda, config);

          ///////opção de configuração de Escolha da Espécie/////////////
             config->escolha_especie = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/especie.png");
                       config->escolha_especie.set_scale(0.06,0.0,0.06);
                       config->escolha_especie.set_pos(-0.68,0.0,0.03);

                       //carregando o marcador/////////
                       config->marcador=Simdunas::get_window()->load_model(config->escolha_especie,"models/buttons/marcador.png");
                            config->marcador.set_scale(0.2, 0.0, 0.2);
                            config->marcador.set_pos(4.0,0.0,-4.7);
   ///////Botões para escolha da especie/////////////////

                       //botão TROPIDURUS///////////////

    NodePath botao_tropidurus=Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/tropidurus");
                     botao_tropidurus.detach_node();
                     config->botao_tropidurus=new PGButton("tropidurus");
                     config->botao_tropidurus->setup(botao_tropidurus);
                     config->nod_bot_tropidurus=Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_tropidurus);
                     config->nod_bot_tropidurus.set_scale(0.5,0.1,0.18);
                     config->nod_bot_tropidurus.set_pos(-0.85,0.0,-0.1);
                     config->botao_tropidurus->set_frame(-0.4 , 0.4 , -0.4, 0.4 );

   Simdunas::get_evt_handler()->add_hook(config->botao_tropidurus->get_click_event(MouseButton::one()), tropidurus_funcao, config);

                       ///////botão EUROLOPHOSAURUS //////////////////////////
   NodePath botao_eurolophosaurus=Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/eurolophosaurus");
                     botao_eurolophosaurus.detach_node();
                     config->botao_eurolophosaurus=new PGButton("eurolophosaurus");
                     config->botao_eurolophosaurus->setup(botao_eurolophosaurus);
                     config->nod_bot_eurolophosaurus=Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_eurolophosaurus);
                     config->nod_bot_eurolophosaurus.set_scale(0.6,0.1,0.18);
                     config->nod_bot_eurolophosaurus.set_pos(-0.8,0.0,-0.25);
                     config->botao_eurolophosaurus->set_frame(-0.4 , 0.4 , -0.4, 0.4 );

  Simdunas::get_evt_handler()->add_hook(config->botao_eurolophosaurus->get_click_event(MouseButton::one()), eurolophosaurus_funcao, config);


                       ///////botão CNEMIDOPHORUS //////////////////////////
  NodePath botao_cnemidophorus=Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/cnemidophorus");
                 botao_cnemidophorus.detach_node();
                 config->botao_cnemidophorus=new PGButton("cnemidophorus");
                 config->botao_cnemidophorus->setup(botao_cnemidophorus);
                 config->nod_bot_cnemidophorus=Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_cnemidophorus);
                 config->nod_bot_cnemidophorus.set_scale(0.6,0.1,0.18);
                 config->nod_bot_cnemidophorus.set_pos(-0.8,0.0,-0.4);
                 config->botao_cnemidophorus->set_frame(-0.4 , 0.4 , -0.4, 0.4 );

 Simdunas::get_evt_handler()->add_hook(config->botao_cnemidophorus->get_click_event(MouseButton::one()), cnemidophorus_funcao, config);

 Simdunas::get_evt_handler()->add_hook(config->slid->get_adjust_event(),slide,config);
            //o lagarto default é o eurolophosaurus
            eurolophosaurus_funcao(NULL,config);
                }
                else{

                    config->show_tela_configuracao();
                }
        
}

void Menu::tropidurus_funcao(const Event*, void *data){
      Menu * t=(Menu*)data;

    
      t->marcador.set_pos(4.0,0.0,-2.2);//movendo o marcador


      switch (especie){

        case Player::cnemidophorus:
            t->cnemidophorus.hide();
            break;


        case Player::eurolophosaurus:
            t->eurolophosasurus.hide();
            break;

         default:
            break;
    }
      especie=Player::tropidurus;
      t->tropidurus.show();
      

}

void Menu::eurolophosaurus_funcao(const Event*, void* data){
     Menu * e=(Menu*)data;

     
     e->marcador.set_pos(4.0,0.0,-4.7);//movendo o marcador
     
     e->lagarto.hide();

       switch (especie){

        case Player::tropidurus:
            e->tropidurus.hide();
            break;


        case Player::cnemidophorus:
            e->cnemidophorus.hide();
            break;

         default:
            break;
    }

     
    
    especie=Player::eurolophosaurus;
     e->eurolophosasurus.show();
     

}

void Menu::cnemidophorus_funcao(const Event*, void* data){
     Menu * c=(Menu*)data;

   
     c->marcador.set_pos(4.0,0.0,-7.2);//movendo o marcador

      switch (especie){

        case Player::tropidurus:
            c->tropidurus.hide();
            break;


        case Player::eurolophosaurus:
            c->eurolophosasurus.hide();
            break;

         default:
            break;
    }

     especie=Player::cnemidophorus;
     c->cnemidophorus.show();
     

}
void Menu::slide(const Event*, void* data){
Menu * slide=(Menu*)data;

	  slide->minuto_dia_virtual=(int)slide->slid->get_value();
	  ostringstream letra;//convertendo float em string
	  letra<<slide->minuto_dia_virtual;
      std::string st(letra.str());
    
      Menu::informa_segundos(st);

/*cout<<"Chamou Slide"<<endl;
cout<<"Valor :"<<(int)slide->slid->get_value()<<endl;
cout<<"Valor Minuto_dia_Virtual Slide:"<<slide->minuto_dia_virtual<<endl;*/


}
void Menu::direita(const Event*, void* data){

     Menu * d=(Menu*)data;

     if(d->minuto_dia_virtual<60){
		d->minuto_dia_virtual++;
		 
     ostringstream letra;//convertendo float em string
	 
	 
	 //TimeControl::virtualTime = d->minuto_dia_virtual;

	 letra<<d->minuto_dia_virtual;
     std::string st(letra.str());
    
     Menu::informa_segundos(st);

	    /*cout<<"Valor :"<<(int)d->slid->get_value()<<endl;
		cout<<"Valor Minuto_dia_Virtual Direita:"<<d->minuto_dia_virtual<<endl;*/
	 
		d->slid->set_value(d->minuto_dia_virtual);
     }

}
void Menu::esquerda(const Event*, void* data){

     Menu * d=(Menu*)data;

    if(d->minuto_dia_virtual>1){
		d->minuto_dia_virtual--;
		 
     ostringstream letra;//convertendo float em string
	 
	 
	 //TimeControl::virtualTime = d->minuto_dia_virtual;

	 letra<<d->minuto_dia_virtual;
     std::string st(letra.str());
    
     Menu::informa_segundos(st);

	    /*cout<<"Valor :"<<(int)d->slid->get_value()<<endl;
		cout<<"Valor Minuto_dia_Virtual Esquerda:"<<d->minuto_dia_virtual<<endl;*/
		d->slid->set_value(d->minuto_dia_virtual);
	}
}

void Menu::event_voltar_funcao(const Event*, void* data){
    Menu * voltar=(Menu*)data;

    voltar->hide_tela_configuracao();
    voltar->show_tela_principal();

}

int Menu::get_minuto_dia_virtual(){
    return minuto_dia_virtual;
}
Player::lizardEpecie Menu::get_especie(){

    return especie;
}

bool Menu::get_flag_stop_time_pause(){

    return flag_stop_time_pause;
}

bool Menu::get_rodar(){
    return rodar;
}

void Menu::chama_pause_game(const Event*, void* data){
     Menu * voltar_jogo=(Menu*)data;
     voltar_jogo->pause_game();

}

void Menu::pause_game(){

    if(flag_stop_time_pause){
        TimeControl::get_instance()->set_stop_time(false);//se o jogo estiver pausado, ao pressionar esc novamente volta ao normal
        flag_stop_time_pause=false;

        logo.remove_node();
        nod_botao_voltar_jogo.remove_node();
        nod_sair.hide();
    }
    else{
    	Session::get_instance()->stop_animations();
        if(!TimeControl::get_instance()->get_stop_time()){//se o tempo ja estiver parado ele naum pausa o jogo
        logo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/pausa.png");
        logo.set_scale(0.06);
        logo.set_pos(0.0, 0, 0.8);

                          nod_sair.show();
                          nod_sair.set_pos(0.0,0.0,-0.5);

  ///////////////////criando botão voltar ao jogo/////////////////////
  NodePath nod_voltar_jogo=Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/continuar");
           nod_voltar_jogo.detach_node();
             botao_voltar_jogo=new PGButton("voltar ao jogo");
             botao_voltar_jogo->setup(nod_voltar_jogo);
             nod_botao_voltar_jogo=Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_voltar_jogo);
             nod_botao_voltar_jogo.set_scale(0.9,0.1,0.22);
             nod_botao_voltar_jogo.set_pos(0.0,0.0,0.0);
             botao_voltar_jogo->set_frame(-0.4 , 0.4 , -0.4, 0.4 );

  Simdunas::get_evt_handler()->add_hook(botao_voltar_jogo->get_click_event(MouseButton::one()), chama_pause_game, this);
           
        
        TimeControl::get_instance()->set_stop_time(true);
        flag_stop_time_pause = true;
        }
    }
}

void Menu::tela_over(Session *nsession){

	this->session = nsession;
    
	
            //Tela de game over
    frame_tela=new PGVirtualFrame("fundo_tela");
    frame_tela->setup(1,2);

  background_over = Simdunas::get_window()->get_aspect_2d().attach_new_node(frame_tela);
  background_over.set_pos(-0.5,0,-1);
  background_over.set_transparency(TransparencyAttrib::M_alpha);
  background_over.set_alpha_scale(0.0);

  logo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/fimdojogo.png");
  logo.set_scale(0.03);
  logo.set_pos(0.0,0,0.8);
   // Simdunas::get_window()->get_aspect_2d().attach_new_node(logo);
   //informa_Inicio("FIM DO JOGO!!!!");
	
	int morte=Session::get_instance()->get_causa_mortis();//pegando causa da morte
	
	switch(morte){//mostrando causa da morte
	case DESNUTRICAO: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/desnutricao.png");
		indica_morte.set_scale(0.065,0.0,0.09);
		indica_morte.set_pos(-0.05, 0.0, 0.45);
		break;

	case DESIDRATACAO: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/desidratacao.png");
		indica_morte.set_scale(0.065,0.0,0.09);
		indica_morte.set_pos(-0.05, 0.0, 0.45);
		break;

	case ALTA_TEMPERATURA: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/temperatura_alta.png");
		indica_morte.set_scale(0.065,0.0,0.09);
		indica_morte.set_pos(-0.1, 0.0, 0.45);
		break;

	case BAIXA_TEMPERATURA: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/temperatura_baixa.png");
		indica_morte.set_scale(0.065,0.0,0.09);
		indica_morte.set_pos(-0.1, 0.0, 0.45);
		break;

	case MORTE_IDADE: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/morte_idade.png");
		indica_morte.set_scale(0.065,0.0,0.09);
		indica_morte.set_pos(-0.1, 0.0, 0.45);
		break;

		default : break;
	
	} 

  
NodePath im_reiniciar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/reiniciar");
NodePath im_grafico = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/grafico");
//NodePath im_sair = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/sair");  
im_reiniciar.detach_node();
im_grafico.detach_node();
//im_sair.detach_node();


////////////////////////////botoes
  
    	botao_restart = new PGButton("restart");
  	botao_restart->setup(im_reiniciar);
  	
       	button_restart =  Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_restart);
  	button_restart.set_scale(0.3);
    	button_restart.set_pos(0.0, 0.0, 0.0);
        botao_restart->set_frame(-0.4 , 0.4 , -0.4, 0.4 );
        Simdunas::get_evt_handler()->add_hook(botao_restart->get_click_event(MouseButton::one()),restart,this);
		cout << "botao restart" << endl;
////////////////////////////////////////////
        /*botao_sair = new PGButton("sair");
  	botao_sair->setup(im_sair);
  	

  	button_sair = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_sair);
  	button_sair.set_scale(0.3);
  	
  	button_sair.set_pos(0.0, 0.0, -0.4);
        botao_sair->set_frame(-0.4 , 0.4 , -0.4, 0.4 );
        Simdunas::get_evt_handler()->add_hook(botao_sair->get_click_event(MouseButton::one()),out,this);
		cout << "botao sair" << endl;*/
		
		 nod_sair.show();//mostrando o botão (sair)
		 nod_sair.set_pos(0.0, 0.0, -0.4);
		
////////////////////////////////////////

        botao_graph = new PGButton("grafico");
  	botao_graph->setup(im_grafico);
  	
  	//button_grafico = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_graph);
  	//button_grafico.set_scale(0.3);
  	
  	//button_grafico.set_pos(0.0, 0.0, 0.4);
    //botao_graph->set_frame(-0.4 , 0.4 , -0.4, 0.4 );
    //Simdunas::get_evt_handler()->add_hook(botao_graph->get_click_event(MouseButton::one()),graph,this);
    //cout << "botao grafico" << endl;
  /////////////////////////////////////////fim dos botoes

  //while para esperar o evendo do click TEMPORARIO
  //while(Simdunas::get_framework()->do_frame(Thread::get_current_thread()) && controle==false){}
		
   //cout << "while" << endl;
 // controle=false;
  
  //removendo os nodepaths
 /* background_over.remove_node();
  button_sair.remove_node();
  button_restart.remove_node();
  button_grafico.remove_node();
  node_texto.remove_node();
  cout << "final" << endl;

  return tecla;*/

}

void Menu::hide_tela_over() {
    background_over.hide();
    nod_sair.hide();
    button_restart.hide();
   // button_grafico.hide();
   // node_texto.hide();
    logo.hide();
	indica_morte.hide();
}

void Menu::hide_tela_principal() {
    button_np.hide();
    nod_sair.hide();
    logo.hide();
    nod_config_egg.hide();
}

void Menu::hide_tela_configuracao(){

    title_config.hide();
    node_texto.hide();
    tempo.hide();
    relogio_frase.hide();
    nod_noid.hide();
    nod_mais.hide();
    nod_menos.hide();
    escolha_especie.hide();
    nod_bot_tropidurus.hide();
    nod_bot_eurolophosaurus.hide();
    nod_bot_cnemidophorus.hide();
    
    nod_botao_voltar.hide();

    switch (especie){

        case Player::tropidurus:
            tropidurus.hide();
            break;
        case Player::eurolophosaurus:
             eurolophosasurus.hide();
             break;

        case Player::cnemidophorus:
            cnemidophorus.hide();
            break;

         default:
            break;
    }

}
void Menu::hide_tela_pause(){
	logo.hide();
	nod_botao_voltar_jogo.hide();
	nod_sair.hide();

}

////////////remove todos os componentes(botões tútulos e etc.) de menu para que o jogo se inicie
void Menu::remove_tela_menu() {

    node_texto.remove_node();
    button_np.remove_node();
    nod_sair.hide(); //este não eh removido pois será utilizado em caso de pausa ou morte do calango
    lagarto.remove_node();
    logo.remove_node();
    nod_config_egg.remove_node();
    title_config.remove_node();
    nod_botao_ok.remove_node();
    nod_noid.remove_node();
    nod_mais.remove_node();
    nod_menos.remove_node();
    tempo.remove_node();
    relogio_frase.remove_node();
    title_config.remove_node();
    escolha_especie.remove_node();
    nod_bot_tropidurus.remove_node();
    nod_bot_eurolophosaurus.remove_node();
    nod_bot_cnemidophorus.remove_node();
    nod_botao_voltar.remove_node();
    tropidurus.remove_node();
    eurolophosasurus.remove_node();
    cnemidophorus.remove_node();
}

void Menu::show_tela_over() {
    background_over.show();
    nod_sair.show();
    button_restart.show();
    //button_grafico.show();
    //node_texto.show();
    logo.show();
	indica_morte.show();
}

void Menu::show_tela_pause(){
	logo.show();
	nod_botao_voltar_jogo.show();
	nod_sair.show();

}

void Menu::show_tela_principal(){

    button_np.show();
	button_np.set_pos(-0.5, 0.4, -0.25);//colocando o botão (Iniciar) novamente em seu lugar na tela principal
    nod_sair.show();
    logo.show();
    nod_config_egg.show();
    lagarto.show();
}

void Menu::show_tela_configuracao(){

    title_config.show();
    node_texto.show();
    tempo.show();
    relogio_frase.show();
    nod_noid.show();
    nod_mais.show();
    nod_menos.show();
    escolha_especie.show();
    nod_bot_tropidurus.show();
    nod_bot_eurolophosaurus.show();
    nod_bot_cnemidophorus.show();
    button_np.show();
	button_np.set_pos(0.0,0.0,-0.8);//colocando o botão (Iniciar) novamente em seu lugar na tela principal
    nod_botao_voltar.show();

    lagarto.hide();//escondendo o lagarto da tela principal

     switch (especie){//mostrando especie q tava selecionada

        case Player::tropidurus:
            tropidurus.show();
            break;
        case Player::eurolophosaurus:
             eurolophosasurus.show();
             break;

        case Player::cnemidophorus:
            cnemidophorus.show();
            break;

         default:
            break;
    }


}
void Menu::restart(const Event*, void* data){
    Menu *m=(Menu*)data;
    tecla="r";
    //controle=true;
	Session *session = (Session*)data;
	background_over.remove_node();
	button_sair.remove_node();
	button_restart.remove_node();
	button_grafico.remove_node();
	node_texto.remove_node();
	logo.remove_node();
    m->indica_morte.remove_node();
    m->nod_sair.hide();
	cout << "final r" << endl;

	session->receive_answer(tecla);
	//return tecla;

}
void Menu::out(const Event*, void* data){
//	Session::get_instance()->end_session();

    exit(0);//saindo direto, fechando o jogo
    //na tela de inicialização ou de game over
    
}
void Menu::graph(const Event*, void* data){
    //Menu *m=(Menu*)data;
    tecla="g";
   // controle=true;
	Session *session = (Session*)data;
	background_over.remove_node();
	button_sair.remove_node();
	button_restart.remove_node();
	button_grafico.remove_node();
	node_texto.remove_node();
	logo.remove_node();
	cout << "final g" << endl;

	session->receive_answer(tecla);
	//return tecla;
}


Menu* Menu::get_instance(){

    if(instance==NULL){

        instance=new Menu(Simdunas::get_window());
        return instance;

    }

    else{
        return instance;
    }

}

