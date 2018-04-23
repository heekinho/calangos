#include "playerAchievements.h"

playerAchievements::playerAchievements(int senhor_mordida_estrela,int sobrevivencia_estrela, int bom_de_boca_estrela, int reproducao_estrela,
	int temperatura_estrela, int hidratacao_estrela, int energia_estrela, int intocavel_estrela,int guerreiro_estrela,int senhor_mordida_contador,int sobrevivencia_contador,
	int bom_de_boca_contador, int reproducao_contador, int temperatura_contador, int hidratacao_contador, int energia_contador, int intocavel_contador,int guerreiro_contador)
{
	smestrela = senhor_mordida_estrela; smcont = senhor_mordida_contador;
	svestrela = sobrevivencia_estrela; svcont = sobrevivencia_contador;
	bbestrela = bom_de_boca_estrela; bbcont = bom_de_boca_contador;
	reestrela = reproducao_estrela; recont = reproducao_contador; 
	tmestrela = temperatura_estrela; tmcont = temperatura_contador;
	hiestrela = hidratacao_estrela; hicont = hidratacao_contador;
	enestrela = energia_estrela; encont = energia_contador;
	inestrela = intocavel_estrela; incont = intocavel_contador;
	geestrela = guerreiro_estrela; gecont = guerreiro_contador;
}

playerAchievements::playerAchievements(){
	smestrela = 0; smcont = 0;
	svestrela = 0; svcont = 0;
	bbestrela = 0; bbcont = 0;
	reestrela = 0; recont = 0; 
	tmestrela = 0; tmcont = 0;
	hiestrela = 0; hicont = 0;
	enestrela = 0; encont = 0;
	inestrela = 0; incont = 0;
	geestrela = 0; gecont = 0;
}

playerAchievements::~playerAchievements(void)
{

}

int playerAchievements::get_smestrela()
{
	return smestrela;
}
int playerAchievements::get_svestrela()
{
	return svestrela;
}
int playerAchievements::get_bbestrela()
{
	return bbestrela;
}
int playerAchievements::get_reestrela()
{
	return reestrela;
}
int playerAchievements::get_tmestrela()
{
	return tmestrela;
}
int playerAchievements::get_hiestrela()
{
	return hiestrela;
}
int playerAchievements::get_enestrela()
{
	return enestrela;
}
int playerAchievements::get_inestrela()
{
	return inestrela;
}
int playerAchievements::get_geestrela()
{
	return geestrela;
}
int playerAchievements::get_smcont()
{
	return smcont;
}
int playerAchievements::get_svcont()
{
	return svcont;
}
int playerAchievements::get_bbcont()
{
	return bbcont;
}
int playerAchievements::get_recont()
{
	return recont;
}
int playerAchievements::get_tmcont()
{
	return tmcont;
}
int playerAchievements::get_hicont()
{
	return hicont;
}
int playerAchievements::get_encont()
{
	return encont;
}
int playerAchievements::get_incont()
{
	return incont;
}
int playerAchievements::get_gecont()
{
	return gecont;
}


void playerAchievements::set_smestrela(int senhor_estrela)
{
	smestrela = senhor_estrela;
}
void playerAchievements::set_svestrela(int sobrevi_estrela)
{
	svestrela = sobrevi_estrela;
}
void playerAchievements::set_bbestrela(int bomde_estrela)
{
	bbestrela = bomde_estrela;
}
void playerAchievements::set_reestrela(int reprodu_estrela)
{
	reestrela = reprodu_estrela;
}
void playerAchievements::set_tmestrela(int tempera_estrela)
{
	tmestrela = tempera_estrela;
}
void playerAchievements::set_hiestrela(int hidrat_estrela)
{
	hiestrela = hidrat_estrela;
}
void playerAchievements::set_enestrela(int energ_estrela)
{
	enestrela = energ_estrela;
}
void playerAchievements::set_inestrela(int intoca_estrela)
{
	inestrela = intoca_estrela;
}
void playerAchievements::set_geestrela(int guerre_estrela)
{
	geestrela = guerre_estrela;
}

void playerAchievements::set_smcont(int senhor_contador)
{
	smcont = senhor_contador;
}
void playerAchievements::set_svcont(int sobrevi_contador)
{
	svcont = sobrevi_contador;
}
void playerAchievements::set_bbcont(int bomde_contador)
{
	bbcont = bomde_contador;
}
void playerAchievements::set_recont(int reprodu_contador)
{
	recont = reprodu_contador;
}
void playerAchievements::set_tmcont(int tempera_contador)
{
	tmcont = tempera_contador;
}
void playerAchievements::set_hicont(int hidrat_contador)
{
	hicont = hidrat_contador;
}
void playerAchievements::set_encont(int energ_contador)
{
	encont = energ_contador;
}
void playerAchievements::set_incont(int intoca_contador)
{
	incont = intoca_contador;
}
void playerAchievements::set_gecont(int guerre_contador)
{
	gecont = guerre_contador;
}