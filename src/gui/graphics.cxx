
#include <stddef.h>
#include <queue>
#include "graphics.h"
#include "simdunas.h"
#include "timeControl.h"
#include "mouseWatcher.h"
#include "lineSegs.h"

#define DEBUG_GUI 0

//Utilizado para tornar a classe PT
TypeHandle Graphics::_type_handle;

//TODO retirar daqui!!!!!!!!!!!!!!!!!!!
//Declaração de variavel. Foram declarados aqui como variaveis globais
//porque quando colocadas no graphics.h dava erro de compilação.
NodePath linha_grafico_np;
LineSegs* linha_grafico;
TextNode* marcacaoX1_titulo;
TextNode* marcacaoX2_titulo;
TextNode* marcacaoX3_titulo;
TextNode* marcacaoX4_titulo;
TextNode* marcacaoX5_titulo;
TextNode* marcacaoY1_titulo;
TextNode* marcacaoY2_titulo;
TextNode* marcacaoY3_titulo;
TextNode* marcacaoY4_titulo;
TextNode* marcacaoY5_titulo;
NodePath marcacaoX1_titulo_np;
NodePath marcacaoX2_titulo_np;
NodePath marcacaoX3_titulo_np;
NodePath marcacaoX4_titulo_np;
NodePath marcacaoX5_titulo_np;
NodePath marcacaoY1_titulo_np;
NodePath marcacaoY2_titulo_np;
NodePath marcacaoY3_titulo_np;
NodePath marcacaoY4_titulo_np;
NodePath marcacaoY5_titulo_np;
char stringMarcacaoY1[8];
char stringMarcacaoY2[8];
char stringMarcacaoY3[8];
char stringMarcacaoY4[8];
char stringMarcacaoY5[8];
float unidade_marcacaoX;
float posicao_marcacaoX1;
float posicao_marcacaoX2;
float posicao_marcacaoX3;
float posicao_marcacaoX4;
float posicao_marcacaoX5;
float unidade_marcacaoY;
float posicao_marcacaoY1;
float posicao_marcacaoY2;
float posicao_marcacaoY3;
float posicao_marcacaoY4;
float posicao_marcacaoY5;
bool tipoTempo;

LineSegs* eixo_hint;
NodePath eixo_hint_np;
LineSegs* eixo_hint2;
NodePath eixo_hint2_np;
TextNode* valor_hint;
NodePath valor_hint_np;
TextNode* valor_hint2;
NodePath valor_hint2_np;

//Destrutor: Remove os graficos da tela.
Graphics::~Graphics() {
    //if(&graphic_np != NULL)
    if (&graphic_np != NULL)
        graphic_np.remove_node();
    if (&eixoX != NULL) {
        delete eixoX;
    }
    if (&eixoX2 != NULL) {
        delete eixoX2;
    }
    if (&eixoY != NULL) {
        delete eixoY;
    }
    if (&eixoY2 != NULL) {
        delete eixoY2;

		    }
}

//Construtor
//NodePath* paiNode: Node onde o grafico vai ser anexado (componente de interface grafica, ex. frame)
//queue<double> vetorXtmp: Fila com os valores do eixo X. Não pode ter mais de 24 horas.
//queue<double> vetorYtmp: Fila com os valores do eixo Y.
//double limiteSuperiorXTmp: Valor maximo do eixo X.
//double limiteInferiorXTmp: Valor minimo do eixo X.
//double limiteSuperiorYTmp: Valor maximo do eixo Y.
//double limiteInferiorYTmp: Valor minimo do eixo Y.
//bool tipoTempoTmp: Indica se é grafico de tempo (tipoTempoTmp = true) ou se é do tipo variavel por variavel (tipoTempoTmp = false).
Graphics::Graphics(NodePath paiNode, History::HList* vetorXtmp, History::HList* vetorYtmp,  double limiteSuperiorXTmp, double limiteInferiorXTmp, double limiteSuperiorYTmp, double limiteInferiorYTmp, bool tipoTempoTmp){

	/* Cria cópia (através do operador =) */
    vetorX = new History::HList(*vetorXtmp);
    vetorY = new History::HList(*vetorYtmp);

    tipoTempo = tipoTempoTmp;

	if(limiteInferiorYTmp == limiteSuperiorYTmp) {
		limiteInferiorYTmp -= 2.0;
		limiteSuperiorYTmp += 2.0;
	}

    limiteSuperiorX = limiteSuperiorXTmp;
    limiteInferiorX = limiteInferiorXTmp;
    limiteSuperiorY = limiteSuperiorYTmp;
    limiteInferiorY = limiteInferiorYTmp;

    //Cria o frame e seta a propriedade do frame onde o grafico será construido.
    graphic_frame = new PGVirtualFrame("Frame do grafico");
    graphic_frame->setup(1.1, 1.0);
    PGFrameStyle style = graphic_frame->get_frame_style(graphic_frame->get_state());
    style.set_type(PGFrameStyle::T_flat);
    style.clear_texture();
    graphic_frame->set_frame_style(graphic_frame->get_state(), style);
    graphic_np = paiNode.attach_new_node(graphic_frame);
    graphic_np.set_color(1.0, 1.0, 1.0);

    //Inicia as linhas utilizadas nos desenhos dos eixos.
    eixoX = new LineSegs("eixoX");
    eixoX2 = new LineSegs("eixoX2");
    eixoY = new LineSegs("eixoY");
    eixoY2 = new LineSegs("eixoY2");

    //DESENHANDO OS EIXOS-------------------------------------------------------
    //Eixo X.
    this->desenha_eixoX();

    //Eixo Y.
    this->desenha_eixoY();

    //COLOCANDO MARCAÇÕES NO EIXO X---------------------------------------------
    this->desenha_marcacao_eixoX();

    //COLOCANDO MARCAÇÕES NO EIXO Y---------------------------------------------
    this->desenha_marcacao_eixoY();


    //COLOCANDO TITULO E TEXTOS-------------------------------------------------

    //Criando o label do titulo.
    graphic_titulo = new TextNode("Titulo");
    graphic_titulo_np = graphic_np.attach_new_node(graphic_titulo);
    graphic_titulo_np.set_pos(0.15, 0.0, 0.94);
    graphic_titulo_np.set_scale(0.06);
    graphic_titulo_np.set_color(0.0, 0.0, 0.0, 1, 0);

    //Criando o label do titulo do eixo X.
    graphic_titulo_eixoX = new TextNode("Eixo_X");
    graphic_titulo_eixoX_np = graphic_np.attach_new_node(graphic_titulo_eixoX);
    graphic_titulo_eixoX_np.set_pos(0.80, 0.0, 0.14);
    graphic_titulo_eixoX_np.set_scale(0.04);
    graphic_titulo_eixoX_np.set_color(0.0, 0.0, 0.0, 1, 0);

    //Criando o label do titulo do eixo Y.
    graphic_titulo_eixoY = new TextNode("Eixo_Y");
    graphic_titulo_eixoY_np = graphic_np.attach_new_node(graphic_titulo_eixoY);
    graphic_titulo_eixoY_np.set_pos(0.04, 0.0, 0.84);
    graphic_titulo_eixoY_np.set_scale(0.04);
    graphic_titulo_eixoY_np.set_color(0.0, 0.0, 0.0, 1, 0);

}

