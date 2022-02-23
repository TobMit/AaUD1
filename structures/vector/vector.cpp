#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	// konötruktor 
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)), // priraduj˙ sa tam hodnoty, calloc inicializuje urËit˙ veækosù a + inicializuje pam‰ù 0
		size_(size) // to v z·tvork·ch je inicializ·cia, je efektÌvnejöia neû cez oper·tor priradenia =
	{	
	}

	//kopÌrovacÌ konötruktor
	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_); //skopÌruje pam‰ù s pÙvodnÈho vectora do novÈho vectora
	}

	Vector::~Vector()
	{
		free(memory_); // vymaûe d·ta z memory
		memory_ = nullptr;
		size_ = 0;
		//aby sa nestalo, ûe by som neskÙr pristupoval k vymazanÈmu objektu, tak je to lepöie si prekryù, inak to bude fungovaù dobre
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)
	{
		if (this != &other) { // overuejem, Ëi sa nesnaûÌm prideliù s·m seba, sebe (ak sa ch·pem xD)
			Vector& otherVector = dynamic_cast<Vector&>(other); //dynamic cast vr·ti to Ëo je v hranat˝ch z·tvork·ch
			// keby to pretypov·vame v z·tvork·ch, tak to je static cast, je to ËÌtateænejöie, a robÌ viacej kontrol
			// a potom pri refaktoringu sa æahöie d· vyhæadaù
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_); //aby n·m pÙvodn˝ smernÌk po realokovanÌ ukazoval na nov˝ repsektÌve spr·vny
		}

		return *this;  //vraciam samÈho seba, pretoûe som uravoval samÈho seba.
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other)
		{
			return true;
		}
		else
		{
			Vector& otherVector = dynamic_cast<Vector*>(&other); // &other -> ukozovateæ na structure a Vector* je pointer, ak sa nepodarÌ pretypovaù tak vratÌ NULL
			if (&otherVector != nullptr)
			{
				return  size_ = otherVector->size_ && memcmp(memory_, otherVector ->memory_, size_) = 0;
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