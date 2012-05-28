/*
 * File:   foliage.h
 * Author: tassalon
 * Created on 19 de Maio de 2011, 11:03
 */

#ifndef FOLIAGE_H
#define	FOLIAGE_H

#include "pnmImage.h"
#include "textureStage.h"
#include "texture.h"
#include "referenceCount.h"

class Foliage : public ReferenceCount {
public:
    Foliage();
    Foliage(const Foliage& orig);
    virtual ~Foliage();
    void add_foliage(string path, NodePath vegetal);

    static void set_wireframe(bool enable);

private:

    int terrain_size;
    int block_size;
    PT(Texture) folhagem_texture;
    PT(TextureStage) folhagem_stage;
    //PNMImage *TodaFolhagem;

    static NodePath folhas;
    //int indice;
};

#endif	/* FOLIAGE_H */