//create_Graphic é o método que desenha o grafico na tela. Caso um objeto graphics seja iniciado e esse método
//não seja chamado, o grafico não irá ser desenhado, aparecerá apenas o frame branco com os eixos azuis.
//double tamanhoVetorXtmp: Quantidade de amostras do eixo x.
//double tamanhoVetorYtmp: Quantidade de amostras do eixo Y.
void Graphics::create_Graphic(double tamanhoVetorXtmp, double tamanhoVetorYtmp) {

    //Inicia a linha do grafico. Esse componente é usado tanto para desenhar um linha continua, no caso do grafico
    //de tempo, como pontos, no caso do grafico de variavel por variavel.
    linha_grafico = new LineSegs("linha-grafico");
    linha_grafico->set_color(0.0, 0.0, 0.0);
    double tamanhoVetorX = tamanhoVetorXtmp;
    double tamanhoVetorY = tamanhoVetorYtmp;
    double escalaX;
    double escalaY;
    double posicaoX;
    double posicaoY;

    //Faz o calculo da escala em x de acordo com o tipo de grafico.
    if(tipoTempo){
		//this->add_hint_line_draw_hook(); // hook para atualizar a linha do hint dentro do gráfico a cada frame
        //escalaX = 0.63 / (tamanhoVetorX - 1);
    	// TODO criar constante na classe que constroi vetores de amostragem
    	escalaX = 0.63 / (144 - 1);
        //posicaoX = 0;

    	// Cada hora possui 6 amostras, então o máximo de amostras por dia é de 144.
    	// É necessário multiplicar por 6 para fazer a equivalência de hora com o vetor de amostras.
    	// Por ex.: A amostra da oitava hora do dia será a 48a do vetor (8 * 6)
    	// Sendo assim, a posição inicial de X será o 48o espaço de 144 espaços possíveis no eixo X
    	posicaoX = vetorX->front() * 6;

    } else {
        if (tamanhoVetorX > 0) {
            escalaX = (0.63) / (limiteSuperiorX - limiteInferiorX);//((100 * 0.0063) / limiteSuperiorX);
            posicaoX = vetorX->front();
            vetorX->pop_front();
            if (posicaoX > limiteSuperiorX){
                posicaoX = limiteSuperiorX;
            }
            if (posicaoX < limiteInferiorX){
                posicaoX = limiteInferiorX;
            }
        }
    }
    //Calcula a escala em y.
    escalaY = (0.63) / (limiteSuperiorY - limiteInferiorY);

    //Se o vetor Y não for vazio ele coloca a linha do grafico na posição inicial.
	if (tamanhoVetorY > 0) {
        posicaoY = vetorY->front();
        vetorY->pop_front();
        linha_grafico->reset();
        if (tipoTempo) {
        	linha_grafico->move_to((posicaoX * escalaX), 0.0, ((posicaoY - limiteInferiorY) * escalaY));
        } else {
            linha_grafico->move_to(((posicaoX - limiteInferiorX) * escalaX), 0.0, ((posicaoY - limiteInferiorY) * escalaY));
        }
    }

	//Verifica qual o maior valor do vetor X.
//	History::HList listaTemp (*this->vetorX);
//    double maior = listaTemp.front();
//    int tamanhoFor = listaTemp.size();
//
//    for(int i = 1; i < tamanhoFor; i++){
//    	//cout << "\n ListaTemp na posição " << i << "é igual a: " << listaTemp.front();
//        if(listaTemp.front() > maior)
//            maior = listaTemp.front();
//        listaTemp.pop_front();
//    }

	//Gera os valores das marcações dos eixos do grafico.
    PT(TimeControl) time_control = TimeControl::get_instance();
    if (tipoTempo) {
        //Colocando os numeros das marcacoes do eixo X.
//        sprintf(stringMarcacaoX1, "%.2f", (maior / 5));
//        marcacaoX1_titulo->set_text(stringMarcacaoX1);
//        sprintf(stringMarcacaoX2, "%.2f", (2 * (maior / 5)));
//        marcacaoX2_titulo->set_text(stringMarcacaoX2);
//        sprintf(stringMarcacaoX3, "%.2f", (3 * (maior / 5)));
//        marcacaoX3_titulo->set_text(stringMarcacaoX3);
//        sprintf(stringMarcacaoX4, "%.2f", (4 * (maior / 5)));
//        marcacaoX4_titulo->set_text(stringMarcacaoX4);
//        sprintf(stringMarcacaoX5, "%.2f", maior);
//        marcacaoX5_titulo->set_text(stringMarcacaoX5);
        marcacaoX1_titulo->set_text("6h");
        marcacaoX2_titulo->set_text("12h");
        marcacaoX3_titulo->set_text("18h");
        marcacaoX4_titulo->set_text("24h");
//        sprintf(stringMarcacaoX5, "%.2f", 24.00);
//        marcacaoX5_titulo->set_text(stringMarcacaoX5);
    } else {
        //Colocando os numeros das marcacoes do eixo X.
        sprintf(stringMarcacaoX1, "%.2f", (limiteInferiorX));
        marcacaoX1_titulo->set_text(stringMarcacaoX1);
        sprintf(stringMarcacaoX2, "%.2f", (((limiteSuperiorX - limiteInferiorX) / 4)) + limiteInferiorX);
        marcacaoX2_titulo->set_text(stringMarcacaoX2);
        sprintf(stringMarcacaoX3, "%.2f", ((2 * ((limiteSuperiorX - limiteInferiorX) / 4))) + limiteInferiorX);
        marcacaoX3_titulo->set_text(stringMarcacaoX3);
        sprintf(stringMarcacaoX4, "%.2f", ((3 * ((limiteSuperiorX - limiteInferiorX) / 4))) + limiteInferiorX);
        marcacaoX4_titulo->set_text(stringMarcacaoX4);
        //sprintf(stringMarcacaoX5, "%.2f", (limiteSuperiorX));
        //marcacaoX5_titulo->set_text(stringMarcacaoX5);
    }

    //Colocando os numeros das marcacoes do eixo Y.
    sprintf(stringMarcacaoY1, "%.2f", (limiteInferiorY));
    marcacaoY1_titulo->set_text(stringMarcacaoY1);
    sprintf(stringMarcacaoY2, "%.2f", (((limiteSuperiorY - limiteInferiorY) / 4)) + limiteInferiorY);
    marcacaoY2_titulo->set_text(stringMarcacaoY2);
    sprintf(stringMarcacaoY3, "%.2f", ((2 * ((limiteSuperiorY - limiteInferiorY) / 4))) + limiteInferiorY);
    marcacaoY3_titulo->set_text(stringMarcacaoY3);
    sprintf(stringMarcacaoY4, "%.2f", ((3 * ((limiteSuperiorY - limiteInferiorY) / 4))) + limiteInferiorY);
    marcacaoY4_titulo->set_text(stringMarcacaoY4);
    //sprintf(stringMarcacaoY5, "%.2f", (limiteSuperiorY));
    //marcacaoY5_titulo->set_text(stringMarcacaoY5);

    /*
     * For que constroi o grafico.
     * Comeca de 1 porque a primeira amostra foi postada anteriormente.
     */
    double front_x = 0;
	//cout << "\n ---------- Front Y: " << vetorY->front() << "Back Y: " << vetorY->back();

    // Com a iteração através de inserção e remoção dos itens da fila, armazena-se o primeiro item antes de fazer o pop_front().
    // Este item é readicionado no final da fila (push_back()) para que o vetor não sofra alterações ao acabar a iteração.
    if ((tamanhoVetorY > 0) & (tamanhoVetorX > 0)) {
        for (int i = 1; i < tamanhoVetorX; i++) {
        	front_x = vetorX->front(); // para ser readicionado a vetorX
        	posicaoX = front_x * 6;
        	vetorX->pop_front();
        	posicaoY = vetorY->front();
            vetorY->pop_front();
            if (tipoTempo) {
                //posicaoX = posicaoX + escalaX;
                linha_grafico->draw_to(posicaoX * escalaX, 0.0, ((posicaoY - limiteInferiorY) * escalaY));
            } else {
                posicaoX = vetorX->front();
                vetorX->pop_front();
                if (posicaoX > limiteSuperiorX) {
                    posicaoX = limiteSuperiorX;
                }
                if (posicaoX < limiteInferiorX) {
                    posicaoX = limiteInferiorX;
                }
                linha_grafico->move_to((((posicaoX - limiteInferiorX) * escalaX) + 0.005), 0.0, ((posicaoY - limiteInferiorY) * escalaY));
                linha_grafico->draw_to((((posicaoX - limiteInferiorX) * escalaX) - 0.01), 0.0, ((posicaoY - limiteInferiorY) * escalaY));
                linha_grafico->move_to(((posicaoX - limiteInferiorX) * escalaX), 0.0, ((posicaoY - limiteInferiorY) * escalaY) + 0.008);
                linha_grafico->draw_to(((posicaoX - limiteInferiorX) * escalaX), 0.0, (((posicaoY - limiteInferiorY) * escalaY) - 0.016));
            }
            vetorX->push_back(front_x); // readiciona ao final da fila a última referência removida
            vetorY->push_back(posicaoY); // readiciona ao final da fila a última referência removida
        }
        front_x = vetorX->front(); // última referência de hora não é removida no for
        vetorX->pop_front(); // remove última referência de hora do início
        vetorX->push_back(front_x); // e coloca no final de vetorX

//        posicaoY = vetorY->front(); // última referência de Y não é removida no for
//        vetorY->pop_front(); // remove última referência de hora do início
//        vetorY->push_back(posicaoY); // e coloca no final de vetorY
    }

    //cout << "\n---------- Front Y: " << vetorY->front() << "Back Y: " << vetorY->back();

	//Faz o attach do grafico na tela.
    linha_grafico_np = graphic_np.attach_new_node(linha_grafico->create(true));
    linha_grafico_np.set_pos(0.15, 0.0, 0.15);
    linha_grafico_np.set_color(0.0, 0.0, 0.0);

}

