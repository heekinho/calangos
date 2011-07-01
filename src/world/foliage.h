/*
 * File:   foliage.h
 * Author: tassalon
 *
 * Created on 19 de Maio de 2011, 11:03
 */

#ifndef FOLIAGE_H
#define	FOLIAGE_H

#include "pnmImage.h"
#include "textureStage.h"
#include "texture.h"

class foliage{
public:
    foliage();
    foliage(const foliage& orig);
    virtual ~foliage();
    void add_foliage(string path, NodePath vegetal);
    static void wire_frame_folhas();
    static void wire_frame_folhas_off();


private:

    int terrain_size;
    int block_size;
    PT(Texture) folhagem_texture;
    PT(TextureStage) folhagem_stage;
    PNMImage *TodaFolhagem;

    static NodePath folhas;
    //int indice;


};

#endif	/* FOLIAGE_H */