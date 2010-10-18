




#include "menu.h"


#include "nodePath.h"
#include "textNode.h"
#include "mouseButton.h"
#include "pgSliderBar.h"
#include "fontPool.h"
#include "eventQueue.h"
#include "guiManager.h"
#include "audioManager.h"




TextNode* Menu::tex = NULL;
TextNode* Menu::tex_obj=NULL;
NodePath Menu::frameNode=NULL;
NodePath Menu::node_tex_obj=NULL;
NodePath Menu::node_texto = NULL;
NodePath Menu::background_over = NULL;
NodePath Menu::background_instrucoes = NULL;
NodePath Menu::background_icones = NULL;
bool Menu::rodar = false;
bool Menu::controle = false;
bool Menu::showing_creditos = false;
char* Menu::tecla = NULL;
Menu * Menu::instance = NULL;
//para desativar a colisão no jogo basta colocar false neste variável:
bool Menu::colisao = true;

//mudei de lugar
NodePath Menu::button_sair = NULL;
NodePath Menu::button_restart = NULL;
NodePath Menu::button_grafico = NULL;

NodePath Menu::logo = NULL;
Player::lizardEpecie Menu::especie = Player::eurolophosaurus; //a especie dfault

Menu::Menu(WindowFramework *window) {
    this->_framework = window->get_panda_framework();
    this->minuto_dia_virtual = 0;
    this->flag_stop_time_pause = false;

    Simdunas::get_framework()->define_key("escape", "Stop_Movie", stop_movie, this);

		
}

#include "auto_bind.h"
#include "animatedObjetoJogo.h"

void Menu::start_Menu() {

    play_movie("models/videos/vinheta_opcao_1_mpeg4.avi");


    Simdunas::get_window()->set_background_type(WindowFramework::BT_black);

    //carregando animação inicial da Tela principal
    lagarto = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/cnemidophorus/male/model");
    lagarto.set_scale(0.08, 0.08, 0.08);
    lagarto.set_pos(0, 35, -2);
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

    tropidurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/tropidurus/male/model");
    tropidurus.set_scale(0.04, 0.04, 0.04);
    tropidurus.set_pos(4, 35, -3);
    tropidurus.set_h(45);
    tropidurus.set_p(20);


    /* Animação */
    Simdunas::get_window()->load_model(tropidurus, "models/lizards/tropidurus/male/walk");
    auto_bind(tropidurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    tropidurus.hide();
    //////////////////////////Eurolophosauros/////////////////
    eurolophosasurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/eurolophosaurus/male/model");
    eurolophosasurus.set_scale(0.04, 0.04, 0.04);
    eurolophosasurus.set_pos(4, 35, -3);
    eurolophosasurus.set_h(45);
    eurolophosasurus.set_p(20);

    /* Animação */
    Simdunas::get_window()->load_model(eurolophosasurus, "models/lizards/eurolophosaurus/male/walk");
    auto_bind(eurolophosasurus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    eurolophosasurus.hide();
    //////////////////Cnemidophorus////////////
    cnemidophorus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/cnemidophorus/male/model");
    cnemidophorus.set_scale(0.04, 0.04, 0.04);
    cnemidophorus.set_pos(4, 35, -3);
    cnemidophorus.set_h(45);
    cnemidophorus.set_p(20);

    //		/* Animação */
    Simdunas::get_window()->load_model(cnemidophorus, "models/lizards/cnemidophorus/male/walk");
    auto_bind(cnemidophorus.node(), anims, PartGroup::HMF_ok_part_extra |
            PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);
    cnemidophorus.hide();

    //      Lagarto Personalizado
    lagartoPersonalizado = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render(), "models/lizards/personalizar/male/model");
    lagartoPersonalizado.set_scale(0.08, 0.08, 0.08);
    lagartoPersonalizado.set_pos(0, 35, -2);
    lagartoPersonalizado.set_h(45);
    lagartoPersonalizado.set_p(20);

    //		/* Animação */
    Simdunas::get_window()->load_model(lagartoPersonalizado, "models/lizards/personalizar/male/walk");
    auto_bind(lagartoPersonalizado.node(), anims, PartGroup::HMF_ok_part_extra |
    PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
    anims.loop_all(false);


    ///imagem do logo
    logo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/calangos.png");
    logo.set_scale(0.1);
    logo.set_pos(0.0, 0, 0.6);


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


    botao_iniciar->setup(tela, pos_click, emcima, pos_click); //colocando a imagem no botao


    button_np = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_iniciar);

    button_np.set_scale(0.25, 0.25, 0.25);
    //button_np.set_color(0.2, 0.5, 0.2, 0.0);
    //button_np.set_pos(-0.3, 0.4, -0.55);

    //setando o frame do botao
    //as coordenadas do frame é em relação ao botao
    botao_iniciar->set_frame(-0.4, 0.4, -0.4, 0.4);


    //////////////////////////cria botão de créditos////////////////////////////

    botao_creditos = new PGButton("creditos");
    nod_botao_creditos = constroi_botao("models/buttons/creditos",botao_creditos);
    nod_botao_creditos.set_scale(0.4, 0.25, 0.3);
    nod_botao_creditos.set_pos(0.3, 0.0, -0.55);



    /////////////////////////////////////////////////////////////////

    //////////////////////criando o botao sair//////////////////////////////////////////////////////////////
    NodePath saindo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/sair");

    saindo.detach_node();


    botao_sair = new PGButton("Sair");

    botao_sair->setup(saindo);

    nod_sair = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_sair);
    nod_sair.set_scale(0.21, 0.21, 0.21);
    nod_sair.set_pos(0.5, 0.4, -0.25);
    botao_sair->set_frame(-0.4, 0.4, -0.4, 0.4);

    ////////////////////////criando o botao configurações////////////////////////////////////////////////////////////////

    botao_configuracoes = new PGButton("configuracoes");
    botao_configuracoes->setup(config); //colocando a imagem no botão

    nod_config_egg = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_configuracoes);
    nod_config_egg.set_scale(0.55, 0.25, 0.25);
    nod_config_egg.set_pos(0.0, 0.4, -0.25);
    botao_configuracoes->set_frame(-0.4, 0.4, -0.4, 0.4);

    ///////////////////////////Criando botão Instruções

    NodePath botao_instrucao_red = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/instrucoes");
    botao_instrucao_red.detach_node();
    botao_instrucao = new PGButton("instrucoes");
    botao_instrucao->setup(botao_instrucao_red);
    nod_botao_instrucao = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_instrucao);
    nod_botao_instrucao.set_scale(0.68, 0.32, 0.32);
    nod_botao_instrucao.set_pos(-0.5, 0.4, -0.25);
    botao_instrucao->set_frame(-0.4, 0.4, -0.4, 0.4);




    //adicionando os eventos dos botões//////////////////////////
    Simdunas::get_evt_handler()->add_hook(botao_iniciar->get_click_event(MouseButton::one()), event_clik, this);
    Simdunas::get_evt_handler()->add_hook(botao_sair->get_click_event(MouseButton::one()), out, this);
    Simdunas::get_evt_handler()->add_hook(botao_configuracoes->get_click_event(MouseButton::one()), configure, this);
    Simdunas::get_evt_handler()->add_hook(botao_instrucao->get_click_event(MouseButton::one()), instrucoes_teclas, this);
    Simdunas::get_evt_handler()->add_hook(botao_creditos->get_click_event(MouseButton::one()), creditos, this);

    hide_tela_principal();
}