void Graphics::set_Position_Graphic(float x, float y) {
    this->graphic_np.set_pos(x, 0.0, y);
}

void Graphics::set_scale(float x) {
    this->graphic_np.set_scale(x);
}

void Graphics::hide(){
    this->graphic_np.stash();
    //this->remove_hint_line_draw_hook();
}

void Graphics::desenha_eixoX() {
    eixoX->set_color(0.0, 0.0, 1);
    eixoX->draw_to(0.0, 0.0, 0.0);
    eixoX->draw_to(0.68, 0.0, 0.0);
    eixoX_np = graphic_np.attach_new_node(eixoX->create());
    eixoX_np.set_pos(0.10, 0.0, 0.15);

    eixoX2->set_color(0.0, 0.0, 1);
    eixoX2->draw_to(0.0, 0.0, 0.0);
    eixoX2->draw_to(0.68, 0.0, 0.0);
    eixoX2_np = graphic_np.attach_new_node(eixoX2->create());
    eixoX2_np.set_pos(0.10, 0.0, 0.149);

}

void Graphics::desenha_eixoY() {
    eixoY->set_color(0.0, 0.0, 1.0);
    eixoY->draw_to(0.0, 0.0, 0.0);
    eixoY->draw_to(0.0, 0.0, 0.68);
    eixoY_np = graphic_np.attach_new_node(eixoY->create());
    eixoY_np.set_pos(0.15, 0.0, 0.10);

    eixoY2->set_color(0.0, 0.0, 1.0);
    eixoY2->draw_to(0.0, 0.0, 0.0);
    eixoY2->draw_to(0.0, 0.0, 0.68);
    eixoY2_np = graphic_np.attach_new_node(eixoY2->create());
    eixoY2_np.set_pos(0.149, 0.0, 0.10);

}

