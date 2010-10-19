/*! Obtém o tamanho "real" em metros (1m = 1u do panda) do objeto */
INLINE LVecBase3f ObjetoJogo::get_size() const {
	return _size * get_sy(); /* Era pra ser uniform, mas funciona como obter comprimento */
}

/*! Obtém a largura "real" em metros (1m = 1u do panda) do objeto */
INLINE float ObjetoJogo::get_width() const {
	return _size[0] * get_sx();
}

/*! Obtém o comprimento "real" em metros (1m = 1u do panda) do objeto */
INLINE float ObjetoJogo::get_length() const {
	return _size[1] * get_sy();
}

/*! Obtém a altura "real" em metros (1m = 1u do panda) do objeto */
INLINE float ObjetoJogo::get_height() const {
	return _size[2] * get_sz();
}

/*! Define as dimensões "reais" do objeto em metros (1m = 1u do panda) */
INLINE void ObjetoJogo::set_size(const LVecBase3f &size){
	set_size(size[0], size[1], size[2]);
}

/*! Redefine o tamanho do objeto para o tamanho original da geometria */
INLINE void ObjetoJogo::reset_size() {
	set_size(_osize);
}


/*! Retorna um valor de deslocamento do objeto no eixo Z, para ajustes */
INLINE double ObjetoJogo::get_offset_z(){
	return this->offset_z;
}


/*! Obtém a distância para um outro NodePath */
INLINE float ObjetoJogo::get_distance(const NodePath &other){
	return get_distance(other.get_pos());
}

/* Obtém a distância para um determinado ponto */
INLINE float ObjetoJogo::get_distance(LPoint3f other){
	return (get_pos() - other).length();
}

/*! Obtém a distância para um outro NodePath */
INLINE float ObjetoJogo::get_distance_squared(const NodePath &other){
	return get_distance_squared(other.get_pos());
}

/* Obtém a distância para um determinado ponto */
INLINE float ObjetoJogo::get_distance_squared(LPoint3f other){
	return (get_pos() - other).length_squared();
}

INLINE void ObjetoJogo::look_at(const NodePath &other){
	NodePath::look_at(other);
	if(is_inverted() == -1) set_h(*this, 180);
}


/* Sobreescreveu-se para informar ao código de maneira fácil o movimento.
 * ------------------------------------------------------------------- */

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_pos(float x, float y, float z){
	this->NodePath::set_pos(x, y, z);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_pos(const LVecBase3f &pos){
	this->NodePath::set_pos(pos);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_x(float x){
	this->NodePath::set_x(x);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_y(float y){
	this->NodePath::set_y(y);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_z(float z){
	this->NodePath::set_z(z);
//	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_pos(const NodePath &other, const LVecBase3f &pos){
	this->NodePath::set_pos(other, pos);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_x(const NodePath &other, float x){
	this->NodePath::set_x(other, x);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_y(const NodePath &other, float y){
	this->NodePath::set_y(other, y);
	this->has_moved();
}

/*! Sobreescreve o método de NodePath como uma forma de informar ao resto do
 * código que o player se moveu */
INLINE void ObjetoJogo::set_z(const NodePath &other, float z){
	this->NodePath::set_z(other, z);
//	// Se moveu...
//	this->has_moved();
}
