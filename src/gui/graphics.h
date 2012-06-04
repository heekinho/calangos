#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "pandaFramework.h"
#include "lineSegs.h"
#include "simdunas.h"
#include "pgVirtualFrame.h"
#include "textNode.h"
//#include <queue>
#include "history.h"

class Graphics : public TypedReferenceCount {
public:
//    Graphics(NodePath pai, queue<double> vetorXtmp, queue<double> vetorYtmp, double limiteSuperiorXTmp, double limiteInferiorXTmp, double limiteSuperiorYTmp, double limiteInferiorYTmp, bool tipoTempoTmp);
	Graphics(NodePath pai, History::HList* vetorXtmp, History::HList* vetorYtmp, double limiteSuperiorXTmp, double limiteInferiorXTmp, double limiteSuperiorYTmp, double limiteInferiorYTmp, bool tipoTempoTmp);
    ~Graphics();
    void create_Graphic(double tamanhoVetorXtmp, double tamanhoVetorYtmp);
    void set_Position_Graphic(float x, float y);
    void set_scale(float x);
    void hide();
    void set_Titulo_Grafico(const string& tituloString);
    void set_Titulo_EixoX(const string& tituloEixoXString);
    void set_Titulo_EixoY(const string& tituloEixoYString);
    static TypeHandle get_class_type() { return _type_handle; }
    static void init_type() { register_type(_type_handle, "Graphics"); }

private:
    static TypeHandle _type_handle;
    void desenha_eixoX();
    void desenha_eixoY();
    void desenha_marcacao_eixoX();
    void desenha_marcacao_eixoY();
    PGVirtualFrame* graphic_frame;
    LineSegs* eixoX;
    LineSegs* eixoX2;
    LineSegs* eixoY;
    LineSegs* eixoY2;
    NodePath eixoX_np;
    NodePath eixoX2_np;
    NodePath eixoY_np;
    NodePath eixoY2_np;
    NodePath graphic_np;
    TextNode* graphic_titulo;
    NodePath graphic_titulo_np;
    TextNode* graphic_titulo2;
    NodePath graphic_titulo_np2;
    TextNode* graphic_titulo3;
    NodePath graphic_titulo_np3;
    TextNode* graphic_titulo_eixoX;
    NodePath graphic_titulo_eixoX_np;
    TextNode* graphic_titulo_eixoY;
    NodePath graphic_titulo_eixoY_np;
    History::HList* vetorX;
    History::HList* vetorY;
    double limiteSuperiorX;
    double limiteInferiorX;
    double limiteSuperiorY;
    double limiteInferiorY;
    char stringMarcacaoX1[8];
    char stringMarcacaoX2[8];
    char stringMarcacaoX3[8];
    char stringMarcacaoX4[8];
    char stringMarcacaoX5[8];
};

#endif
