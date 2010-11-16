#ifndef IMAGEREPOSITORY_H
#define IMAGEREPOSITORY_H

#include <string>
#include <vector>

#include "nodePathCollection.h"


/*! Um ImageRepository armazena as imagens e abstrai o recurso de instancing do Panda3D */
class ImageRepository {
public:
	// Singleton
	static ImageRepository* get_instance();
	~ImageRepository();

	void add_image(const string &name, const string &path);

	NodePath get_image(const string &name);

private:
	/* Controle do Singleton */
	static bool instanceFlag;
	static ImageRepository *single;

	ImageRepository();

	map<string, NodePath> models;

	void load_images();
};

#endif
