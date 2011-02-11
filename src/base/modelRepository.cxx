#include "modelRepository.h"

#include "simdunas.h"
#include "menu.h"

#define PALETTIZE_VEGETABLES 0

/* Singleton */
bool ModelRepository::instanceFlag = false;
ModelRepository* ModelRepository::single = NULL;

/*! Constrói o repositório de modelos */
ModelRepository::ModelRepository(){
	load_models();
}

/*! Retorna/constrói o repositório de modelos */
ModelRepository* ModelRepository::get_instance() {
	if(!instanceFlag) {
        single = new ModelRepository();
        instanceFlag = true;
    }
    return single;
}


/*! Destrói o repositório de modelos */
ModelRepository::~ModelRepository(){
	instanceFlag = false;
	models.clear();
	animated_models.clear();
}



//TODO: Criar load_models lendo um arquivo de configuração.
/*! Carrega os modelos. Pode ser realizado de forma distribuída também, mas pode ser bom
 * manter esta tarefa centralizada. */
void ModelRepository::load_models(){
	// Personagens
	nout << endl << "Carregando PCs" << endl;

	/* Informa o path do lagarto a ser carregado */
	string lizard_name;

	lizard_name = Player::get_specie_name(Player::lizard_specie) + "/" + Player::get_gender_name(Player::female);
	load_player_models(lizard_name);

	lizard_name = Player::get_specie_name(Player::lizard_specie) + "/" + Player::get_gender_name(Player::male);
	load_player_models(lizard_name);

	lizard_name = Player::get_specie_name(Player::lizard_specie) + "/" + Player::get_gender_name(Player::young);
	load_player_models(lizard_name);


	// Animais
	nout << endl << "Carregando NPCs" << endl;

	/* Outros Animais */
	add_model("sapo", "models/npcs/sapo");

	/* Presas */
	//TODO: Criar método para criar um conjunto: (aranha, besouro, cupim...)
	add_model("aranha", "models/npcs/aranha_anim");
	add_animated_model("aranha",  "models/npcs/", "aranha_anim",  "");

	add_model("besouro", "models/npcs/besouro_anim");
	add_animated_model("besouro", "models/npcs/", "besouro_anim", "");

	add_model("cupim", "models/npcs/cupim_anim");
	add_animated_model("cupim",   "models/npcs/", "cupim_anim",   "");

	add_model("formiga", "models/npcs/formiga_anim");
	add_animated_model("formiga", "models/npcs/", "formiga_anim", "");

	add_model("grilo", "models/npcs/grilo_anim");
	add_animated_model("grilo",   "models/npcs/", "grilo_anim",   "");

	add_model("larva", "models/npcs/larva_anim");
	add_animated_model("larva",   "models/npcs/", "larva_anim",   "");

	/* Predadores */
	string siriema_anims[] = {"siriema_andar", "siriema_comer", "siriema_correr", "siriema_stand"};
	add_animated_model("siriema", "models/npcs/predators/siriema/", "siriema_model", "", 4, siriema_anims);

	string raposa_anims[] = {"raposa_andar", "raposa_comer", "raposa_stand", "raposa_stand2"};
	add_animated_model("raposa", "models/npcs/predators/raposa/", "raposa_model", "", 4, raposa_anims);

	string gato_anims[] = {"gato_andar", "gato_comer", "gato_comer2", "gato_stand"};
	add_animated_model("gato", "models/npcs/predators/gato/", "gato_model", "", 4, gato_anims);

	string teiu_anims[] = {"teiu_andar", "teiu_morder", "teiu_morder2"};
	add_animated_model("teiu", "models/npcs/predators/teiu/", "teiu_model", "", 3, teiu_anims);

	string jararaca_anims[] = {"jararaca_rastejar", "jararaca_eating", "jararaca_stand"};
	add_animated_model("jararaca", "models/npcs/predators/jararaca/", "jararaca_model", "", 3, jararaca_anims);

	string colubridae_anims[] = {"colubridae_andar", "colubridae_morder", "colubridae_stand"};
	add_animated_model("colubridae", "models/npcs/predators/colubridae/", "colubridae_model", "", 3, colubridae_anims);
	
	/* Predadores Voadores */
	string coruja_anims[] = {"coruja_voar", "coruja_comer", "coruja_stand"};
	add_animated_model("coruja", "models/npcs/predators/coruja/", "coruja_model", "", 3, coruja_anims);


	/* Vegetais */
	nout << endl << "Carregando Vegetais" << endl;
	load_vegetals();


	/* Objects */
	nout << endl << "Carregando Objetos" << endl;
	add_model("cerca", "models/objects/cerca");
	add_model("casa1", "models/objects/casa1");
	add_model("casa2", "models/objects/casa2");
	add_model("casa3", "models/objects/casa3");
	add_model("toca", "models/objects/toca");
}