Menu::~Menu() {
}



//método para modularizar a construção de botões

NodePath Menu::constroi_botao(string file, PGButton *botao) {

    NodePath node = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), file);
    node.detach_node();

    botao->setup(node);
    botao->set_frame(-0.4, 0.4, -0.4, 0.4);
    NodePath no_retorno = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao);
    return no_retorno;


}



//tela de instruções

void Menu::instrucoes_teclas(const Event*, void* data) {
    Menu * inst = (Menu*) data;

    inst->hide_tela_principal();

    if (inst->background_instrucoes.is_empty()) {

        /////Carregando tela teclas
        background_instrucoes = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render_2d(), "models/gui/teclas.png");
        background_instrucoes.set_scale(0.1, 0.001, 0.17);
        background_instrucoes.set_pos(0.0, 0.0, 0.06);

        informa_segundos("Teclas");
        node_texto.set_pos(-0.3, 0.0, 0.85);
        //node_texto.set_color(0.0, 0.0, 0.0);
        //construindo o botão instruções
        inst->botao_voltar = new PGButton("instrucoes");
        inst->nod_botao_voltar = inst->constroi_botao("models/buttons/voltar", inst->botao_voltar);
        inst->nod_botao_voltar.set_scale(0.17);
        inst->nod_botao_voltar.set_pos(-1.2, 0.0, -0.9);

        ///construindo o botão next
        inst->botao_next = new PGButton("next");
        inst->nod_botao_next = inst->constroi_botao("models/buttons/next", inst->botao_next);
        inst->nod_botao_next.set_scale(0.24);
        inst->nod_botao_next.set_pos(1.2, 0.0, -0.9);

        Simdunas::get_evt_handler()->add_hook(inst->botao_voltar->get_click_event(MouseButton::one()), event_voltar_funcao, inst);
        Simdunas::get_evt_handler()->add_hook(inst->botao_next->get_click_event(MouseButton::one()), next, inst);
        inst->node_texto.show();
        

        /////carregando tela de marcadores

        background_icones = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render_2d(), "models/gui/icones.png");
        background_icones.set_scale(0.1, 0.001, 0.15);
        background_icones.set_pos(0.0, 0.0, 0.0);


        inst->botao_back = new PGButton("back");
        inst->nod_botao_back = inst->constroi_botao("models/buttons/back", inst->botao_back);
        inst->nod_botao_back.set_scale(0.24);
        inst->nod_botao_back.set_pos(-1.2, 0.0, -0.9);
        Simdunas::get_evt_handler()->add_hook(inst->botao_back->get_click_event(MouseButton::one()), back, inst);



        //colocando texto com objetivos da primeira fase do jogo (SÓ ACONTECE NA INICIALIZAÇÃO DO JOGO)

        inst->hide_tela_marcadores(); //escondendo a segunda tela
        inst->hide_tela_instrucoes();//esconde a primeira tela
        
        PGVirtualFrame *Frame = new PGVirtualFrame("Frame de Texto");
        Frame->setup(3.0, 2.0);

        PGFrameStyle style = Frame->get_frame_style(Frame->get_state());
        style.set_type(PGFrameStyle::T_flat);
        Frame->set_frame_style(Frame->get_state(), style);

        frameNode = NodePath(Frame);
        frameNode.reparent_to(Simdunas::get_window()->get_aspect_2d());
        frameNode.set_pos(-1.4, 0.0, -0.85);
        frameNode.set_color(0.0, 0.0, 0.0);


        inst->nod_botao_next.show();
         
