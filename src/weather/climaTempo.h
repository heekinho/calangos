/*Essa classe é responsável por controlar as temperaturas do ambiente (ar, solo e toca). A cada dia (virtual), os valores de 
temperaturas máximas e mínimas são obtidas mediante um sorteio normal e, a partir desses valores, as temperaturas 
são atualizadas a cada hora virtual.*/

#ifndef CLIMATEMPO_H
#define CLIMATEMPO_H

#include "timeControl.h"
#include "eventHandler.h"
#include "eventQueue.h"
#include "simdunas.h"

class ClimaTempo : public TypedReferenceCount{

public:
	ClimaTempo();
	~ClimaTempo();

	//Singleton
	static PT(ClimaTempo) get_instance();

	//Método responsável por manter atualizados os valores das variáveis ambientais
    void ambient_control(int hour,int month);

	//M�todos respons�veis pelos c�lculos do valores das vari�veis ambientais

	//retorna a temperatura do ar na hora espec�ficada
	double temp_ar_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday);
	//retorna temperatura do solo na hora especificada
	double temp_solo_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday, float prevTmin, float prevTmax, float preVariaton);
	//retorna temperatura das tocas na hora especificada
	double temp_toca_single(int hour, float nextMin, float nextMax, float nextVariation, float tminToday, float tmaxToday, float variationToday, float prevTmin, float prevTmax, float preVariaton);
	//recebe a temperatura do ar e devolve a umidade relativa naquele instante
	double umidade_relativa(double tempAr);
	/*retorna a quantidade de chuvas em um dia, o c�lculo � feito de acordo com o m�s
	*passado como par�metro*/
	double prob_chuva(int mes);

	/*recebe a esperan�a e a vari�ncia de uma curva normal e retorna um valor sorteado
	*aleatoriamente, de acordo com as vari�veis recebidas*/
	double random_normal(double esp,double var);

	//get's
	double get_temp_ar();
	double get_temp_solo();
	double get_temp_toca();
	double get_chuva_today();
	double get_umi_rel();

	//processa evento de passagem de hora(�nico que interessa at� o momento), onde as temperaturas serão atualizadas
	static void event_phour_temp(const Event *, void *data);

	//destroi o objeto e/ou qualquer referência a ele
	static void unload_climaTempo();

	//armazena a quantidade de chuvas para cada dia
	double qtChuva;
	//armazena temperatura do ar, que � atualizada a cada hora
	double tempArControl;
	//armazena temperatura do solo, que � atualizada a cada hora
	double tempSoloControl;
	//armazena temperatura do toca, que � atualizada a cada hora
	double temTocaControl;
	//armazena umidade relativa do ar, que � atualizada a cada hora
	double umidadeRel;
	//varia�ao da temperatura entre 0:00 e 5:00 do dia anterior
	double variationPrev;
	//variacao da temperatura entre 0:00 e 5:00 de hoje
	double variationToday;
	//variacao da temperatura entre 0:00 e 5:00 de amanha
	double nextVariation;
	//variacao da temperatura entre 0:00 e 5:00 daqui a dois dias
	double nextVariation2;
	//temperatura m�xima do dia anterior
	double maxPrev;
	//temperatura m�nima do dia anterior
	double minPrev;
	//temperatura m�xima do dia corrente
	double tmaxToday;
	//temperatura m�nima do dia corrente
	double tminToday;
	//temperatura m�xima do dia seguinte
	double nextMax;
	//temperatura m�nima do dia seguinte
	double nextMin;
	//temperatura m�xima em dois dias
	double nextMax2;
	//temperatura m�nima em dois dias
	double nextMin2;
	int initialization;
	//armazena temperaturas do ar para conferencia
	vector<double> vectorTempAr;
	//ponteiro para gravar os dados do vector em arquivo texto
	FILE *arquivo;

	// Typed Object
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "ClimaTempo"); }

private:
	static bool instanceFlag;
	static PT(ClimaTempo) single;
	static TypeHandle _type_handle;
};

#endif