//void Graphics::desenha_linha_hint(float pos_x) {
//	eixo_hint->set_color(1.0, 0.0, 0.0);
//	eixo_hint->draw_to(0.0, 0.0, 0.0);
//	eixo_hint->draw_to(0.0, 0.0, 0.68);
//	eixo_hint_np = graphic_np.attach_new_node(eixo_hint->create());
//	//eixo_hint_np.set_pos(pos_x, 0.0, 0.10);
//
//	eixo_hint2->set_color(1.0, 0.0, 0.0);
//	eixo_hint2->draw_to(0.0, 0.0, 0.0);
//	eixo_hint2->draw_to(0.0, 0.0, 0.68);
//	eixo_hint2_np = graphic_np.attach_new_node(eixo_hint2->create());
//	//eixo_hint2_np.set_pos((pos_x - 0.001), 0.0, 0.10);
//
//}

void Graphics::desenha_marcacao_eixoX(){

    //if (tipoTempo) {
//        posicao_marcacaoX1 = 0.276;
//        posicao_marcacaoX2 = 0.402;
//        posicao_marcacaoX3 = 0.528;
//        posicao_marcacaoX4 = 0.654;
//        posicao_marcacaoX5 = 0.780;
        posicao_marcacaoX1 = 0.15 + (0.63 / 4);
        posicao_marcacaoX2 = 0.15 + (2 * 0.63 / 4);
        posicao_marcacaoX3 = 0.15 + (3 * 0.63 / 4);
        posicao_marcacaoX4 = 0.15 + (4 * 0.63 / 4);
   // } else {
        //unidade_marcacaoX = 0.0063; // largura de espaçamento entre os marcadores conforme a coordenada X da tela
        //posicao_marcacaoX5 = (100 * unidade_marcacaoX) + 0.15;
        //posicao_marcacaoX1 = (0 * unidade_marcacaoX) + 0.15;
        //posicao_marcacaoX2 = ((posicao_marcacaoX5 - posicao_marcacaoX1) / 4) + posicao_marcacaoX1;
        //posicao_marcacaoX3 = (2 * (posicao_marcacaoX5 - posicao_marcacaoX1) / 4) + posicao_marcacaoX1;
        //posicao_marcacaoX4 = (3 * (posicao_marcacaoX5 - posicao_marcacaoX1) / 4) + posicao_marcacaoX1;
    //}

    LineSegs* marcacaoX1 = new LineSegs("mx1");
    marcacaoX1->set_color(0.0, 0.0, 1.0);
    marcacaoX1->draw_to(0.0, 0.0, 0.0);
    marcacaoX1->draw_to(0.0, 0.0, 0.035);
    NodePath marcacaoX1_np = graphic_np.attach_new_node(marcacaoX1->create());
    marcacaoX1_np.set_pos(posicao_marcacaoX1, 0.0, 0.13);
    //legenda da marcação 1
    marcacaoX1_titulo = new TextNode("legendamarcacaoX1");
	marcacaoX1_titulo->set_text("");
	marcacaoX1_titulo_np = graphic_np.attach_new_node(marcacaoX1_titulo);
	marcacaoX1_titulo_np.set_pos(posicao_marcacaoX1 - 0.03, 0.0, 0.07);
	marcacaoX1_titulo_np.set_scale(0.04);
  	marcacaoX1_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);

    LineSegs* marcacaoX2 = new LineSegs("mx2");
    marcacaoX2->set_color(0.0, 0.0, 1.0);
    marcacaoX2->draw_to(0.0, 0.0, 0.0);
    marcacaoX2->draw_to(0.0, 0.0, 0.035);
    NodePath marcacaoX2_np = graphic_np.attach_new_node(marcacaoX2->create());
    marcacaoX2_np.set_pos(posicao_marcacaoX2, 0.0, 0.13);
    //legenda da marcação 2
    marcacaoX2_titulo = new TextNode("legendamarcacaoX2");
	marcacaoX2_titulo->set_text("");
	marcacaoX2_titulo_np = graphic_np.attach_new_node(marcacaoX2_titulo);
	marcacaoX2_titulo_np.set_pos(posicao_marcacaoX2 - 0.03, 0.0, 0.07);
	marcacaoX2_titulo_np.set_scale(0.04);
  	marcacaoX2_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);

    LineSegs* marcacaoX3 = new LineSegs("mx3");
    marcacaoX3->set_color(0.0, 0.0, 1.0);
    marcacaoX3->draw_to(0.0, 0.0, 0.0);
    marcacaoX3->draw_to(0.0, 0.0, 0.035);
    NodePath marcacaoX3_np = graphic_np.attach_new_node(marcacaoX3->create());
    marcacaoX3_np.set_pos(posicao_marcacaoX3, 0.0, 0.13);
    //legenda da marcação 3
    marcacaoX3_titulo = new TextNode("legendamarcacaoX3");
	marcacaoX3_titulo->set_text("");
	marcacaoX3_titulo_np = graphic_np.attach_new_node(marcacaoX3_titulo);
	marcacaoX3_titulo_np.set_pos(posicao_marcacaoX3 - 0.03, 0.0, 0.07);
	marcacaoX3_titulo_np.set_scale(0.04);
  	marcacaoX3_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);

    LineSegs* marcacaoX4 = new LineSegs("mx4");
    marcacaoX4->set_color(0.0, 0.0, 1.0);
    marcacaoX4->draw_to(0.0, 0.0, 0.0);
    marcacaoX4->draw_to(0.0, 0.0, 0.035);
    NodePath marcacaoX4_np = graphic_np.attach_new_node(marcacaoX4->create());
    marcacaoX4_np.set_pos(posicao_marcacaoX4, 0.0, 0.13);
    //legenda da marcação 4
    marcacaoX4_titulo = new TextNode("legendamarcacaoX4");
	marcacaoX4_titulo->set_text("");
	marcacaoX4_titulo_np = graphic_np.attach_new_node(marcacaoX4_titulo);
	marcacaoX4_titulo_np.set_pos(posicao_marcacaoX4 - 0.03, 0.0, 0.07);
	marcacaoX4_titulo_np.set_scale(0.04);
  	marcacaoX4_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);