/////////////////////////////////criando texto com objetivos///////////////
        tex_obj = new TextNode("objetivo");


        tex_obj->set_text("               Objetivos do Jogo:                               Seu objetivo nesta primeira fase é sobreviver, "
                "desenvolver-se e reproduzir. Seu sucesso será medido pelo número de vezes "
                "que conseguiu se reproduzir. Busque controlar o nível de energia e de hidratação,"
                " e também a temperatura interna. Seu lagarto vive até 36 meses.");

        node_tex_obj = Simdunas::get_window()->get_aspect_2d().attach_new_node(tex_obj);
        node_tex_obj.set_scale(0.17);
        node_tex_obj.set_pos(-1.2, 0, 0.75);
        node_tex_obj.set_color(0.87, 0.72, 0.52);

        tex_obj->set_wordwrap(15.0);
      /////////////////////////////////////////////////////////////////////////

    } else {


        inst->show_tela_instrucoes();
    }
}

void Menu::back(const Event*, void* data) {

    Menu * back = (Menu*) data;

    back->hide_tela_marcadores();
    back->show_tela_instrucoes();

}

void Menu::creditos(const Event*, void* data){

     Menu * cr = (Menu*) data;

     cr->hide_tela_principal();
     cr->showing_creditos=true;

        cr->credit = Simdunas::get_window()->load_model(Simdunas::get_window()->get_render_2d(), "models/apoio-creditos.jpg");
        cr->credit.set_scale(0.12, 0.001, 0.15);
        cr->credit.set_pos(0.0, 0.0, 0.06);

        //////Criando botão voltar
        NodePath botao_voltar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/voltar");
        botao_voltar.detach_node();
        cr->botao_voltar = new PGButton("voltar");
        cr->botao_voltar->setup(botao_voltar);
        cr->nod_botao_voltar = Simdunas::get_window()->get_aspect_2d().attach_new_node(cr->botao_voltar);
        cr->nod_botao_voltar.set_scale(0.21, 0.21, 0.21);
        cr->nod_botao_voltar.set_pos(1.1, 0.0, -0.8);
        cr->botao_voltar->set_frame(-0.4, 0.4, -0.4, 0.4);

        ///adicionando o evento no botão voltar
        Simdunas::get_evt_handler()->add_hook(cr->botao_voltar->get_click_event(MouseButton::one()), event_voltar_funcao, cr);

}

void Menu::next(const Event*, void* data) {

    Menu * next = (Menu*) data;

    if(!next->node_tex_obj.is_empty()){//verifica se as informações do objetivo está sendo mostrada (só acontece na primeira vez que abre a tela de instruções)

        next->node_tex_obj.remove_node();
        frameNode.remove_node();
        next->show_tela_instrucoes();

    }
    else{
    next->hide_tela_instrucoes();
    next->show_tela_marcadores();
    }
   

}

void Menu::lagartos_play(const Event*, void* data) {
    Menu * lagartos = (Menu*) data;
    lagartos->hide_tela_pause();
    GuiManager::get_instance()->hide_frameNode();
    lagartos->play_movie("models/videos/clipe_1_lagartos_mpeg4.avi");
    
}

void Menu::predadores_play(const Event*, void* data) {
    Menu * predadores = (Menu*) data;
    predadores->hide_tela_pause();
    GuiManager::get_instance()->hide_frameNode();
    predadores->play_movie("models/videos/clipe_2_predadores_mpeg4.avi");

}

void Menu::presas_play(const Event*, void* data) {
    Menu * presas = (Menu*) data;
    presas->hide_tela_pause();
    GuiManager::get_instance()->hide_frameNode();
    presas->play_movie("models/videos/clipe_3_presas_mpeg4.avi");

}

void Menu::habitat_play(const Event*, void* data) {
    Menu * habitat = (Menu*) data;
    habitat->hide_tela_pause();
    GuiManager::get_instance()->hide_frameNode();
    habitat->play_movie("models/videos/clipe_4_habitat_mpeg4.avi");
}

void Menu::clima_play(const Event*, void* data) {
    Menu * clima = (Menu*) data;
    clima->hide_tela_pause();
    GuiManager::get_instance()->hide_frameNode();
    clima->play_movie("models/videos/clipe_5_variacoes_climaticas_mpeg4.avi");
}

void Menu::stop_movie(const Event*, void* data) {
    Menu * stop = (Menu*) data;

	    if (stop->playing_movio) {
        stop->ASound->stop();
        stop->node_card.remove_node();
        if (!stop->nod_config_egg.is_empty()) {//só mostra a tela principal quando for a vinheta que estiver tocando
            stop->show_tela_principal();

        }
        else{//se não for a vinheta ele mostra o frame com os ícones do jogo
            GuiManager::get_instance()->show_frameNode();
        }
        stop->playing_movio = false; //o video não está mais tocando
    }

    //Simdunas::get_evt_handler()->remove_hooks("escape");//retirando o evento da fila, se não vai continuar chamando quando pressionar ESC

}

void Menu::play_movie(string file) {



    mov = new MovieTexture("movie");


    mov->read(file);

    cm = new CardMaker("Video");
    cm->set_frame_fullscreen_quad();
    cm->set_uv_range(mov);
    node_card = NodePath(cm->generate());
    node_card.reparent_to(Simdunas::get_window()->get_render_2d());
    node_card.set_texture(mov);
    //node_card.set_tex_scale(TextureStage::get_default(), mov->get_tex_scale());



    AM = AudioManager::create_AudioManager();
    ASound = AM->get_sound(file, true, 1);

    mov->synchronize_to(ASound);


    ASound->play();
    playing_movio = true;

}

