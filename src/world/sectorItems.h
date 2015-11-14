#ifndef SECTORITEMS_H
#define SECTORITEMS_H

#include "pandaFramework.h"
#include <list>

class Setor;

template<class Type>
class SectorItems : public list<Type> {
public:
	INLINE SectorItems(PT(Setor) sector = NULL);
	~SectorItems(){ _sector = NULL; };

	INLINE void set_sector(PT(Setor) sector);
	INLINE PT(Setor) get_sector();
	Type get_closest_to(const LPoint3f &ref);

    INLINE void push_front(const Type& item);
    INLINE void push_back(const Type& item);

	INLINE void pop_front();
	INLINE void pop_back();
    INLINE void remove(const Type& item);

    INLINE void deep_clear();

    INLINE NodePath get_root() const {
    	return _root;
    }

    INLINE void set_root(NodePath np) const {
    	_root = np;
    }

private:
    NodePath _root;
    PT(Setor) _sector;
};

#include "sectorItems.I"

#endif
