#include "imageRepository.h"
#include "simdunas.h"


/* Singleton */
bool ImageRepository::instanceFlag = false;
ImageRepository* ImageRepository::single = NULL;

/*! Constrói o repositório de modelos */
ImageRepository::ImageRepository(){
	load_images();
}

/*! Retorna/constrói o repositório de modelos */
ImageRepository* ImageRepository::get_instance() {
	if(!instanceFlag) {
        single = new ImageRepository();
        instanceFlag = true;
    }
    return single;
}


/*! Destrói o repositório de modelos */
ImageRepository::~ImageRepository(){
	instanceFlag = false;
	models.clear();
}


void ImageRepository::load_images(){
	nout << endl << "Carregando imagens" << endl;

	add_image("diaEnoite", "models/gui/diaEnoite.png");
	add_image("ponteiro", "models/gui/ponteiro.png");
	add_image("ponteiro_red", "models/gui/ponteiro_red.png");
	add_image("calango_color", "models/calango_color.png");
	add_image("calango_border", "models/calango_border.png");
	add_image("pisca_life", "models/pisca_life");
	add_image("modeloHidratacao", "models/gui/modeloHidratacao.png");
	add_image("barra-hidratacao-espelhada", "models/gui/barra-hidratacao-espelhada.png");
	add_image("modeloTemperatura", "models/gui/modeloTemperatura.png");
	add_image("barra-hidratacao4", "models/gui/barra-hidratacao4.png");
	add_image("mundo_temp2", "models/gui/mundo_temp2.png");
	add_image("mundo_umi", "models/gui/mundo_umi.png");
	add_image("(fe)male_symbol", "models/gui/(fe)male_symbol.png");
	add_image("GrayLed", "models/gui/GrayLed.png");
	add_image("egg2", "models/gui/egg2.png");
	add_image("graphic_1", "models/gui/graphic_1.jpg");
	add_image("GreenLed", "models/gui/GreenLed.png");
	add_image("mundo_temp3", "models/gui/mundo_temp3.png");
	add_image("modeloNutricional", "models/gui/modeloNutricional.png");
	add_image("modeloEnergia", "models/gui/modeloEnergia.png");
	add_image("modeloGatoEnergetico", "models/gui/modeloGatoEnergetico.png");
	add_image("calendar", "models/gui/calendar.png");
	add_image("predator_left", "models/gui/arrow-left2.png");
	add_image("predator_right", "models/gui/arrow-right2.png");
	add_image("predator_up", "models/gui/arrow-up2.png");
	add_image("predator_down", "models/gui/arrow-down2.png");
}


/*! Obtém uma instância de uma imagem do repositório */
NodePath ImageRepository::get_image(const string &name){
	return models[name].copy_to(aspect2d);
}


/*! Adiciona uma imagem ao repositório:
 * @param name - Nome do modelo, deve ser relevante pois é a chave de acesso futuro.
 * @param path - Caminho do modelo.*/
void ImageRepository::add_image(const string &name, const string &path){
	// Assign to map
	models[name] = window->load_model(Simdunas::get_framework()->get_models(), path);
}