AudioManager* Menu::get_audioManager() {
    return AM;

}

AudioSound* Menu::get_sound() {

    return ASound;
}

//método estatico para mostrar o número da Configuração do relógio virtual

void Menu::informa_segundos(string aviso) {

    if (tex == NULL) {

        tex = new TextNode("inicio");
        tex->set_font(FontPool::load_font("models/ExpletiveDeleted.ttf"));
        tex->set_text(aviso);

        node_texto = Simdunas::get_window()->get_aspect_2d().attach_new_node(tex);
        node_texto.set_scale(0.17);
        node_texto.set_pos(-1.2, 0, 0.35);
        node_texto.set_color(0.87, 0.72, 0.52);

    } else {

        tex->set_text(aviso);
        node_texto.set_scale(0.17);
        node_texto.set_pos(-1.2, 0, 0.35);
        node_texto.set_color(0.87, 0.72, 0.52);

    }





}

void Menu::event_clik(const Event*, void *data) {
    Menu * men = (Menu*) data;

    men->botao_iniciar->set_active(false);
    men->remove_tela_menu();
    if (men->minuto_dia_virtual == 0) {
        men->minuto_dia_virtual = TimeControl::virtualTime;
    }

    men->rodar = true;

}

void Menu::configure(const Event*, void *data) {

    Menu * config = (Menu*) data;



    config->hide_tela_principal(); //escondendo tela principal
    config->showing_conf = true;

    //verifica se eh a primeira vez q ta sendo chamado a configuração
    //se não for não será preciso ler tudo dinovo.
    if (config->title_config.is_empty()) {
        config->ratio = 0;


        ///carregando titulo do menu de configurações
        config->title_config = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/config_jogo.png");
        config->title_config.set_scale(0.1);
        config->title_config.set_pos(0.0, 0, 0.8);


        //relogio virtual////////////////////

        config->tempo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/tempo");
        config->tempo.set_scale(1, 0.0, 0.2);
        config->tempo.set_pos(-0.8, 0.0, 0.6);

        ///////////relogio_frse//////////////////////////////////

        config->relogio_frase = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/relogio_frase");
        config->relogio_frase.set_scale(1.8, 0.0, 0.2);
        config->relogio_frase.set_pos(-0.1, 0.0, 0.4);


        /////////////////////Mostrando botão jogar////////////////////////



        config->button_np.show();
        config->button_np.set_pos(0.0, 0.0, -0.8);




        //////Criando botão voltar
        NodePath botao_voltar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/voltar");
        botao_voltar.detach_node();
        config->botao_voltar = new PGButton("voltar");
        config->botao_voltar->setup(botao_voltar);
        config->nod_botao_voltar = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_voltar);
        config->nod_botao_voltar.set_scale(0.21, 0.21, 0.21);
        config->nod_botao_voltar.set_pos(0.5, 0.0, -0.8);
        config->botao_voltar->set_frame(-0.4, 0.4, -0.4, 0.4);

        ///adicionando o evento no botão voltar
        Simdunas::get_evt_handler()->add_hook(config->botao_voltar->get_click_event(MouseButton::one()), event_voltar_funcao, config);




        //////////////////////////////////////////Opção de configuração Tempo Virtual//////////

        config->slid = new PGSliderBar("slid");
        config->slid->set_range(1, 60);
        config->nod_noid = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->slid);

        config->slid->setup_slider(false, 1.0, 0.06, 0.01);


        config->nod_noid.set_scale(0.5, 1.0, 1.0);
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


        Simdunas::get_evt_handler()->add_hook(config->botao_mais->get_click_event(MouseButton::one()), direita, config);

        ////////o default será três? minutos então ja começa como se tivesse dado três clicks no +
        for (int i = 0; i < TimeControl::virtualTime; i++) {
            //                            const Event *ev_direita = new Event(config->botao_mais->get_click_event(MouseButton::one()));
            //                            Simdunas::get_evt_queue()->queue_event(ev_direita);
            //  cout<<"Minuto dia virtual: "<<config->minuto_dia_virtual<<endl;

            //melhor que ficar enfileirando eventos!!!
            direita(NULL, config);
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
        config->escolha_especie.set_scale(0.06, 0.0, 0.06);
        config->escolha_especie.set_pos(-0.68, 0.0, 0.03);

        //carregando o marcador/////////
        config->marcador = Simdunas::get_window()->load_model(config->escolha_especie, "models/buttons/marcador.png");
        config->marcador.set_scale(0.2, 0.0, 0.2);
        config->marcador.set_pos(4.0, 0.0, -4.7);
        ///////Botões para escolha da especie/////////////////

        //botão TROPIDURUS///////////////

        NodePath botao_tropidurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/tropidurus");
        botao_tropidurus.detach_node();
        config->botao_tropidurus = new PGButton("tropidurus");
        config->botao_tropidurus->setup(botao_tropidurus);
        config->nod_bot_tropidurus = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_tropidurus);
        config->nod_bot_tropidurus.set_scale(0.5, 0.1, 0.18);
        config->nod_bot_tropidurus.set_pos(-0.85, 0.0, -0.1);
        config->botao_tropidurus->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(config->botao_tropidurus->get_click_event(MouseButton::one()), tropidurus_funcao, config);

        ///////botão EUROLOPHOSAURUS //////////////////////////
        NodePath botao_eurolophosaurus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/eurolophosaurus");
        botao_eurolophosaurus.detach_node();
        config->botao_eurolophosaurus = new PGButton("eurolophosaurus");
        config->botao_eurolophosaurus->setup(botao_eurolophosaurus);
        config->nod_bot_eurolophosaurus = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_eurolophosaurus);
        config->nod_bot_eurolophosaurus.set_scale(0.6, 0.1, 0.18);
        config->nod_bot_eurolophosaurus.set_pos(-0.8, 0.0, -0.25);
        config->botao_eurolophosaurus->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(config->botao_eurolophosaurus->get_click_event(MouseButton::one()), eurolophosaurus_funcao, config);


        ///////botão CNEMIDOPHORUS //////////////////////////
        NodePath botao_cnemidophorus = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/cnemidophorus");
        botao_cnemidophorus.detach_node();
        config->botao_cnemidophorus = new PGButton("cnemidophorus");
        config->botao_cnemidophorus->setup(botao_cnemidophorus);
        config->nod_bot_cnemidophorus = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_cnemidophorus);
        config->nod_bot_cnemidophorus.set_scale(0.6, 0.1, 0.18);
        config->nod_bot_cnemidophorus.set_pos(-0.8, 0.0, -0.4);
        config->botao_cnemidophorus->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(config->botao_cnemidophorus->get_click_event(MouseButton::one()), cnemidophorus_funcao, config);

            ///////TASSALON COLOCANDO UM BOTÃO PERSONALIZAR //////////////////////////
        NodePath personalizar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/personalizar");
        personalizar.detach_node();
        config->botao_personalizar = new PGButton("Personalizar");
        config->botao_personalizar->setup(personalizar);
        config->nod_bot_personalizar = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_personalizar);
        config->nod_bot_personalizar.set_scale(0.6, 0.1, 0.18);
        config->nod_bot_personalizar.set_pos(-0.8, 0.0, -0.55);
        config->botao_personalizar->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(config->botao_personalizar->get_click_event(MouseButton::one()), personalizar_funcao, config);

         ///////TASSALON COLOCANDO UM BOTÃO COLISAO PARA ATIVAR/DESATIVAR COLISAO  //////////////////////////

         NodePath colisao = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/colisao");
        colisao.detach_node();
        config->botao_colisao = new PGButton("colisao");
        config->botao_colisao->setup(colisao);
        config->nod_bot_colisao = Simdunas::get_window()->get_aspect_2d().attach_new_node(config->botao_colisao);
        config->nod_bot_colisao.set_scale(0.6, 0.1, 0.18);
        config->nod_bot_colisao.set_pos(0.6, 0.0, 0.03);
        config->botao_colisao->set_frame(-0.4, 0.4, -0.4, 0.4);

        Simdunas::get_evt_handler()->add_hook(config->botao_colisao->get_click_event(MouseButton::one()), colisao_funcao, config);

        //carregando botão V (de ativar colisão)
        config->colisaoVerdade = Simdunas::get_window()->load_model(config->escolha_especie, "models/buttons/v.png");
        config->colisaoVerdade.set_scale(0.2, 0.0, 0.2);
        config->colisaoVerdade.set_pos(28.0, 0.0, 0.0);

         //carregando botão x (de desativar colisão)
        config->colisaoFalso = Simdunas::get_window()->load_model(config->escolha_especie, "models/buttons/x.png");
        config->colisaoFalso.set_scale(0.2, 0.0, 0.2);
        config->colisaoFalso.set_pos(28.0, 0.0, 0.0);
        config->colisaoFalso.hide();


        Simdunas::get_evt_handler()->add_hook(config->slid->get_adjust_event(), slide, config);
        //o lagarto default é o eurolophosaurus
        eurolophosaurus_funcao(NULL, config);
        config->node_texto.show();
    } else {

        config->show_tela_configuracao();
    }

}

