#pragma once
#ifndef PLAYERACHIEVEMENTS_H
#define	PLAYERACHIEVEMENTS_H

class playerAchievements
{
public:
	
	playerAchievements();
	playerAchievements(int senhor_mordida_estrela,int sobrevivencia_estrela, int bom_de_boca_estrela, int reproducao_estrela,
	int temperatura_estrela, int hidratacao_estrela, int energia_estrela, int intocavel_estrela,int guerreiro_estrela,int senhor_mordida_contador,int sobrevivencia_contador,
	int bom_de_boca_contador, int reproducao_contador, int temperatura_contador, int hidratacao_contador, int energia_contador, int intocavel_contador,int guerreiro_contador);
	
	void set_smestrela(int senhor_estrela);
	void set_svestrela(int sobrevi_estrela);
	void set_bbestrela(int bomde_estrela);
	void set_reestrela(int reprodu_estrela);
	void set_tmestrela(int tempera_estrela);
	void set_hiestrela(int hidrat_estrela);
	void set_enestrela(int energ_estrela);
	void set_inestrela(int intoca_estrela);
	void set_geestrela(int guerre_estrela);
	void set_smcont(int senhor_contador);
	void set_svcont(int sobrevi_contador);
	void set_bbcont(int bomde_contador);
	void set_recont(int reprodu_contador);
	void set_tmcont(int tempera_contador);
	void set_hicont(int hidrat_contador);
	void set_encont(int energ_contador);
	void set_incont(int intoca_contador);
	void set_gecont(int guerre_contador);
	
	int get_smestrela();         
	int get_svestrela();
	int get_bbestrela();
	int get_reestrela();
	int get_tmestrela();
	int get_hiestrela();
	int get_enestrela();
	int get_inestrela();
	int get_geestrela();
	int get_smcont();
	int get_svcont();
	int get_bbcont();
	int get_recont();
	int get_tmcont();
	int get_hicont();
	int get_encont();
	int get_incont();
	int get_gecont();

	~playerAchievements(void);
private:
	int smestrela; int smcont;
	int svestrela; int svcont;
	int bbestrela; int bbcont;
	int reestrela; int recont; 
	int tmestrela; int tmcont;
	int hiestrela; int hicont;
	int enestrela; int encont;
	int inestrela; int incont;
	int geestrela; int gecont;

};
#endif