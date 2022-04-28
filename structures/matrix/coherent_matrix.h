#pragma once

#include "matrix.h"
#include <stdexcept>
#include <cstring>
#include "../utils.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

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
		void* memory_;
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount):
		rowCount(rowCount),
		columnCount(columnCount),
		memory_(std::calloc(sizeof(T)* rowCount* columnCount, 1))
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) :
		CoherentMatrix<T>(other.rowCount, other.columnCount)
	{
		memcpy(memory_, other.memory_, other.size() * sizeof(T));
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		free(memory_);
		memory_ = nullptr;
		rowCount = 0;
		columnCount = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this != &other) {
			CoherentMatrix<T>& otherCohMatrix = dynamic_cast<CoherentMatrix<T>&>(other);
			if (rowCount == otherCohMatrix.getRowCount() && columnCount == otherCohMatrix.getColumnCount())
			{
				memcpy(memory_, otherCohMatrix.memory_, otherCohMatrix.size() * sizeof(T));
			}
			else {
				throw std::invalid_argument("Matrix size diff! Expe trow in CoherentMatrix<T>::assig()");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		if (this == &other) {
			return true;
		}
		else {
			CoherentMatrix<T>* otherCohMatrix = dynamic_cast<CoherentMatrix<T>*>(&other);
			if (otherCohMatrix != nullptr) {
				return size() == otherCohMatrix->size() && memcmp(memory_, otherCohMatrix->memory_, otherCohMatrix->size() * sizeof(T)) == 0;
			}
			else {
				return false;
			}
		}
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return rowCount * columnCount;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return rowCount;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return columnCount;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, rowCount, "Invalid rowIndex! Exception from CoherentMatrix<T>::at()");
		Utils::rangeCheckExcept(columnIndex, columnCount, "Invalid columnIndex! Exception from CoherentMatrix<T>::at()");
		byte* ptrByte = reinterpret_cast<byte*> (memory_) + ((rowIndex * columnCount + columnIndex) * sizeof(T));
		T* ptrT = reinterpret_cast<T*> (ptrByte);
		return *ptrT;

	}
}