void Menu::tropidurus_funcao(const Event*, void *data) {
    Menu * t = (Menu*) data;


    t->marcador.set_pos(4.0, 0.0, -2.2); //movendo o marcador


    switch (especie) {

        case Player::cnemidophorus :
                    t->cnemidophorus.hide();
            break;


        case Player::eurolophosaurus :
                    t->eurolophosasurus.hide();
            break;

        default:
            break;
    }
    especie = Player::tropidurus;
    t->tropidurus.show();


}

void Menu::eurolophosaurus_funcao(const Event*, void* data) {
    Menu * e = (Menu*) data;


    e->marcador.set_pos(4.0, 0.0, -4.7); //movendo o marcador

    e->lagarto.hide();

    switch (especie) {

        case Player::tropidurus :
                    e->tropidurus.hide();
            break;


        case Player::cnemidophorus :
                    e->cnemidophorus.hide();
            break;

        default:
            break;
    }

    especie = Player::eurolophosaurus;
    e->eurolophosasurus.show();

}

void Menu::cnemidophorus_funcao(const Event*, void* data) {
    Menu * c = (Menu*) data;


    c->marcador.set_pos(4.0, 0.0, -7.2); //movendo o marcador

    switch (especie) {

        case Player::tropidurus :
                    c->tropidurus.hide();
            break;


        case Player::eurolophosaurus :
                    c->eurolophosasurus.hide();
            break;

        default:
            break;
    }

    especie = Player::cnemidophorus;
    c->cnemidophorus.show();


}

void Menu::personalizar_funcao(const Event*, void* data) {
    Menu * c = (Menu*) data;

    c->marcador.set_pos(4.0, 0.0, -9.5); //movendo o marcador
   //limpa o menu de configuração
    c->hide_tela_configuracao();
    //apresenta o menu de personalização do lagarto
    c->show_tela_personalizar();
}

