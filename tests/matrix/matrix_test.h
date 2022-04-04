#pragma once

#include "../test.h"
#include "../../structures/matrix/matrix.h"
#include "../../structures/_logger/logger.h"
//#include "../../structures/heap_monitor.h"
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

	/// <summary>
	/// Otestujem ci som implementoval vsetky metody spravne
	/// </summary>
	class CohereneMatrixFunctionTest
		:public SimpleTest
	{
	public:
		CohereneMatrixFunctionTest();
		void test() override;
	};

	/// <summary>
	/// Testovanie pre �lohu 2
	/// </summary>
	class CohereneMatrixUloha2
		:public SimpleTest
	{
	public:
		CohereneMatrixUloha2();
		void test() override;
	private:
		void cyklus(char oznacenie,int podielRow, int podielColumn, int podielAt, structures::CoherentMatrix<int>& matica);
	};


	/// <summary>
	/// Testujem �i som implementoval v�etky met�dy spr�vne
	/// </summary>
	class IncoherentMatrixFunctionTest :
		public SimpleTest
	{
	public:
		IncoherentMatrixFunctionTest();
		void test() override;
	};

	/// <summary>
	/// Testovanie pre �lohu 2
	/// </summary>
	class IncoherenMatrixUloha2
		:public SimpleTest
	{
	public:
		IncoherenMatrixUloha2();
		void test() override;
	private:
		void cyklus(char oznacenie, int podielRow, int podielColumn, int podielAt, structures::IncoherentMatrix<int>& matica);
	};


	class IncoherenMatrixUloha3
		:public SimpleTest
	{
	public:
		IncoherenMatrixUloha3();
		void test() override;
	private:
		Microseconds cyklusAt(int x, int y, const int POC_OPAKOVANI);
        Microseconds durationAt(int x, int y, structures::IncoherentMatrix<int>& matica);

        Microseconds cyklusAssign(int x, int y, const int POC_OPAKOVANI);
        Microseconds durationAssign(int x, int y, structures::IncoherentMatrix<int>& matica, structures::IncoherentMatrix<int>& maticaAssign);


	};

	class CohereneMatrixUloha3
		:public SimpleTest
	{
	public:
		CohereneMatrixUloha3();
		void test() override;
	private:
        Microseconds cyklusAt(int x, int y, const int POC_OPAKOVANI);
        Microseconds durationAt(int x, int y, structures::CoherentMatrix<int>& matica);

        Microseconds cyklusAssign(int x, int y, const int POC_OPAKOVANI);
        Microseconds durationAssign(int x, int y, structures::CoherentMatrix<int>& matica, structures::CoherentMatrix<int>& maticaAssign);
	};
}