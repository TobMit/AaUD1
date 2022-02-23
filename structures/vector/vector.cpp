#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	// konštruktor 
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)), // priradujú sa tam hodnoty, calloc inicializuje urèitú ve¾kos a + inicializuje pamä 0
		size_(size) // to v zátvorkách je inicializácia, je efektívnejšia ne cez operátor priradenia =
	{	
	}

	//kopírovací konštruktor
	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_); //skopíruje pamä s pôvodného vectora do nového vectora
	}

	Vector::~Vector()
	{
		free(memory_); // vymae dáta z memory
		memory_ = nullptr;
		size_ = 0;
		//aby sa nestalo, e by som neskôr pristupoval k vymazanému objektu, tak je to lepšie si prekry, inak to bude fungova dobre
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other) { // overuejem, èi sa nesnaím prideli sám seba, sebe (ak sa chápem xD)
			Vector& otherVector = dynamic_cast<Vector&>(other); //dynamic cast vráti to èo je v hranatıch zátvorkách
			// keby to pretypovávame v zátvorkách, tak to je static cast, je to èítate¾nejšie, a robí viacej kontrol
			// a potom pri refaktoringu sa ¾ahšie dá vyh¾ada
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_); //aby nám pôvodnı smerník po realokovaní ukazoval na novı repsektíve správny
		}

		return *this;  //vraciam samého seba, pretoe som uravoval samého seba.
	}

	bool Vector::equals(Structure& other)
	{
		//TODO 01: Vector
		throw std::runtime_error("Vector::equals: Not implemented yet.");
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		//TODO 01: Vector
		throw std::runtime_error("Vector::at: Not implemented yet.");
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		//TODO 01: Vector
		throw std::runtime_error("Vector::copy: Not implemented yet.");
	}

	byte* Vector::getBytePointer(int index)
	{
		//TODO 01: Vector
		throw std::runtime_error("Vector::getBytePointer: Not implemented yet.");
	}
}