void Menu::colisao_funcao(const Event*, void* data) {
    Menu * c = (Menu*) data;

    if(colisao){
        c->colisaoVerdade.hide();
        c->colisaoFalso.show();
        colisao = false;
    }else
    {
        c->colisaoVerdade.show();
        c->colisaoFalso.hide();
        colisao = true;
    }
}

void Menu::slide(const Event*, void* data) {
    Menu * slide = (Menu*) data;

    slide->minuto_dia_virtual = (int) slide->slid->get_value();
    ostringstream letra; //convertendo float em string
    letra << slide->minuto_dia_virtual;
    std::string st(letra.str());

    Menu::informa_segundos(st);

    /*cout<<"Chamou Slide"<<endl;
    cout<<"Valor :"<<(int)slide->slid->get_value()<<endl;
    cout<<"Valor Minuto_dia_Virtual Slide:"<<slide->minuto_dia_virtual<<endl;*/


}

void Menu::direita(const Event*, void* data) {

    Menu * d = (Menu*) data;

    if (d->minuto_dia_virtual < 60) {
        d->minuto_dia_virtual++;

        ostringstream letra; //convertendo float em string


        //TimeControl::virtualTime = d->minuto_dia_virtual;

        letra << d->minuto_dia_virtual;
        std::string st(letra.str());

        Menu::informa_segundos(st);

        /*cout<<"Valor :"<<(int)d->slid->get_value()<<endl;
            cout<<"Valor Minuto_dia_Virtual Direita:"<<d->minuto_dia_virtual<<endl;*/

        d->slid->set_value(d->minuto_dia_virtual);
    }

}

void Menu::esquerda(const Event*, void* data) {

    Menu * d = (Menu*) data;

    if (d->minuto_dia_virtual > 1) {
        d->minuto_dia_virtual--;

        ostringstream letra; //convertendo float em string


        //TimeControl::virtualTime = d->minuto_dia_virtual;

        letra << d->minuto_dia_virtual;
        std::string st(letra.str());

        Menu::informa_segundos(st);

        /*cout<<"Valor :"<<(int)d->slid->get_value()<<endl;
            cout<<"Valor Minuto_dia_Virtual Esquerda:"<<d->minuto_dia_virtual<<endl;*/
        d->slid->set_value(d->minuto_dia_virtual);
    }
}

void Menu::event_voltar_funcao(const Event*, void* data) {
    Menu * voltar = (Menu*) data;


    if(voltar->showing_creditos){

        voltar->credit.hide();
        voltar->nod_botao_voltar.hide();
        voltar->showing_creditos=false;//escondendo tela de créditos
    }


    else if (voltar->title_config.is_empty() || !voltar->showing_conf) {//ta voltando da tela de instruções

        voltar->hide_tela_instrucoes();


    } else {


        voltar->hide_tela_configuracao();


    }

    voltar->show_tela_principal();
}

int Menu::get_minuto_dia_virtual() {
    return minuto_dia_virtual;
}

Player::lizardEpecie Menu::get_especie() {

    return especie;
}

bool Menu::get_flag_stop_time_pause() {

    return flag_stop_time_pause;
}

bool Menu::get_playing_movie() {
    return playing_movio;
}

bool Menu::get_rodar() {
    return rodar;
}

void Menu::chama_pause_game(const Event*, void* data) {
    Menu * voltar_jogo = (Menu*) data;
    voltar_jogo->pause_game();

}

void Menu::pause_game() {

    if (flag_stop_time_pause) {
        TimeControl::get_instance()->set_stop_time(false); //se o jogo estiver pausado, ao pressionar esc novamente volta ao normal
        flag_stop_time_pause = false;

        logo.remove_node();
        nod_botao_voltar_jogo.remove_node();
        nod_sair.hide();
        videos.remove_node();
        nod_bot_habitat.remove_node();
        nod_bot_lagartos.remove_node();
        nod_bot_predadores.remove_node();
        nod_bot_presas.remove_node();
        nod_bot_variacao_clima.remove_node();
    } else {
        Session::get_instance()->stop_animations();
        if (!TimeControl::get_instance()->get_stop_time()) {//se o tempo ja estiver parado ele naum pausa o jogo
            logo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/pausa.png");
            logo.set_scale(0.06);
            logo.set_pos(0.0, 0, 0.8);


            /////////colocando nome videos

            videos = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/videos.png");
            videos.set_scale(0.025);
            videos.set_pos(0.0, 0, 0.55);


            //////construindo os botões dos videos

            lagartos = new PGButton("lagartos"); //////////Lagartos
            nod_bot_lagartos = constroi_botao("models/buttons/lagartos", lagartos);
            nod_bot_lagartos.set_scale(0.25);
            nod_bot_lagartos.set_pos(0.0, 0.0, 0.35);

            predadores = new PGButton("Predadores"); //////////Predadores
            nod_bot_predadores = constroi_botao("models/buttons/predadores", predadores);
            nod_bot_predadores.set_scale(0.25);
            nod_bot_predadores.set_pos(0.0, 0.0, 0.15);

            presas = new PGButton("Presas"); //////////Presas
            nod_bot_presas = constroi_botao("models/buttons/presas", presas);
            nod_bot_presas.set_scale(0.25);
            nod_bot_presas.set_pos(0.0, 0.0, -0.05);

            variacao_clima = new PGButton("Clima"); //////////Clima
            nod_bot_variacao_clima = constroi_botao("models/buttons/clima", variacao_clima);
            nod_bot_variacao_clima.set_scale(0.25);
            nod_bot_variacao_clima.set_pos(0.0, 0.0, -0.25);

            habitat = new PGButton("habitat"); //////////Habitat
            nod_bot_habitat = constroi_botao("models/buttons/habitat", habitat);
            nod_bot_habitat.set_scale(0.25);
            nod_bot_habitat.set_pos(0.0, 0.0, -0.45);
            ///////////////////////////////////////fim dos botões de vídeos

            nod_sair.show();
            nod_sair.set_pos(0.4, 0.0, -0.9);

            ///////////////////criando botão voltar ao jogo/////////////////////

            botao_voltar_jogo = new PGButton("voltar ao jogo");
            nod_botao_voltar_jogo = constroi_botao("models/buttons/continuar", botao_voltar_jogo);
            nod_botao_voltar_jogo.set_scale(0.9, 0.1, 0.22);
            nod_botao_voltar_jogo.set_pos(-0.55, 0.0, -0.9);

            ////adicionando os eventos na fila
            Simdunas::get_evt_handler()->add_hook(botao_voltar_jogo->get_click_event(MouseButton::one()), chama_pause_game, this);
            Simdunas::get_evt_handler()->add_hook(lagartos->get_click_event(MouseButton::one()), lagartos_play, this);
            Simdunas::get_evt_handler()->add_hook(predadores->get_click_event(MouseButton::one()), predadores_play, this);
            Simdunas::get_evt_handler()->add_hook(presas->get_click_event(MouseButton::one()), presas_play, this);
            Simdunas::get_evt_handler()->add_hook(habitat->get_click_event(MouseButton::one()), habitat_play, this);
            Simdunas::get_evt_handler()->add_hook(variacao_clima->get_click_event(MouseButton::one()), clima_play, this);


            TimeControl::get_instance()->set_stop_time(true);
            flag_stop_time_pause = true;
        }
    }
}