//    LineSegs* marcacaoX5 = new LineSegs("mx5");
//    marcacaoX5->set_color(0.0, 0.0, 1.0);
//    marcacaoX5->draw_to(0.0, 0.0, 0.0);
//    marcacaoX5->draw_to(0.0, 0.0, 0.035);
//    NodePath marcacaoX5_np = graphic_np.attach_new_node(marcacaoX5->create());
//    marcacaoX5_np.set_pos(posicao_marcacaoX5, 0.0, 0.13);
//    //legenda da marcação 5
//    marcacaoX5_titulo = new TextNode("legendamarcacaoX5");
//	marcacaoX5_titulo->set_text("");
//	marcacaoX5_titulo_np = graphic_np.attach_new_node(marcacaoX5_titulo);
//	marcacaoX5_titulo_np.set_pos(posicao_marcacaoX5 - 0.03, 0.0, 0.07);
//	marcacaoX5_titulo_np.set_scale(0.04);
//  	marcacaoX5_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);
}

void Graphics::desenha_marcacao_eixoY() {

    unidade_marcacaoY = 0.0063;
    posicao_marcacaoY5 = (100 * unidade_marcacaoY) + 0.15;
    posicao_marcacaoY1 = (0 * unidade_marcacaoY) + 0.15;
    posicao_marcacaoY2 = ((posicao_marcacaoY5 - posicao_marcacaoY1) / 4) + posicao_marcacaoY1;
    posicao_marcacaoY3 = (2 * (posicao_marcacaoY5 - posicao_marcacaoY1) / 4) + posicao_marcacaoY1;
    posicao_marcacaoY4 = (3 * (posicao_marcacaoY5 - posicao_marcacaoY1) / 4) + posicao_marcacaoY1;

    LineSegs* marcacaoY1 = new LineSegs("my1");
    marcacaoY1->set_color(0.0, 0.0, 1.0);
    marcacaoY1->draw_to(0.0, 0.0, 0.0);
    marcacaoY1->draw_to(0.035, 0.0, 0.0);
    NodePath marcacaoY1_np = graphic_np.attach_new_node(marcacaoY1->create());
    marcacaoY1_np.set_pos(0.13, 0.0, posicao_marcacaoY1);
    //legenda da marcação 1
    marcacaoY1_titulo = new TextNode("legendamarcacaoY1");
    marcacaoY1_titulo->set_text("");
    marcacaoY1_titulo_np = graphic_np.attach_new_node(marcacaoY1_titulo);
    marcacaoY1_titulo_np.set_pos(0.015, 0.0, posicao_marcacaoY1 - 0.01);
    marcacaoY1_titulo_np.set_scale(0.04);
    marcacaoY1_titulo_np.set_color(0.0, 0.0, 0.0, 1, 0);

    LineSegs* marcacaoY2 = new LineSegs("my2");
    marcacaoY2->set_color(0.0, 0.0, 1.0);
    marcacaoY2->draw_to(0.0, 0.0, 0.0);
    marcacaoY2->draw_to(0.035, 0.0, 0.0);
    NodePath marcacaoY2_np = graphic_np.attach_new_node(marcacaoY2->create());
    marcacaoY2_np.set_pos(0.13, 0.0, posicao_marcacaoY2);
    //legenda da marcação 2
    marcacaoY2_titulo = new TextNode("legendamarcacaoY2");
    marcacaoY2_titulo->set_text("");
    marcacaoY2_titulo_np = graphic_np.attach_new_node(marcacaoY2_titulo);
    marcacaoY2_titulo_np.set_pos(0.015, 0.0, posicao_marcacaoY2 - 0.01);
    marcacaoY2_titulo_np.set_scale(0.04);
    marcacaoY2_titulo_np.set_color(0.0, 0.0, 0.0, 1, 0);

    LineSegs* marcacaoY3 = new LineSegs("my3");
    marcacaoY3->set_color(0.0, 0.0, 1.0);
    marcacaoY3->draw_to(0.0, 0.0, 0.0);
    marcacaoY3->draw_to(0.035, 0.0, 0.0);
    NodePath marcacaoY3_np = graphic_np.attach_new_node(marcacaoY3->create());
    marcacaoY3_np.set_pos(0.13, 0.0, posicao_marcacaoY3);
    //legenda da marcação 3
    marcacaoY3_titulo = new TextNode("legendamarcacaoY3");
    marcacaoY3_titulo->set_text("");
    marcacaoY3_titulo_np = graphic_np.attach_new_node(marcacaoY3_titulo);
    marcacaoY3_titulo_np.set_pos(0.015, 0.0, posicao_marcacaoY3 - 0.01);
    marcacaoY3_titulo_np.set_scale(0.04);
    marcacaoY3_titulo_np.set_color(0.0, 0.0, 0.0, 1, 0);

    LineSegs* marcacaoY4 = new LineSegs("my4");
    marcacaoY4->set_color(0.0, 0.0, 1.0);
    marcacaoY4->draw_to(0.0, 0.0, 0.0);
    marcacaoY4->draw_to(0.035, 0.0, 0.0);
    NodePath marcacaoY4_np = graphic_np.attach_new_node(marcacaoY4->create());
    marcacaoY4_np.set_pos(0.13, 0.0, posicao_marcacaoY4);
    //legenda da marcação 4
    marcacaoY4_titulo = new TextNode("legendamarcacaoY4");
    marcacaoY4_titulo->set_text("");
    marcacaoY4_titulo_np = graphic_np.attach_new_node(marcacaoY4_titulo);
    marcacaoY4_titulo_np.set_pos(0.015, 0.0, posicao_marcacaoY4 - 0.01);
    marcacaoY4_titulo_np.set_scale(0.04);
    marcacaoY4_titulo_np.set_color(0.0, 0.0, 0.0, 1, 0);

    LineSegs* marcacaoY5 = new LineSegs("my5");
    marcacaoY5->set_color(0.0, 0.0, 1.0);
    marcacaoY5->draw_to(0.0, 0.0, 0.0);
    marcacaoY5->draw_to(0.035, 0.0, 0.0);
    NodePath marcacaoY5_np = graphic_np.attach_new_node(marcacaoY5->create());
    marcacaoY5_np.set_pos(0.13, 0.0, posicao_marcacaoY5);
    marcacaoY5_np.set_color(0.0, 0.0, 1.0);
    //legenda da marcação 5
    marcacaoY5_titulo = new TextNode("legendamarcacaoY5");
    marcacaoY5_titulo->set_text("");
    marcacaoY5_titulo_np = graphic_np.attach_new_node(marcacaoY5_titulo);
    marcacaoY5_titulo_np.set_pos(0.015, 0.0, posicao_marcacaoY5 - 0.01);
    marcacaoY5_titulo_np.set_scale(0.04);
    marcacaoY5_titulo_np.set_color(0.0, 0.0, 0.0, 1, 0);
}

