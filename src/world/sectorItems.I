#include "setor.h"

/*! Constrói uma lista especial para armazenar e gerenciar os elementos
 * presentes nos setores */
template<class Type>
INLINE SectorItems<Type>::SectorItems(PT(Setor) sector) {
	_sector = sector;
	_root = NodePath(typeid(Type).name());
}

/*! Define o setor associado à esta lista de elementos */
template<class Type>
INLINE void SectorItems<Type>::set_sector(PT(Setor) sector) {
	_sector = sector;
}

/*! Obtém o setor associado à esta lista de elementos */
template<class Type>
INLINE PT(Setor) SectorItems<Type>::get_sector() {
	return _sector;
}

/*! Obtém o objeto mais próximo ao ponto de referência. */
template<class Type>
INLINE Type SectorItems<Type>::get_closest_to(const LPoint3f &ref) {
	float dist = INT_MAX;
	Type closest = NULL;

	typename list<Type>::iterator it;
	for (it = list<Type>::begin(); it != list<Type>::end(); ++it) {
		float cdist = (*it)->get_distance_squared(ref);
		if(cdist < dist) {
			closest = *it;
			dist = cdist;
		}
	}
	return closest;
}

/*! Insere elementos na frente da lista */
template<class Type>
INLINE void SectorItems<Type>::push_front(const Type& item) {
	item->set_setor(_sector);
	list<Type>::push_front(item);
	item->reparent_to(_root);
}

/*! Insere elementos no final da lista */
template<class Type>
INLINE void SectorItems<Type>::push_back(const Type& item) {
	item->set_setor(_sector);
	list<Type>::push_back(item);
	item->reparent_to(_root);
}

/*! Remove o primeiro elemento da lista */
template<class Type>
INLINE void SectorItems<Type>::pop_front() {
	if(list<Type>::front()) list<Type>::front()->set_setor(NULL);
	list<Type>::front()->reparent_to(NodePath(""));
	list<Type>::pop_front();
}

/*! Remove o último elemento da lista */
template<class Type>
INLINE void SectorItems<Type>::pop_back() {
	if(list<Type>::back()) list<Type>::back()->set_setor(NULL);
	list<Type>::back()->reparent_to(NodePath(""));
	list<Type>::pop_back();
}

/*! Remove determinado elemento da lista */
template<class Type>
INLINE void SectorItems<Type>::remove(const Type& item) {
	item->set_setor(NULL);
	list<Type>::remove(item);
}

/*! Remove determinado elemento da lista e o exclui usando delete! */
template<class Type>
INLINE void SectorItems<Type>::deep_clear() {
	typename list<Type>::iterator it;
	for (it = list<Type>::begin(); it != list<Type>::end(); ++it) {
		delete (*it);
	}
}