void Menu::tela_over(Session *nsession) {

    this->session = nsession;


    //Tela de game over
    frame_tela = new PGVirtualFrame("fundo_tela");
    frame_tela->setup(1, 2);

    background_over = Simdunas::get_window()->get_aspect_2d().attach_new_node(frame_tela);
    background_over.set_pos(-0.5, 0, -1);
    background_over.set_transparency(TransparencyAttrib::M_alpha);
    background_over.set_alpha_scale(0.0);

    logo = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/fimdojogo.png");
    logo.set_scale(0.03);
    logo.set_pos(0.0, 0, 0.8);
    // Simdunas::get_window()->get_aspect_2d().attach_new_node(logo);
    //informa_Inicio("FIM DO JOGO!!!!");

    int morte = Session::get_instance()->get_causa_mortis(); //pegando causa da morte

    switch (morte) {//mostrando causa da morte
        case DESNUTRICAO: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/desnutricao.png");
            indica_morte.set_scale(0.065, 0.0, 0.09);
            indica_morte.set_pos(-0.05, 0.0, 0.45);
            break;

        case ALTA_TEMPERATURA: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/temperatura_alta.png");
            indica_morte.set_scale(0.065, 0.0, 0.09);
            indica_morte.set_pos(-0.1, 0.0, 0.45);
            break;

        case BAIXA_TEMPERATURA: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/temperatura_baixa.png");
            indica_morte.set_scale(0.065, 0.0, 0.09);
            indica_morte.set_pos(-0.1, 0.0, 0.45);
            break;

        case MORTE_IDADE: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/morte_idade.png");
            indica_morte.set_scale(0.065, 0.0, 0.09);
            indica_morte.set_pos(-0.1, 0.0, 0.45);
            break;

        case DESIDRATACAO: indica_morte = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/desidratacao.png");
            indica_morte.set_scale(0.065, 0.0, 0.09);
            indica_morte.set_pos(-0.05, 0.0, 0.45);
            break;

        default: break;

    }


    NodePath im_reiniciar = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/reiniciar");
    NodePath im_grafico = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/grafico");
    //NodePath im_sair = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/sair");
    NodePath pos_click = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/buttons/pos_click");

    pos_click.detach_node();
    im_reiniciar.detach_node();
    im_grafico.detach_node();
    //im_sair.detach_node();


    ////////////////////////////botoes

    botao_restart = new PGButton("restart");
    botao_restart->setup(im_reiniciar, pos_click);

    button_restart = Simdunas::get_window()->get_aspect_2d().attach_new_node(botao_restart);
    button_restart.set_scale(0.3);
    button_restart.set_pos(0.0, 0.0, 0.0);
    botao_restart->set_frame(-0.4, 0.4, -0.4, 0.4);
    Simdunas::get_evt_handler()->add_hook(botao_restart->get_click_event(MouseButton::one()), restart, this);
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

    nod_sair.show(); //mostrando o botão (sair)
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
    nod_botao_instrucao.hide();
    nod_botao_creditos.hide();

}

void Menu::hide_tela_instrucoes() {

    background_instrucoes.hide();
    nod_botao_voltar.hide();
    node_texto.hide();
    nod_botao_next.hide();

}

void Menu::hide_tela_marcadores() {

    background_icones.hide();
    nod_botao_back.hide();
}

void Menu::hide_tela_configuracao() {

    showing_conf = false;

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
    nod_bot_personalizar.hide();
    nod_bot_colisao.hide();
    nod_botao_voltar.hide();

    switch (especie) {

        case Player::tropidurus :
                    tropidurus.hide();
            break;
        case Player::eurolophosaurus :
                    eurolophosasurus.hide();
            break;

        case Player::cnemidophorus :
                    cnemidophorus.hide();
            break;

        default:
            break;
    }

}