void ModelRepository::load_vegetals(){
	/* Para testar vegetais com apenas uma textura */
	if(PALETTIZE_VEGETABLES) palettize_mod();
	else {
		add_model("bromelia-seco", "models/vegetation/Bromelia/bromelia2");
		add_model("colher-seco","models/vegetation/Colher/colher");
		add_model("eugenia-seco","models/vegetation/Eugenia/eugenia_model");
		add_model("mandacaru-seco","models/vegetation/Mandacaru/mandacaru");
		add_model("mimosa-seco", "models/vegetation/Mimosa/mimosa");
		add_model("murici-seco","models/vegetation/Murici/murici_rasteiro");
		add_model("quipa-seco","models/vegetation/Quipa/quipa_model");
		add_model("simaba-seco","models/vegetation/Simaba/simaba_model");
		add_model("xique_xique-seco", "models/vegetation/Xique_xique/xique_model");
		add_model("bocoa-seco","models/vegetation/Bocoa/bocoa");
		add_model("chamaecrista-seco","models/vegetation/Chamaecrista/chamaecrista");
		add_model("copaifera-seco","models/vegetation/Copaifera/copaifera_model");
		add_model("croton-seco","models/vegetation/Croton/croton_model");
		add_model("harpochilus-seco","models/vegetation/Harpochilus/harpochilus_model");
		add_model("jatropha-seco","models/vegetation/Jatropha/jatropha_model");

		add_model("bromelia-chuvoso", "models/vegetation/Bromelia/bromelia");
		add_model("colher-chuvoso","models/vegetation/Colher/colher");
		add_model("eugenia-chuvoso","models/vegetation/Eugenia/eugenia_model_flor");
		add_model("mandacaru-chuvoso","models/vegetation/Mandacaru/mandacaru_model_florefruto");
		add_model("mimosa-chuvoso", "models/vegetation/Mimosa/mimosa");
		add_model("murici-chuvoso","models/vegetation/Murici/murici_flor");
		add_model("quipa-chuvoso","models/vegetation/Quipa/quipa_model_florfruto");
		add_model("simaba-chuvoso","models/vegetation/Simaba/simaba_model_flor");
		add_model("xique_xique-chuvoso", "models/vegetation/Xique_xique/xique_florefruto");
		add_model("bocoa-chuvoso","models/vegetation/Bocoa/bocoa_frutos");
		add_model("chamaecrista-chuvoso","models/vegetation/Chamaecrista/chamaecrista_flor_fruto");
		add_model("copaifera-chuvoso","models/vegetation/Copaifera/copaifera_flores_frutos");
		add_model("croton-chuvoso","models/vegetation/Croton/croton_folhas_flores_frutos");
		add_model("harpochilus-chuvoso","models/vegetation/Harpochilus/harpochilus_model");
		add_model("jatropha-chuvoso","models/vegetation/Jatropha/jatropha_flores_frutos");

		// Vegetais Comestiveis
		//(OK) Sapucaia-flor
		//(OK) Pinhao-flor
		//(OK) Eugenia-flor
		//(FALTA) Simaba-flor
		//(OK) Colher-flor
		//(OK) Colher-fruto
		//(OK) Murici-flor
		//(OK) Murici-fruto
		//(OK) xique-xique-fruto

		nout << endl << "Carregando Vegetais Comestiveis" << endl;
		add_model("copaifera-flor","models/vegetation/Copaifera/flor_copaifera");
		add_model("jatropha-flor","models/vegetation/Jatropha/flor_jatropha");
		add_model("eugenia-flor","models/vegetation/Eugenia/eugenia_flor");
		add_model("colher-flor","models/vegetation/Colher/flor_colher");
		add_model("colher-fruto","models/vegetation/Colher/fruto_colher");
		add_model("murici-flor","models/vegetation/Murici/murici_flor_sep");
		add_model("murici-fruto","models/vegetation/Murici/murici_fruto");
		add_model("xique_xique-fruto","models/vegetation/Xique_xique/xique_fruto");

		//nao cometiveis
		//add_model("quipa-fruto","models/vegetation/Quipa/fruto_quipa");
		//add_model("eugenia-fruto","models/vegetation/Eugenia/eugenia_fruto");
		//add_model("mandacaru-fruto","models/vegetation/Mandacaru/mandacaru_fruto");
	}
}

/* Para usar, tente rodar o script egg-palettize.sh na pasta dos vegetais e
 * setar PALETTIZE_VEGETABLES para 1 */
