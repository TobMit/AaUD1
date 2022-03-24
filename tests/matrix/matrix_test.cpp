#include "matrix_test.h"


namespace tests
{
	tests::MatrixTestInterface::MatrixTestInterface() :
		SimpleTest("Interface")
	{
	}

	void tests::MatrixTestInterface::test()
	{
		structures::Matrix<int>* matrix = this->makeMatrix(20, 20);
		matrix->assign(*matrix);
		matrix->equals(*matrix);
		matrix->size();
		matrix->isEmpty();
		matrix->getRowCount();
		matrix->getColumnCount();
		matrix->at(10, 10);
		delete matrix;
		SimpleTest::logPass("Compiled");

	}

	structures::Matrix<int>* CoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncoherentMatrixTestInterface::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	CoherentMatrixTestOverall::CoherentMatrixTestOverall() :
		ComplexTest("CoherentMatrix")
	{
		addTest(new CoherentMatrixTestInterface());
		addTest(new CohereneMatrixFunctionTest());
		addTest(new CohereneMatrixUloha2());
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncoherentMatrixFunctionTest());
	}

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		srand(time(NULL));
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
	}


	// Moje Testovanie CoherenceMatrix
	CohereneMatrixFunctionTest::CohereneMatrixFunctionTest()
		: SimpleTest("Complex test")
	{
	}
	void CohereneMatrixFunctionTest::test()
	{
		structures::CoherentMatrix<int>* matica = new structures::CoherentMatrix<int>(5, 5);
		SimpleTest::assertTrue(matica->size() == 5 * 5, "Matica ma spravnu velkost");

		SimpleTest::logInfo("Naplnam maticu hodnotami");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				matica->at(i, j) = i * 10 + j;
			}
		}
		structures::CoherentMatrix<int>* copyMatica = new structures::CoherentMatrix<int>(*matica);
		SimpleTest::assertTrue(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, mali by byt.");

		SimpleTest::logInfo("Menim hodnotu v copyMatici");
		//SimpleTest::logInfo(std::to_string(copyMatica->at(4, 4)));
		copyMatica->at(1, 3) = 7777;
		SimpleTest::assertTrue(copyMatica->at(1, 3) == 7777, "Kontrolujem ci sa naozaj priradil prvok do matice.");
		SimpleTest::assertFalse(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, nemali by byt.");

		SimpleTest::logInfo("Vkladam copyMaticu do uplne novej matice pomocou assign");
		structures::CoherentMatrix<int>* newMatica = new structures::CoherentMatrix<int>(5, 5);
		newMatica->assign(*copyMatica);
		SimpleTest::assertTrue(newMatica->equals(*copyMatica), "Porovnavam matice ci su rovnake, mali by byt.");



		delete(copyMatica);
		delete(matica);
		delete(newMatica);
	}

	CohereneMatrixUloha2::CohereneMatrixUloha2()
		: SimpleTest("Uloha2")
	{
	}

	void CohereneMatrixUloha2::test()
	{

	
		// scenár A
		structures::CoherentMatrix<int>* matica = new structures::CoherentMatrix<int>(10, 50);
		cyklus('A', 5, 5, 90, *matica);
		delete matica;
		// Scenár B
		matica = new structures::CoherentMatrix<int>(2000, 500);
		cyklus('B', 5, 5, 90, *matica);
		delete matica;

		// Scenár C
		matica = new structures::CoherentMatrix<int>(50, 10);
		cyklus('C', 10, 30, 60, *matica);
		delete matica;

		
		// Scenár D
		matica = new structures::CoherentMatrix<int>(500, 2000);
		cyklus('D', 10, 30, 60, *matica);
		delete matica;
	}

	void CohereneMatrixUloha2::cyklus(char oznacenie, int podielRow, int podielColumn, int podielAt, structures::CoherentMatrix<int>& matica)
	{
		structures::Logger::getInstance().logInfo("Zacal sa test " + std::string(1,oznacenie) + "!");
		SimpleTest::startStopwatch();
		std::vector<char>pool;
		for (unsigned i = 0; i <= 1000000 / podielRow; i++)
		{
			pool.push_back(1);
		}
		for (unsigned i = 0; i <= 1000000 / podielColumn; i++)
		{
			pool.push_back(2);
		}
		for (unsigned i = 0; i <= 1000000 / podielAt; i++)
		{
			pool.push_back(2);
		}

		while (!pool.empty())
		{
			int index = rand() % pool.size();
			switch (pool.at(index))
			{
			case 1:
				matica.getRowCount();
				break;

			case 2:
				matica.getColumnCount();
				break;

			case 3:
				matica.at((rand() % matica.getRowCount()), (rand() % matica.getColumnCount()));
				break;
			}

			pool.erase(pool.begin() + index);
		}

		SimpleTest::stopStopwatch();
		structures::Logger::getInstance().logDuration(0, SimpleTest::getElapsedTime(), "..a trval tolkoto!");

	}


	// Moje Testovanie Incoherence Matrix
	IncoherentMatrixFunctionTest::IncoherentMatrixFunctionTest()
		: SimpleTest("Complex test")
	{
	}
	void IncoherentMatrixFunctionTest::test()
	{
		structures::IncoherentMatrix<int>* matica = new structures::IncoherentMatrix<int>(5, 5);
		SimpleTest::assertTrue(matica->size() == 5 * 5, "Matica ma spravnu velkost");

		SimpleTest::logInfo("Naplnam maticu hodnotami");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				matica->at(i, j) = i * 10 + j;
				//SimpleTest::logInfo(std::to_string(matica->at(i,j)));
			}
		}

		


		structures::IncoherentMatrix<int>* copyMatica = new structures::IncoherentMatrix<int>(*matica);
		SimpleTest::assertTrue(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, mali by byt.");
		
		SimpleTest::logInfo("Menim hodnotu v copyMatici");
		//SimpleTest::logInfo(std::to_string(copyMatica->at(4, 4)));
		copyMatica->at(1, 3) = 7777;
		SimpleTest::assertTrue(copyMatica->at(1, 3) == 7777, "Kontrolujem ci sa naozaj priradil prvok do matice.");
		SimpleTest::assertFalse(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, nemali by byt.");
		
		SimpleTest::logInfo("Vkladam copyMaticu do uplne novej matice pomocou assign");
		structures::IncoherentMatrix<int>* newMatica = new structures::IncoherentMatrix<int>(5, 5);
		newMatica->assign(*copyMatica);
		SimpleTest::assertTrue(newMatica->equals(*copyMatica), "Porovnavam matice ci su rovnake, mali by byt.");


		delete(newMatica);
		delete(copyMatica);
		delete(matica);
	}
	void IncoherentMatrixFunctionTest::uloha2()
	{
	}
	void IncoherentMatrixFunctionTest::cyklus(int podielRow, int podielColumn, int podielAt)
	{
	}
}