void Graphics::set_Titulo_Grafico(const string& tituloString){
    graphic_titulo->set_text(tituloString);
}

void Graphics::set_Titulo_EixoX(const string& tituloEixoXString){
    graphic_titulo_eixoX->set_text(tituloEixoXString);
}

void Graphics::set_Titulo_EixoY(const string& tituloEixoYString){
    graphic_titulo_eixoY->set_text(tituloEixoYString);
}

//// Evento que atualiza a posição da linha do hint dentro do gráfico a cada frame
//void Graphics::add_hint_line_draw_hook() {
//	event_handler->add_hook(TimeControl::EV_pass_frame_gui_options, draw_hint_line, this);
//}
//
//void Graphics::remove_hint_line_draw_hook() {
//	event_handler->remove_hook(TimeControl::EV_pass_frame_gui_options, draw_hint_line, this);
//}

//void Graphics::draw_hint_line() {
//	float mouse_x = 0; // coordenada X do mouse na tela
//	float mouse_y = 0; // coordenada Y do mouse na tela
//	float hour = 0; // valor de X (hora) no gráfico
//	float item_value = 0; // valor de Y no gráfico
//
//	// Todas as coordenadas utilizadas nos cálculos são referentes à toda a tela de jogo
//	// Os valores de coordenadas são os mesmos para qualquer resolução da tela de jogo
//	MouseWatcher *mwatcher = DCAST(MouseWatcher, window->get_mouse().node());
//	if(mwatcher->has_mouse()) {
//		mouse_x = mwatcher->get_mouse_x();
//		mouse_y = mwatcher->get_mouse_y();
//		//cout << "\n------- X = " << mouse_x << " ; Y = " << mouse_y;
//		// Hora = (24 horas * (posição de tela atual do X do cursor - posição de tela de X na linha de início do eixo X)) /
//		// posição de tela de X no fim do eixo X - posição de tela de X na linha de início do eixo X;
//		hour = (24 * (mouse_x - 0.03)) / 0.54;
//
//		if (&eixo_hint2_np != NULL) {
//			eixo_hint2_np.remove_node();
//			valor_hint2_np.remove_node();
//		}
//		if (&eixo_hint_np != NULL) {
//			eixo_hint_np.remove_node();
//			valor_hint_np.remove_node();
//		}
//
//		// a hora pode ser igual para dias diferentes;
//		// criar sublista de vetorX somente com amostras do dia corrente
//		// usar iterator
//
//		// Itera os vetores X e Y para pegar o valor de Y equivalente à hora obtida no vetor X
//		// Pega a amostra do vetor Y a partir da posição do mouse e da hora equivalente no vetor X
//		std::list<float>::const_iterator iterator, iterator2;
//		float previous_x = 0;
//		float previous_y = 0;
//		for (iterator = vetorX->begin(), iterator2 = vetorY->begin();
//			iterator != vetorX->end(), iterator2 != vetorY->end(); ++iterator, ++iterator2) {
//			// se o valor de hora do iterator for maior do que o valor de hora equivalente à posição atual do mouse
//			// e menor ou igual que o valor de hora guardado anteriormente, pega a amostra anterior e para a iteração
//			if (*iterator > hour && previous_x <= hour) {
//				item_value = previous_y;
//				break;
//			}
//			previous_x = *iterator; // guarda o valor atual de hora que servirá de condição para a próxima iteração
//			previous_y = *iterator2;
//		}
//
////		if (mouse_x >= 0.03 && mouse_x <= 0.57 && hour >= vetorX->front() && hour <= vetorX->back()) {
////			if (mouse_y >= 0.12 && mouse_y <= 0.66) {
////				eixo_hint = new LineSegs("eixo-hint");
////				eixo_hint->set_color(1.0, 0.0, 0.0);
////				eixo_hint->draw_to(0.0, 0.0, 0.0);
////				eixo_hint->draw_to(0.0, 0.0, 0.54);
////				eixo_hint_np = graphic_np.get_parent().attach_new_node(eixo_hint->create(true));
////				eixo_hint_np.set_pos(window->get_render_2d(), mouse_x, 0.0, 0.12);
////
////				stringstream hint_msg;
////				hint_msg << item_value;
////				valor_hint = new TextNode("valor-hint");
////				valor_hint->set_text(hint_msg.str());
////				valor_hint_np = graphic_np.get_parent().attach_new_node(valor_hint);
////				valor_hint_np.set_scale(0.05);
////				valor_hint_np.set_color(0.0, 0.0, 0.0, 1, 0);
////				//valor_hint_np.set_pos(0.7, 0.0, 1.7);
////				valor_hint_np.set_pos(window->get_render_2d(), 0.3, 0.0, 0.7);
////			} else if (mouse_y >= -0.77 && mouse_y <= -0.23) {
////				eixo_hint2 = new LineSegs("eixo-hint2");
////				eixo_hint2->set_color(0.0, 1.0, 0.0);
////				eixo_hint2->draw_to(0.0, 0.0, 0.0);
////				eixo_hint2->draw_to(0.0, 0.0, 0.54);
////				eixo_hint2_np = graphic_np.get_parent().attach_new_node(eixo_hint2->create(true));
////				eixo_hint2_np.set_pos(window->get_render_2d(), mouse_x, 0.0, -0.77);
////
////				stringstream hint_msg2;
////				hint_msg2 << item_value;
////				valor_hint2 = new TextNode("valor-hint2");
////				valor_hint2->set_text(hint_msg2.str());
////				valor_hint2_np = graphic_np.get_parent().attach_new_node(valor_hint2);
////				valor_hint2_np.set_scale(0.05);
////				valor_hint2_np.set_color(0.0, 0.0, 0.0, 1, 0);
////				valor_hint2_np.set_pos(window->get_render_2d(), 0.3, 0.0, -0.2);
////
////			}
////		}
//
////		if (graphic_np.get_y() == 1.0) {
////			if (mouse_x >= 0.03 && mouse_x <= 0.57 && mouse_y >= 0.12 && mouse_y <= 0.66 &&
////					hour >= vetorX->front() && hour <= vetorX->back()) {
////				eixo_hint = new LineSegs("eixo-hint");
////				eixo_hint->set_color(1.0, 0.0, 0.0);
////				eixo_hint->draw_to(0.0, 0.0, 0.0);
////				eixo_hint->draw_to(0.0, 0.0, 0.54);
////				eixo_hint_np = graphic_np.get_parent().attach_new_node(eixo_hint->create(true));
////				eixo_hint_np.set_pos(window->get_render_2d(), mouse_x, 0.0, 0.12);
////				stringstream hint_msg;
////				hint_msg << item_value;
////				valor_hint = new TextNode("valor-hint");
////				valor_hint->set_text(hint_msg.str());
////				valor_hint_np = graphic_np.get_parent().attach_new_node(valor_hint);
////				valor_hint_np.set_scale(0.05);
////				valor_hint_np.set_color(0.0, 0.0, 0.0, 1, 0);
////				valor_hint_np.set_pos(window->get_render_2d(), 0.3, 0.0, 0.7);
////			}
////		} else if (graphic_np.get_y() == 0.1) {
////			if (mouse_x >= 0.03 && mouse_x <= 0.57 && mouse_y >= -0.77 && mouse_y <= -0.23 &&
////					hour >= vetorX->front() && hour <= vetorX->back()) {
////				eixo_hint = new LineSegs("eixo-hint");
////				eixo_hint->set_color(1.0, 0.0, 0.0);
////				eixo_hint->draw_to(0.0, 0.0, 0.0);
////				eixo_hint->draw_to(0.0, 0.0, 0.54);
////				eixo_hint_np = graphic_np.get_parent().attach_new_node(eixo_hint->create(true));
////				eixo_hint_np.set_pos(window->get_render_2d(), mouse_x, 0.0, -0.77);
////				stringstream hint_msg;
////				hint_msg << item_value;
////				valor_hint = new TextNode("valor-hint");
////				valor_hint->set_text(hint_msg.str());
////				valor_hint_np = graphic_np.get_parent().attach_new_node(valor_hint);
////				valor_hint_np.set_scale(0.05);
////				valor_hint_np.set_color(0.0, 0.0, 0.0, 1, 0);
////				valor_hint_np.set_pos(window->get_render_2d(), 0.3, 0.0, -0.2);
////			}
////		}
//
//	}
//
//}