void ModelRepository::palettize_mod(){
	const string path = "models/vegetation/result/";
	add_model("bromelia-seco", path + "bromelia2");
	add_model("colher-seco", path + "colher");
	add_model("eugenia-seco", path + "eugenia_model");
	add_model("mandacaru-seco", path + "mandacaru");
	add_model("mimosa-seco", path + "mimosa");
	add_model("murici-seco", path + "murici_rasteiro");
	add_model("quipa-seco", path + "quipa_model");
	add_model("simaba-seco", path + "simaba_model");
	add_model("xique_xique-seco",  path + "xique_model");
	add_model("bocoa-seco", path + "bocoa");
	add_model("chamaecrista-seco", path + "chamaecrista");
	add_model("copaifera-seco", path + "copaifera_model");
	add_model("croton-seco", path + "croton_model");
	add_model("harpochilus-seco", path + "harpochilus_model");
	add_model("jatropha-seco", path + "jatropha_model");

	add_model("bromelia-chuvoso",  path + "bromelia");
	add_model("colher-chuvoso", path + "colher");
	add_model("eugenia-chuvoso", path + "eugenia_model_flor");
	add_model("mandacaru-chuvoso", path + "mandacaru_model_florefruto");
	add_model("mimosa-chuvoso",  path + "mimosa");
	add_model("murici-chuvoso", path + "murici_flor");
	add_model("quipa-chuvoso", path + "quipa_model_florfruto");
	add_model("simaba-chuvoso", path + "simaba_model_flor");
	add_model("xique_xique-chuvoso",  path + "xique_florefruto");
	add_model("bocoa-chuvoso", path + "bocoa_frutos");
	add_model("chamaecrista-chuvoso", path + "chamaecrista_flor_fruto");
	add_model("copaifera-chuvoso", path + "copaifera_flores_frutos");
	add_model("croton-chuvoso", path + "croton_folhas_flores_frutos");
	add_model("harpochilus-chuvoso", path + "harpochilus_model");
	add_model("jatropha-chuvoso", path + "jatropha_flores_frutos");

	nout << endl << "Carregando Vegetais Comestiveis" << endl;
	add_model("copaifera-flor", path + "flor_copaifera");
	add_model("jatropha-flor", path + "flor_jatropha");
	add_model("eugenia-flor", path + "eugenia_flor");
	add_model("colher-flor", path + "flor_colher");
	add_model("colher-fruto", path + "fruto_colher");
	add_model("murici-flor", path + "murici_flor_sep");
	add_model("murici-fruto", path + "murici_fruto");
	add_model("xique_xique-fruto", path + "xique_fruto");
}

/*! Carrega o modelo dos lagartos. Este método bem poderia ser migrado para a classe Player */
void ModelRepository::load_player_models(const string &lizard_name){
	string path = "models/lizards/" + lizard_name + "/";

	/* Informa quais são os modelos */
	//int num_anims = 7; string l_anims[] = {"walk", "run", "eat", "fast_bite", "slow_bite", "bobbing", "stand"};
	int num_anims = 3; string l_anims[] = {"walk", "fast_bite", "bobbing"};

	/* Carrega os lagartos */
	add_animated_model(lizard_name, path, "model", "", num_anims, l_anims);
}



/*! Obtém o modelo armazenado no repositório */
PT(ObjetoJogo) ModelRepository::get_model(const string &name){
	return models[name];
}


/*! Obtém o modelo animado armazenado no repositório */
PT(AnimatedObjetoJogo) ModelRepository::get_animated_model(const string &name){
	return animated_models[name];
}


/*! Obtém uma instância de um modelo do repositório */
PT(ObjetoJogo) ModelRepository::get_model_instance(const string &name){
	if(get_model(name) != NULL) return new ObjetoJogo(get_model(name));
	else nout << "O modelo \"" << name << "\" não existe." << endl;

	return NULL;
}


/*! Obtém uma instância animada de um modelo do repositório */
PT(AnimatedObjetoJogo) ModelRepository::get_animated_model_instance(const string &name){
	if(get_animated_model(name) != NULL) return new AnimatedObjetoJogo(get_animated_model(name));
	else nout << "O modelo \"" << name << "\" não existe." << endl;

	return NULL;
}


/*! Adiciona um modelo ao repositório:
 * @param name - Nome do modelo, deve ser relevante pois é a chave de acesso futuro.
 * @param path - Caminho do modelo.*/
void ModelRepository::add_model(const string &name, const string &path){
	PT(ObjetoJogo) object = new ObjetoJogo(path);
	object->set_name(name);

	// Assign to map
	models[name] = object;
}


/*! Adiciona um modelo animado ao repositório
 * @param name - Nome do objeto usado para fazer o mapeamento no repositório.
 * @param path - Caminho do modelo.
 * @param anims - Vetor com os caminhos para os modelos. */
void ModelRepository::add_animated_model(const string &name, const string &path, const string &model,
		const string &filetype, int num_anims, string anims[]){

	/* Carrega Objetos com animação. */
	PT(AnimatedObjetoJogo) object = new AnimatedObjetoJogo(path + model + filetype);
	object->set_name(name);


	for(int i = 0; i < num_anims; i++) Simdunas::get_window()->load_model(*object, Filename(path + anims[i] + filetype));


	/* Bind Anims */
	object->bind_anims(object->node());

	animated_models[name] = object;
}
