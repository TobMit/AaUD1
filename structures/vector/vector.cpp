#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	// konštruktor 
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)), // priradujú sa tam hodnoty, calloc inicializuje urèitú ve¾kos a + inicializuje pamä 0
		size_(size) // to v zátvorkách je inicializácia, je efektívnejšia než cez operátor priradenia =
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
		free(memory_); // vymaže dáta z memory
		memory_ = nullptr;
		size_ = 0;
		//aby sa nestalo, že by som neskôr pristupoval k vymazanému objektu, tak je to lepšie si prekry, inak to bude fungova dobre
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other) { // overuejem, èi sa nesnažím prideli sám seba, sebe (ak sa chápem xD)
			Vector& otherVector = dynamic_cast<Vector&>(other); //dynamic cast vráti to èo je v hranatých zátvorkách
			// keby to pretypovávame v zátvorkách, tak to je static cast, je to èítate¾nejšie, a robí viacej kontrol
			// a potom pri refaktoringu sa ¾ahšie dá vyh¾ada
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_); //aby nám pôvodný smerník po realokovaní ukazoval na nový repsektíve správny
			memcpy(memory_, otherVector.memory_, size_);
		}

		return *this;  //vraciam samého seba, pretože som uravoval samého seba.
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other)
		{
			return true;
		}
		else
		{
			Vector* otherVector = dynamic_cast<Vector*>(&other); // &other -> ukozovate¾ na structure a Vector* je pointer, ak sa nepodarí pretypova tak vratí NULL
			if (otherVector != nullptr)
			{
				return size_ == otherVector->size_ && memcmp(memory_, otherVector->memory_, size_) == 0; //na bitovej úrovni porovná dva pamäťové bloky
			}

			else
			{
				return false;
			}
		}
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		return *getBytePointer(index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		Utils::rangeCheckExcept(srcStartIndex, src.size_, "Invalid starting Index! (exception from Vector::copy)");
		Utils::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid source length! (exception from Vector::copy)");
		Utils::rangeCheckExcept(destStartIndex, dest.size_, "Invalid destination Index! (exception from Vector::copy)");
		Utils::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid source length! (exception from Vector::copy)");
		// abs je absolutna hodnota
		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length) { //overím či sa nesnaží kopírovať ten istý vektor do toho istého vektora a zároveň sa miesta prekrívajú
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {

			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		Utils::rangeCheckExcept(index, size_, "Invalid index!");   // toto je trieda ktorú spravili na unize pre nás, aby sme stále to isté neprogramovali
		return reinterpret_cast<byte*>(memory_) + index;
	}
}