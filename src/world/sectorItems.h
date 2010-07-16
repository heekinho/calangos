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
	Type get_closest_to(LPoint3f ref);

    INLINE void push_front(const Type& item);
    INLINE void push_back(const Type& item);

	INLINE void pop_front();
	INLINE void pop_back();
    INLINE void remove(const Type& item);
private:
    PT(Setor) _sector;
};

#include "sectorItems.I"

#endif
