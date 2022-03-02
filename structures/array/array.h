#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T>
	class Array : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& operator[](int index);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& at(int index);

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception>
		static void copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int index) const;
	};

	template<typename T>
	Array<T>::Array(size_t size) :
		vector_(new Vector(size * sizeof(T))), //jedno poľe sa skladá z jedného vektora. A do vektora sa uloží 3* size of T aby sme nemali pre každý prvok array jeden vektor ale aby to bolo všetko po hromade. Sizeof(T) to preto aby sa vytvorila napr pre int potrebne miesto
 		size_(size)
	{
	}

	template<typename T>
	Array<T>::Array(Array<T>& other) :
		vector_(new Vector(*(other.vector_))), //zavolá sa kopírovací konštruktor poľa a vďaka tomu vytvoríme novú kópiu vektora
		size_(other.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete vector_; //Zavoláme deštruktor poľa
		vector_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	Structure& Array<T>::assign(Structure& other)
	{
		//skotrolujem identitu a ak nie som identicky, tak:
		//	pretypujem other na Array<T>&
		//	skontroluje, ci maju polia rovnaku velkost
		//		ano: necham priradit vektory(assign)
		//		nie: Vynimka!
		
		if (this != &other)
		{
			Array<T>& otherArray = dynamic_cast< Array<T>&>(other);
			if (size_ == otherArray.size_)
			{
				vector_->assign(*otherArray.vector_);  //Vector::assign potrebuje referenciu preto je tam ta *
			}
			else
				throw std::invalid_argument("Array size differ!");
		}
		
		return *this;
	}

	template<typename T>
	inline bool Array<T>::equals(Structure& other)
	{
		// pretypujte si other na Array<T>*
		// to nebude nullptr
		//	vratte vysledok porovnania vektorov (equals)
		//	inak vráte false

		Array<T>* otherArray = dynamic_cast<Array<T>*> (&other);
		if (otherArray != nullptr)
		{
			return vector_->equals(*otherArray->vector_);
			//return vector_->operator==(*otherArray->vector_);
			//return *vector_ == *otherArray->vector_;
			//return vector_ == otherArray->vector_;  //ZLE!!!
		}
		else
			return false;
	}

	template<typename T>
	size_t Array<T>::size()
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](int index)
	{
		return at(index);
	}

	template<typename T>
	inline T& Array<T>::at(int index)
	{
		// 1) ziskajte index vo vektore
		// 2) ziskajte byte* na danom indexe
		// 3) pretypujte ukazovatel na T* (teinterpreter_cast)
		// 4) vrati dereferovany ukazoval z ktroku 3

		int indexInVector = mapFunction(index);
		byte* ptrByte = vector_->getBytePointer(indexInVector);
		T* ptrT = reinterpret_cast<T*> (ptrByte);
		return *ptrT;


	}

	template<typename T>
	void Array<T>::copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length)
	{
		//TODO 02: Array
		throw std::runtime_error("Array<T>::copy: Not implemented yet.");
	}

	template<typename T>
	inline int Array<T>::mapFunction(int index) const
	{
		Utils::rangeCheckExcept(index, size_, "Invalid Index!");
		return index * sizeof(T); //vráti nám začiatok bloku vo vektore
	}
}


