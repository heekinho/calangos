/*! Inicia o hidratação e valor nutricional em 0 */

INLINE Edible::Edible(){

	_nutritional = 0;

	_hydration = 0;

}



/*! Inicializa os valores conforme especificado*/

INLINE Edible::Edible(float nutritional, float hydration){

	_nutritional = nutritional;

	_hydration = hydration;

}



INLINE Edible::Specie Edible::get_specie_value() {

	return _specie;

}



INLINE void Edible::set_specie_value(Edible::Specie specie) {

	_specie = specie;

}



/*! Obtém o valor nutricional associado */

INLINE float Edible::get_nutritional_value() const {

	return _nutritional;

}



/*! Define o valor nutricional associado */

INLINE void Edible::set_nutritional_value(float nutritional){

	_nutritional = nutritional;

}



/*! Obtém a hidratação associada */

INLINE float Edible::get_hydration_value() const {

	return _hydration;

}



/*! Define o valor de hidratação associado */

INLINE void Edible::set_hydration_value(float hydration) {

	_hydration = hydration;

}