void Graphics::update_hint_line(float line_pos_x, float line_pos_y, float label_pos_y) {
	float hour = (24 * (line_pos_x - 0.03)) / 0.54;
	float item_value = 0;
	std::list<float>::const_iterator iterator, iterator2;
	float previous_x = 0;
	float previous_y = 0;

	if (&eixo_hint_np != NULL) {
		eixo_hint_np.remove_node();
		valor_hint_np.remove_node();
	}

	// Itera os vetores X e Y para pegar o valor de Y equivalente à hora obtida no vetor X
	// Pega a amostra do vetor Y a partir da posição do mouse e da hora equivalente no vetor X

	// ****** Quando pausa o jogo e passa o mouse pelas regiões onde são plotados os gráficos 1 e 2,
	// capota o jogo aqui ******
	for (iterator = vetorX->begin(), iterator2 = vetorY->begin();
		iterator != vetorX->end(), iterator2 != vetorY->end(); ++iterator, ++iterator2) {
		// se o valor de hora do iterator for maior do que o valor de hora equivalente à posição atual do mouse
		// e menor ou igual que o valor de hora guardado anteriormente, pega a amostra anterior e para a iteração
		if (*iterator > hour && previous_x <= hour) {
			item_value = previous_y;
			break;
		}
		previous_x = *iterator; // guarda o valor atual de hora que servirá de condição para a próxima iteração
		previous_y = *iterator2;
	}

	if (hour >= vetorX->front() && hour <= vetorX->back()) {
		eixo_hint = new LineSegs("eixo-hint");
		eixo_hint->set_color(1.0, 0.0, 0.0);
		eixo_hint->draw_to(0.0, 0.0, 0.0);
		eixo_hint->draw_to(0.0, 0.0, 0.54);
		eixo_hint_np = graphic_np.get_parent().attach_new_node(eixo_hint->create(true));
		eixo_hint_np.set_pos(window->get_render_2d(), line_pos_x, 0.0, line_pos_y);
		stringstream hint_msg;
		hint_msg << item_value;
		valor_hint = new TextNode("valor-hint");
		valor_hint->set_text(hint_msg.str());
		valor_hint_np = graphic_np.get_parent().attach_new_node(valor_hint);
		valor_hint_np.set_scale(0.05);
		valor_hint_np.set_color(0.0, 0.0, 0.0, 1, 0);
		valor_hint_np.set_pos(window->get_render_2d(), 0.3, 0.0, label_pos_y);
	}
}

