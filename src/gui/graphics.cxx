
#include <stddef.h>
#include <queue>
#include "graphics.h"

#define DEBUG false

TypeHandle Graphics::_type_handle;

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
char stringMarcacaoY1[6];
char stringMarcacaoY2[6];
char stringMarcacaoY3[6];
char stringMarcacaoY4[6];
char stringMarcacaoY5[6];
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

Graphics::Graphics(NodePath* paiNode, queue<double> vetorXtmp, queue<double> vetorYtmp,  double limiteSuperiorXTmp, double limiteInferiorXTmp, double limiteSuperiorYTmp, double limiteInferiorYTmp, bool tipoTempoTmp){

    vetorX = vetorXtmp;
    vetorY = vetorYtmp;

    tipoTempo = tipoTempoTmp;

    limiteSuperiorX = limiteSuperiorXTmp;
    limiteInferiorX = limiteInferiorXTmp;
    limiteSuperiorY = limiteSuperiorYTmp;
    limiteInferiorY = limiteInferiorYTmp;

    //window = Simdunas::get_window();
    graphic_frame = new PGVirtualFrame("Frame do grafico");
    graphic_frame->setup(1.1, 1.0);
    PGFrameStyle style = graphic_frame->get_frame_style(graphic_frame->get_state());
    style.set_type(PGFrameStyle::T_flat);
    style.clear_texture();
    graphic_frame->set_frame_style(graphic_frame->get_state(), style);
    graphic_np = paiNode->attach_new_node(graphic_frame);
    //graphic_np.reparent_to(paiNode);
    //graphic_np.set_pos(0.4, 0.0, 0.5);
    graphic_np.set_color(1.0, 1.0, 1.0);

    eixoX = new LineSegs("eixoX");
    eixoX2 = new LineSegs("eixoX2");
    eixoY = new LineSegs("eixoY");
    eixoY2 = new LineSegs("eixoY2");
    
    //eixoX_Marcacao1 = new LineSegs("eixoX-Marcacao1");

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


void Graphics::create_Graphic(double tamanhoVetorXtmp, double tamanhoVetorYtmp) {

    linha_grafico = new LineSegs("linha-grafico");
    linha_grafico->set_color(0.0, 0.0, 0.0);
    double tamanhoVetorX = tamanhoVetorXtmp;
    double tamanhoVetorY = tamanhoVetorYtmp;
    double escalaX;
    double escalaY;
    double posicaoX;
    double posicaoY;


    if (DEBUG) {
        cout << "\n O tamanho do vetor X eh: " << tamanhoVetorX << endl;
        cout << " O tamanho do vetor Y eh: " << tamanhoVetorY << endl;
        cout << " O tipo de grafico eh: " << tipoTempo << endl;
    }

    if(tipoTempo){
        if(DEBUG){
            cout << " Escala tipo tempo" << endl;
        }
        escalaX = 0.63 / (tamanhoVetorX - 1);
        posicaoX = 0;
    } else {
        if (tamanhoVetorX > 0) {
            escalaX = ((100 * 0.0063) / limiteSuperiorX);
            posicaoX = vetorX.front();
            vetorX.pop();
            if (posicaoX > limiteSuperiorX){
                posicaoX = limiteSuperiorX;
            }
            if (posicaoX < limiteInferiorX){
                posicaoX = limiteInferiorX;
            }
        }
    }
    escalaY = ((100 * 0.0063) / limiteSuperiorY);
    
    if (tamanhoVetorY > 0) {
        posicaoY = vetorY.front();
        vetorY.pop();
        if (posicaoY > limiteSuperiorY) {
            posicaoY = limiteSuperiorY;
        }
        if (posicaoY < limiteInferiorY) {
            posicaoY = limiteInferiorY;
        }
        linha_grafico->reset();
        linha_grafico->move_to((posicaoX * escalaX), 0.0, (posicaoY * escalaY));
        //linha_grafico->create(false);
    }

    queue<double> listaTemp = this->vetorX;
    double maior = listaTemp.front();
    int tamanhoFor = listaTemp.size();

    for(int i = 1; i < tamanhoFor; i++){
        if(listaTemp.front() > maior)
            maior = listaTemp.front();
        listaTemp.pop();
    }

    if (tipoTempo) {
        if(DEBUG){
            cout << " Marcacao tipo tempo" << endl;
        }
        //Colocando os numeros das marcacoes do eixo X.
        sprintf(stringMarcacaoX1, "%.1f", (maior / 5));
        marcacaoX1_titulo->set_text(stringMarcacaoX1);
        sprintf(stringMarcacaoX2, "%.1f", (2 * (maior / 5)));
        marcacaoX2_titulo->set_text(stringMarcacaoX2);
        sprintf(stringMarcacaoX3, "%.1f", (3 * (maior / 5)));
        marcacaoX3_titulo->set_text(stringMarcacaoX3);
        sprintf(stringMarcacaoX4, "%.1f", (4 * (maior / 5)));
        marcacaoX4_titulo->set_text(stringMarcacaoX4);
        sprintf(stringMarcacaoX5, "%.1f", maior);
        marcacaoX5_titulo->set_text(stringMarcacaoX5);
    } else {
        //Colocando os numeros das marcacoes do eixo X.
        sprintf(stringMarcacaoX1, "%.1f", (limiteInferiorX));
        marcacaoX1_titulo->set_text(stringMarcacaoX1);
        sprintf(stringMarcacaoX2, "%.1f", (((limiteSuperiorX - limiteInferiorX) / 4)) + limiteInferiorX);
        marcacaoX2_titulo->set_text(stringMarcacaoX2);
        sprintf(stringMarcacaoX3, "%.1f", ((2 * ((limiteSuperiorX - limiteInferiorX) / 4))) + limiteInferiorX);
        marcacaoX3_titulo->set_text(stringMarcacaoX3);
        sprintf(stringMarcacaoX4, "%.1f", ((3 * ((limiteSuperiorX - limiteInferiorX) / 4))) + limiteInferiorX);
        marcacaoX4_titulo->set_text(stringMarcacaoX4);
        sprintf(stringMarcacaoX5, "%.1f", (limiteSuperiorX));
        marcacaoX5_titulo->set_text(stringMarcacaoX5);
    }

    //Colocando os numeros das marcacoes do eixo Y.
    sprintf(stringMarcacaoY1, "%.1f", (limiteInferiorY));
    marcacaoY1_titulo->set_text(stringMarcacaoY1);
    sprintf(stringMarcacaoY2, "%.1f", (((limiteSuperiorY - limiteInferiorY) / 4)) + limiteInferiorY);
    marcacaoY2_titulo->set_text(stringMarcacaoY2);
    sprintf(stringMarcacaoY3, "%.1f", ((2 * ((limiteSuperiorY - limiteInferiorY) / 4))) + limiteInferiorY);
    marcacaoY3_titulo->set_text(stringMarcacaoY3);
    sprintf(stringMarcacaoY4, "%.1f", ((3 * ((limiteSuperiorY - limiteInferiorY) / 4))) + limiteInferiorY);
    marcacaoY4_titulo->set_text(stringMarcacaoY4);
    sprintf(stringMarcacaoY5, "%.1f", (limiteSuperiorY));
    marcacaoY5_titulo->set_text(stringMarcacaoY5);

    if(DEBUG){
        cout << " A legenda da posicao Y1 ficou: " << stringMarcacaoY1 << endl;
        cout << " A legenda da posicao Y2 ficou: " << stringMarcacaoY2 << endl;
        cout << " A legenda da posicao Y3 ficou: " << stringMarcacaoY3 << endl;
        cout << " A legenda da posicao Y4 ficou: " << stringMarcacaoY4 << endl;
        cout << " A legenda da posicao Y5 ficou: " << stringMarcacaoY5 << endl;
    }

    /*
     * For que constroi o grafico.
     * Comeca de 1 porque a primeira amostra foi postada anteriormente.
     */
    if ((tamanhoVetorY > 0) & (tamanhoVetorX > 0)) {
        for (int i = 1; i < tamanhoVetorX; i++) {
            posicaoY = vetorY.front();
            vetorY.pop();
            if (posicaoY > limiteSuperiorY) {
                posicaoY = limiteSuperiorY;
            }
            if (posicaoY < limiteInferiorY) {
                posicaoY = limiteInferiorY;
            }

//            if(DEBUG){
//                cout << " Tipo = " << tipoTempo << endl;
//            }

            if (tipoTempo) {
//                if (DEBUG) {
//                    cout << "\n Entrou no grafico de tempo: " << tipoTempo << endl;
//                }
                posicaoX = posicaoX + escalaX;
                linha_grafico->draw_to(posicaoX, 0.0, (posicaoY * escalaY));
            } else {
//                if (DEBUG) {
//                    cout << "\n Entrou no grafico de variavel: " << tipoTempo << endl;
//                }
                posicaoX = vetorX.front();
                vetorX.pop();
                if (posicaoX > limiteSuperiorX) {
                    posicaoX = limiteSuperiorX;
                }
                if (posicaoX < limiteInferiorX) {
                    posicaoX = limiteInferiorX;
                }
                linha_grafico->move_to(((posicaoX * escalaX) + 0.005), 0.0, (posicaoY * escalaY));
                linha_grafico->draw_to(((posicaoX * escalaX) - 0.01), 0.0, (posicaoY * escalaY));
                //linha_grafico->draw_to((posicaoX * escalaX), 0.0, (posicaoY * escalaY));
                linha_grafico->move_to((posicaoX * escalaX), 0.0, (posicaoY * escalaY) + 0.008);
                linha_grafico->draw_to((posicaoX * escalaX), 0.0, ((posicaoY * escalaY) - 0.016));
                //linha_grafico->draw_to((posicaoX * escalaX), 0.0, ((posicaoY * escalaY) + 0.010));
                //linha_grafico->draw_to((posicaoX * escalaX), 0.0, ((posicaoY * escalaY) - 0.005));
            }

            //posicaoY = posicaoY + escala;
        }
    }
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
    this->graphic_np.hide();
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

void Graphics::desenha_marcacao_eixoX(){

    if (tipoTempo) {
        posicao_marcacaoX1 = 0.276;
        posicao_marcacaoX2 = 0.402;
        posicao_marcacaoX3 = 0.528;
        posicao_marcacaoX4 = 0.654;
        posicao_marcacaoX5 = 0.780;
    } else {
        unidade_marcacaoX = ((100 * 0.0063) / limiteSuperiorX);
        posicao_marcacaoX5 = (limiteSuperiorX * unidade_marcacaoX) + 0.15;
        posicao_marcacaoX1 = (limiteInferiorX * unidade_marcacaoX) + 0.15;
        posicao_marcacaoX2 = ((posicao_marcacaoX5 - posicao_marcacaoX1) / 4) + posicao_marcacaoX1;
        posicao_marcacaoX3 = (2 * (posicao_marcacaoX5 - posicao_marcacaoX1) / 4) + posicao_marcacaoX1;
        posicao_marcacaoX4 = (3 * (posicao_marcacaoX5 - posicao_marcacaoX1) / 4) + posicao_marcacaoX1;
    }


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
	marcacaoX1_titulo_np.set_pos(posicao_marcacaoX1 - 0.03, 0.0, 0.09);
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
	marcacaoX2_titulo_np.set_pos(posicao_marcacaoX2 - 0.03, 0.0, 0.09);
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
	marcacaoX3_titulo_np.set_pos(posicao_marcacaoX3 - 0.03, 0.0, 0.09);
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
	marcacaoX4_titulo_np.set_pos(posicao_marcacaoX4 - 0.03, 0.0, 0.09);
	marcacaoX4_titulo_np.set_scale(0.04);
  	marcacaoX4_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);

        LineSegs* marcacaoX5 = new LineSegs("mx5");
        marcacaoX5->set_color(0.0, 0.0, 1.0);
        marcacaoX5->draw_to(0.0, 0.0, 0.0);
        marcacaoX5->draw_to(0.0, 0.0, 0.035);
        NodePath marcacaoX5_np = graphic_np.attach_new_node(marcacaoX5->create());
        marcacaoX5_np.set_pos(posicao_marcacaoX5, 0.0, 0.13);
        //legenda da marcação 5
        marcacaoX5_titulo = new TextNode("legendamarcacaoX5");
	marcacaoX5_titulo->set_text("");
	marcacaoX5_titulo_np = graphic_np.attach_new_node(marcacaoX5_titulo);
	marcacaoX5_titulo_np.set_pos(posicao_marcacaoX5 - 0.03, 0.0, 0.09);
	marcacaoX5_titulo_np.set_scale(0.04);
  	marcacaoX5_titulo_np.set_color(0.0, 0.0, 0.0, 1,0);
}

void Graphics::desenha_marcacao_eixoY() {

    unidade_marcacaoY = ((100 * 0.0063) / limiteSuperiorY);
    posicao_marcacaoY5 = (limiteSuperiorY * unidade_marcacaoY) + 0.15;
    posicao_marcacaoY1 = (limiteInferiorY * unidade_marcacaoY) + 0.15;
    posicao_marcacaoY2 = ((posicao_marcacaoY5 - posicao_marcacaoY1) / 4) + posicao_marcacaoY1;
    posicao_marcacaoY3 = (2 * (posicao_marcacaoY5 - posicao_marcacaoY1) / 4) + posicao_marcacaoY1;
    posicao_marcacaoY4 = (3 * (posicao_marcacaoY5 - posicao_marcacaoY1) / 4) + posicao_marcacaoY1;
    
    if (DEBUG) {
        cout << " A unidade marcacao Y ficou: " << unidade_marcacaoY << endl;
        cout << " A posicao Y1 ficou: " << posicao_marcacaoY1 << endl;
        cout << " A posicao Y2 ficou: " << posicao_marcacaoY2 << endl;
        cout << " A posicao Y3 ficou: " << posicao_marcacaoY3 << endl;
        cout << " A posicao Y4 ficou: " << posicao_marcacaoY4 << endl;
        cout << " A posicao Y5 ficou: " << posicao_marcacaoY5 << endl;
    }


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
    marcacaoY1_titulo_np.set_pos(0.05, 0.0, posicao_marcacaoY1 - 0.01);
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
    marcacaoY2_titulo_np.set_pos(0.05, 0.0, posicao_marcacaoY2 - 0.01);
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
    marcacaoY3_titulo_np.set_pos(0.05, 0.0, posicao_marcacaoY3 - 0.01);
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
    marcacaoY4_titulo_np.set_pos(0.05, 0.0, posicao_marcacaoY4 - 0.01);
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
    marcacaoY5_titulo_np.set_pos(0.05, 0.0, posicao_marcacaoY5 - 0.01);
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

