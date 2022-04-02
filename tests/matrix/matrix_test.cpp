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
		addTest(new CohMatrixFunctionTest());
		addTest(new CohMatrixUloha2());
		addTest(new CohMatrixUloha3());

	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncohMatrixFunctionTest());
		addTest(new IncohMatrixUloha2());
		addTest(new IncohMatrixUloha3());
	}

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		srand(time(NULL));
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
	}


	// Moje Testovanie CoherenceMatrix
	MatrixFunctionTest::MatrixFunctionTest()
		: SimpleTest("Complex test")
	{
	}
	void MatrixFunctionTest::test()
	{
		structures::Matrix<int>* matica = this->makeMatrix(5, 5);
		SimpleTest::assertTrue(matica->size() == 5 * 5, "Matica ma spravnu velkost");

		SimpleTest::logInfo("Naplnam maticu hodnotami");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				matica->at(i, j) = i * 10 + j;
			}
		}
		structures::Matrix<int>* copyMatica = this->makeMatrix(*matica);
		SimpleTest::assertTrue(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, mali by byt.");

		SimpleTest::logInfo("Menim hodnotu v copyMatici");
		//SimpleTest::logInfo(std::to_string(copyMatica->at(4, 4)));
		copyMatica->at(1, 3) = 7777;
		SimpleTest::assertTrue(copyMatica->at(1, 3) == 7777, "Kontrolujem ci sa naozaj priradil prvok do matice.");
		SimpleTest::assertFalse(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, nemali by byt.");

		SimpleTest::logInfo("Vkladam copyMaticu do uplne novej matice pomocou assign");
		structures::Matrix<int>* newMatica = this->makeMatrix(5, 5);
		newMatica->assign(*copyMatica);
		SimpleTest::assertTrue(newMatica->equals(*copyMatica), "Porovnavam matice ci su rovnake, mali by byt.");



		delete(copyMatica);
		delete(matica);
		delete(newMatica);
	}

	structures::Matrix<int>* CohMatrixFunctionTest::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::CoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* CohMatrixFunctionTest::makeMatrix(structures::Matrix<int>& other) const
	{
		structures::CoherentMatrix<int>& matica = dynamic_cast<structures::CoherentMatrix<int>&>(other);
		return new structures::CoherentMatrix<int>(matica);
	}

	structures::Matrix<int>* IncohMatrixFunctionTest::makeMatrix(size_t rows, size_t cols) const
	{
		return new structures::IncoherentMatrix<int>(rows, cols);
	}

	structures::Matrix<int>* IncohMatrixFunctionTest::makeMatrix(structures::Matrix<int>& other) const
	{
		structures::IncoherentMatrix<int>& matica = dynamic_cast<structures::IncoherentMatrix<int>&>(other);
		return new structures::IncoherentMatrix<int>(matica);
	}



	//----------------------------------------------------------------------------------------------------------------------------
	MatrixUloha2::MatrixUloha2()
		: SimpleTest("Uloha2")
	{
		
	}
	void MatrixUloha2::test()
	{
		structures::Logger::getInstance().logInfo("Testovanie Uloha2!");
		this->info();
		// scenár A
		structures::Matrix<int>* matica = this->makeMatrix(10, 50);
		cyklus('A', 5, 5, 90, *matica);
		delete matica;

		// Scenár B
		matica = this->makeMatrix(2000, 500);
		cyklus('B', 5, 5, 90, *matica);
		delete matica;

		// Scenár C
		matica = this->makeMatrix(50, 10);
		cyklus('C', 10, 30, 60, *matica);
		delete matica;


		// Scenár D
		matica = this->makeMatrix(500, 2000);
		cyklus('D', 10, 30, 60, *matica);
		delete matica;
	}
	void MatrixUloha2::cyklus(char oznacenie, int podielRow, int podielColumn, int podielAt, structures::Matrix<int>& matica)
	{
		const int OPAKOVANIA = 1000000;

		structures::Logger::getInstance().logInfo("Zacal sa test " + std::string(1, oznacenie) + "!");
		structures::Logger::getInstance().logInfo("Celkovo getRow, Celkovo getColum, Celkovo at, celkova dlzka Scenara " + std::string(1, oznacenie) + "!");

		int opRow = getPomer(OPAKOVANIA, podielRow);
		int opCol = getPomer(OPAKOVANIA, podielColumn);
		int opAt = getPomer(OPAKOVANIA, podielAt);
			
		std::vector<char>pool;
		for (unsigned i = 0; i < opRow; i++)
		{
			pool.push_back(1);
		}
		for (unsigned i = 0; i < opCol; i++)
		{
			pool.push_back(2);
		}
		for (unsigned i = 0; i < opAt; i++)
		{
			pool.push_back(3);
		}

		
		Milliseconds durationRow = std::chrono::microseconds(0);
		Milliseconds durationColumn = std::chrono::microseconds(0);
		Milliseconds durationAt = std::chrono::microseconds(0);

		// todo uprava vypisova aby to vypysovalo aj jednotlive priemery
		while (!pool.empty())
		{
			int index = rand() % pool.size();
			switch (pool.at(index))
			{
			case 1:
				SimpleTest::startStopwatch();
				matica.getRowCount();
				SimpleTest::stopStopwatch();
				durationRow += SimpleTest::getElapsedTime();
				break;

			case 2:
				SimpleTest::startStopwatch();
				matica.getColumnCount();
				SimpleTest::stopStopwatch();
				durationColumn += SimpleTest::getElapsedTime();
				break;

			case 3:
				
				int row = rand() % matica.getRowCount();
				int column = rand() % matica.getColumnCount();

				SimpleTest::startStopwatch();
				matica.at(row, column);
				SimpleTest::stopStopwatch();
				durationAt += SimpleTest::getElapsedTime();

				break;
			}

			pool.erase(pool.begin() + index);
		}

		structures::Logger::getInstance().logDuration(0, durationRow + durationColumn + durationAt, std::to_string(durationRow.count() ) + "," + std::to_string(durationColumn.count()) + "," + std::to_string(durationAt.count()));
	}

	int MatrixUloha2::getPomer(int const OPAKOVANIA, int pomer)
	{
		return (pomer * OPAKOVANIA) / 100;
	}


	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	MatrixUloha3::MatrixUloha3():
		SimpleTest("Uloha3")
	{
	}
	void MatrixUloha3::test()
	{
		structures::Logger::getInstance().logInfo("Testovanie Uloha3!");
		this->infoAt();
		const int MAX = 3000;	
		const int KROK = 100;
		const int POC_VELKOST = 100;
		const int POC_OPAKOVANI = 100;
		int xSize, ySize;
		xSize = ySize = POC_VELKOST;

		structures::Logger::getInstance().logInfo("Pocet Riadkov, Pocet stlpcov, Priemerna dlzka na " + std::to_string(POC_OPAKOVANI) + " opakovani");

		while (xSize <= MAX && ySize <= MAX)
		{
			structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));

			xSize += KROK;
			// Pripravene pre testovanie neštvorcových matic
			//structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));
			ySize += KROK;
		}

		//--------------------Assign-----------------
		this->infoAssign();

		xSize = ySize = POC_VELKOST;
		while (xSize <= MAX && ySize <= MAX)
		{
			structures::Logger::getInstance().logDuration(0, cyklusAssign(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));

			xSize += KROK;
			// Pripravene pre testovanie neštvorcových matic
			//structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));
			ySize += KROK;
		}

	}

	//------------------------------------------------------------------------
	Milliseconds MatrixUloha3::cyklusAt(int x, int y, const int POC_OPAKOVANI)
	{
		structures::Matrix<int>* matica = this->makeMatrix(x, y);
		Milliseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu
		for (int i = 0; i < POC_OPAKOVANI; i++)
		{
			duration += durationAt(rand() % x, rand() % y, *matica);
		}
		delete matica;
		return duration / POC_OPAKOVANI;
	}
	Milliseconds MatrixUloha3::durationAt(int x, int y, structures::Matrix<int>& matica)
	{
		SimpleTest::startStopwatch();
		matica.at(x, y) = 7;
		SimpleTest::stopStopwatch();
		return SimpleTest::getElapsedTime();
	}

	//---------------------------------------------------------------------
	Milliseconds MatrixUloha3::cyklusAssign(int x, int y, const int POC_OPAKOVANI)
	{
		structures::Matrix<int>* matica = this->makeMatrix( x, y);
		structures::Matrix<int>* maticaAssign = this->makeMatrix(x, y);
		Milliseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

		for (int i = 0; i < POC_OPAKOVANI; i++)
		{
			duration += durationAssign(*matica, *maticaAssign);
		}
		delete matica;
		delete maticaAssign;
		return duration / POC_OPAKOVANI;

	}

	Milliseconds MatrixUloha3::durationAssign(structures::Matrix<int>& matica, structures::Matrix<int>& maticaAssign)
	{
		SimpleTest::startStopwatch();
		matica.assign(maticaAssign);
		SimpleTest::stopStopwatch();
		return SimpleTest::getElapsedTime();
	}

}
