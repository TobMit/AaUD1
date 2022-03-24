#pragma once

#include "matrix.h"
#include "../array/array.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;
	private:
		size_t rowCount = 0;
		size_t columnCount = 0;
		Array<Array<T>*>* array_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount):
		rowCount(rowCount),
		columnCount(columnCount)
	{
		array_ = new Array<Array<T>*>(rowCount);
		for (size_t i = 0; i < rowCount; i++)
		{
			Array<T>* pole = new Array<T>(columnCount);
			array_->at(i) = pole;
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other):
		rowCount(other.rowCount),
		columnCount(other.columnCount)
	{
		array_ = new Array<Array<T>*>(rowCount);
		for (size_t i = 0; i < rowCount; i++)
		{
			array_->at(i) = new Array<T>(*(other.array_->at(i)));
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (size_t i = 0; i < rowCount; i++)
		{
			delete array_->at(i);
			array_->at(i) = nullptr;
		}
		delete array_;
		array_ = nullptr;
		rowCount = 0;
		columnCount = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other)
		{
			IncoherentMatrix<T>& otherMatica = dynamic_cast<IncoherentMatrix<T>&>(other);
			if (rowCount == otherMatica.rowCount && columnCount == otherMatica.columnCount)
			{
				array_ = new Array<Array<T>*>(rowCount);
				for (size_t i = 0; i < rowCount; i++)
				{
					array_->at(i) = new Array<T>(*(otherMatica.array_->at(i)));
				}
			}
			else
			{
				throw std::invalid_argument("IncoherentMatrix size differ! Exception from IncoherentMatrix<T>::assign()");
			}
		}

		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		//TODO Zadanie 1: InCoherentMatrix
		throw std::runtime_error("InCoherentMatrix<T>::equals: Not implemented yet.");
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		//TODO Zadanie 1: InCoherentMatrix
		throw std::runtime_error("InCoherentMatrix<T>::size: Not implemented yet.");
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		//TODO Zadanie 1: InCoherentMatrix
		throw std::runtime_error("InCoherentMatrix<T>::getRowCount: Not implemented yet.");
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		//TODO Zadanie 1: InCoherentMatrix
		throw std::runtime_error("InCoherentMatrix<T>::getColumnCount: Not implemented yet.");
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		//TODO Zadanie 1: InCoherentMatrix
		throw std::runtime_error("InCoherentMatrix<T>::at: Not implemented yet.");
	}
}