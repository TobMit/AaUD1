#pragma once

#include "../test.h"
#include "../../structures/matrix/matrix.h"
#include "../../structures/_logger/logger.h"
#include "../../structures/heap_monitor.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"
#include <chrono>

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania matice avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class MatrixTestInterface
		: public SimpleTest
	{
	public:
		MatrixTestInterface();
		void test() override;

	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody koherentnej matice.
	/// </summary>
	class CoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zavola vsetky metody nekoherentnej matice.
	/// </summary>
	class IncoherentMatrixTestInterface
		: public MatrixTestInterface
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherentMatrix.
	/// </summary>
	class CoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		CoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju IncoherentMatrix.
	/// </summary>
	class IncoherentMatrixTestOverall
		: public ComplexTest
	{
	public:
		IncoherentMatrixTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju CoherrentMatrix a IncoherrentMatrix.
	/// </summary>
	class MatrixTestOverall
		: public ComplexTest
	{
	public:
		MatrixTestOverall();
	};

	//--------------------------------------------------------------------------------------------------------------------

	/// <summary>
	/// Otestujem ci som implementoval vsetky metody spravne
	/// </summary>
	class MatrixFunctionTest
		:public SimpleTest
	{
	public:
		MatrixFunctionTest();
		void test() override;
	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
		virtual structures::Matrix<int>* makeMatrix(structures::Matrix<int>& other) const = 0;
	};

	class CohMatrixFunctionTest
		: public MatrixFunctionTest
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
		structures::Matrix<int>* makeMatrix(structures::Matrix<int>& other) const override;
	};

	class IncohMatrixFunctionTest
		: public MatrixFunctionTest
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override;
		structures::Matrix<int>* makeMatrix(structures::Matrix<int>& other) const override;
	};


	//-----------------------------------------------------------------------------------------------------------




	/// <summary>
	/// Testovanie pre úlohu 2
	/// </summary>
	class MatrixUloha2
		:public SimpleTest
	{
	public:
		MatrixUloha2();
		void test() override;
	private:
		void cyklus(char oznacenie, int podielRow, int podielColumn, int podielAt, structures::Matrix<int>& matica);
		int getPomer(int const OPAKOVANIA, int pomer);
	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
		virtual void info() const = 0;
	};


	class CohMatrixUloha2
		: public MatrixUloha2
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override
		{
			return new structures::CoherentMatrix<int>(rows, cols);
		};

		void info() const override
		{
			structures::Logger::getInstance().logInfo("Testovanie CohMatrix!");
		}
	};

	class IncohMatrixUloha2
		: public MatrixUloha2
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override
		{
			return new structures::IncoherentMatrix<int>(rows, cols);
		};
		void info() const override
		{
			structures::Logger::getInstance().logInfo("Testovanie IncohMatrix!");
		}
	};

	//--------------------------------------------------------------------------------------------------------------

	class MatrixUloha3
		:public SimpleTest
	{
	public:
		MatrixUloha3();
		void test() override;
	private:
		Milliseconds cyklusAt(int x, int y, const int POC_OPAKOVANI);
		Milliseconds durationAt(int x, int y, structures::Matrix<int>& matica);

		Milliseconds cyklusAssign(int x, int y, const int POC_OPAKOVANI);
		Milliseconds durationAssign(structures::Matrix<int>& matica, structures::Matrix<int>& maticaAssign);
	protected:
		virtual structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const = 0;
		virtual void infoAt() const = 0;
		virtual void infoAssign() const = 0;

	};

	class CohMatrixUloha3
		: public MatrixUloha3
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override
		{
			return new structures::CoherentMatrix<int>(rows, cols);
		};

		void infoAt() const override
		{
			structures::Logger::getInstance().logInfo("Testovanie CohMatrix - at");
		}
		void infoAssign() const override
		{
			structures::Logger::getInstance().logInfo("Testovanie CohMatrix - Assign");
		}
	};

	class IncohMatrixUloha3
		: public MatrixUloha3
	{
	protected:
		structures::Matrix<int>* makeMatrix(size_t rows, size_t cols) const override
		{
			return new structures::IncoherentMatrix<int>(rows, cols);
		};

		void infoAt() const override
		{
			structures::Logger::getInstance().logInfo("Testovanie IncohMatrix - at");
		}
		void infoAssign() const override
		{
			structures::Logger::getInstance().logInfo("Testovanie IncohMatrix - Assign");
		}
	};

}