void Menu::hide_tela_pause() {
    logo.hide();
    nod_botao_voltar_jogo.hide();
    nod_sair.hide();
    videos.hide();
    nod_bot_habitat.hide();
    nod_bot_lagartos.hide();
    nod_bot_predadores.hide();
    nod_bot_presas.hide();
    nod_bot_variacao_clima.hide();


}

////////////remove todos os componentes(botões tútulos e etc.) de menu para que o jogo se inicie

void Menu::remove_tela_menu() {

    node_texto.remove_node();
    button_np.remove_node();
    nod_botao_creditos.remove_node();
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
    nod_bot_personalizar.remove_node();
    nod_bot_colisao.remove_node();
    nod_botao_voltar.remove_node();
    tropidurus.remove_node();
    eurolophosasurus.remove_node();
    cnemidophorus.remove_node();
    lagartoPersonalizado.remove_node();
    nod_botao_instrucao.remove_node();
    ///removendo telas de instruções para não ficarem comendo memória
    background_instrucoes.remove_node();
    background_icones.remove_node();
    nod_botao_back.remove_node();
    nod_botao_next.remove_node();
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

void Menu::show_tela_pause() {
    logo.show();
    nod_botao_voltar_jogo.show();
    nod_sair.show();
    videos.show();
    nod_bot_habitat.show();
    nod_bot_lagartos.show();
    nod_bot_predadores.show();
    nod_bot_presas.show();
    nod_bot_variacao_clima.show();

}

void Menu::show_tela_principal() {
    lagartoPersonalizado.hide();
    button_np.show();
    nod_botao_creditos.show();
    button_np.set_pos(-0.3, 0.4, -0.55); //colocando o botão (Iniciar) novamente em seu lugar na tela principal
    nod_sair.show();
    logo.show();
    nod_config_egg.show();
    lagarto.show();
    nod_botao_instrucao.show();
}

void Menu::show_tela_personalizar() {
        //carregando animação inicial da Tela principal

    //BOTÃO CONFIGURAÇÃO
   // nod_config_egg.show();

   //APRESENTA O LAGARTO DO MENU PRINCIPAL - TEM QUE MUDAR ISSO
    lagartoPersonalizado.show();

    //APRESENTA OS BOTÕES VOLTAR E JOGAR
    button_np.show();
    nod_botao_voltar.show();
}

void Menu::show_tela_instrucoes() {
    background_instrucoes.show();
    nod_botao_voltar.show();
    node_texto.show();
    nod_botao_next.show();

    informa_segundos("Teclas"); //colocando texto no lacal certo para essa tela
    node_texto.set_pos(-0.3, 0.0, 0.88);
    //node_texto.set_color(0.0, 0.0, 0.0);

    nod_botao_voltar.set_scale(0.17); //repocisionando botão voltar na tela de instruções
    nod_botao_voltar.set_pos(-1.2, 0.0, -0.9);

}

void Menu::show_tela_marcadores() {

    background_icones.show();
    nod_botao_back.show();
    node_texto.show();

    informa_segundos("Indicadores"); //colocando texto no lacal certo para essa tela
    node_texto.set_pos(-0.3, 0.0, 0.88);
    node_texto.set_color(0.0, 0.0, 0.0);

}

void Menu::show_tela_configuracao() {

    showing_conf = true;

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
    nod_bot_personalizar.show();
    nod_bot_cnemidophorus.show();
    nod_bot_colisao.show();
    button_np.show();
    button_np.set_pos(0.0, 0.0, -0.8); //colocando o botão (Iniciar) novamente em seu lugar na tela principal
    nod_botao_voltar.show();

    nod_botao_voltar.set_scale(0.21, 0.21, 0.21);
    nod_botao_voltar.set_pos(0.5, 0.0, -0.8);

    ostringstream letra; //convertendo minuto dia virtual em string
    letra << minuto_dia_virtual;
    std::string st(letra.str());
    informa_segundos(st);

    lagartoPersonalizado.hide();
    lagarto.hide(); //escondendo o lagarto da tela principal

    switch (especie) {//mostrando especie q tava selecionada

        case Player::tropidurus :
                    tropidurus.show();
            break;
        case Player::eurolophosaurus :
                    eurolophosasurus.show();
            break;

        case Player::cnemidophorus :
                    cnemidophorus.show();
            break;
                // O QUE É Player::lagartoPersonalizado:

        default:
            break;
    }


}

void Menu::restart(const Event*, void* data) {
    Menu *m = (Menu*) data;
    tecla = "r";
    //m->hide_tela_over();
    //controle=true;
    Session *session = (Session*) data;
    background_over.remove_node();
    button_sair.remove_node();
    button_restart.remove_node();
    button_grafico.remove_node();
    node_texto.remove_node();
    logo.remove_node();
    m->indica_morte.remove_node();
    m->nod_sair.hide();
    cout << "final r" << endl;

    cout << "PASSSOU RESTART" << endl;


    session->receive_answer(tecla);
    //return tecla;

}

void Menu::out(const Event*, void* data) {
    //	Session::get_instance()->end_session();

    exit(0); //saindo direto, fechando o jogo
    //na tela de inicialização ou de game over

}

void Menu::graph(const Event*, void* data) {
    //Menu *m=(Menu*)data;
    tecla = "g";
    // controle=true;
    Session *session = (Session*) data;
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


bool Menu::get_colisao() {
    return colisao;
}

Menu* Menu::get_instance() {

    if (instance == NULL) {

        instance = new Menu(Simdunas::get_window());
        return instance;

    }
    else {
        return instance;
    }

}


