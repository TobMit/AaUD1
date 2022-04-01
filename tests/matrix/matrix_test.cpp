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
		addTest(new CohereneMatrixUloha3());
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
		addTest(new IncoherentMatrixFunctionTest());
		addTest(new IncoherenMatrixUloha2());
		addTest(new IncoherenMatrixUloha3());
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
		structures::Logger::getInstance().logInfo("Testovanie CohereneMatrix!");
	
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
		std::vector<char>pool;

		const int OPAKOVANIA = 1000000;

		for (unsigned i = 0; i <= OPAKOVANIA / podielRow; i++)
		{
			pool.push_back(1);
		}
		for (unsigned i = 0; i <= OPAKOVANIA / podielColumn; i++)
		{
			pool.push_back(2);
		}
		for (unsigned i = 0; i <= OPAKOVANIA / podielAt; i++)
		{
			pool.push_back(3);
		}

		Milliseconds duration = std::chrono::milliseconds(0);
		while (!pool.empty())
		{
			int index = rand() % pool.size();
			switch (pool.at(index))
			{
			case 1:
				SimpleTest::startStopwatch();
				matica.getRowCount();
				SimpleTest::stopStopwatch();
				duration += SimpleTest::getElapsedTime();
				break;

			case 2:
				SimpleTest::startStopwatch();
				matica.getColumnCount();
				SimpleTest::stopStopwatch();
				duration += SimpleTest::getElapsedTime();
				break;

			case 3:
				SimpleTest::startStopwatch();
				matica.at((rand() % matica.getRowCount()), (rand() % matica.getColumnCount()));
				SimpleTest::stopStopwatch();
				duration += SimpleTest::getElapsedTime();
				break;
			}

			pool.erase(pool.begin() + index);
		}

		structures::Logger::getInstance().logDuration(0, duration, ".Troval toľkoto: ");

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


	IncoherenMatrixUloha2::IncoherenMatrixUloha2()
		: SimpleTest("Uloha2")
	{
		
	}
	void IncoherenMatrixUloha2::test()
	{
		structures::Logger::getInstance().logInfo("Testovanie IncoherenMatrix!");
		// scenár A
		structures::IncoherentMatrix<int>* matica = new structures::IncoherentMatrix<int>(10, 50);
		cyklus('A', 5, 5, 90, *matica);
		delete matica;
		// Scenár B
		matica = new structures::IncoherentMatrix<int>(2000, 500);
		cyklus('B', 5, 5, 90, *matica);
		delete matica;

		// Scenár C
		matica = new structures::IncoherentMatrix<int>(50, 10);
		cyklus('C', 10, 30, 60, *matica);
		delete matica;


		// Scenár D
		matica = new structures::IncoherentMatrix<int>(500, 2000);
		cyklus('D', 10, 30, 60, *matica);
		delete matica;
	}
	void IncoherenMatrixUloha2::cyklus(char oznacenie, int podielRow, int podielColumn, int podielAt, structures::IncoherentMatrix<int>& matica)
	{
		structures::Logger::getInstance().logInfo("Zacal sa test " + std::string(1, oznacenie) + "!");
		std::vector<char>pool;

		const int OPAKOVANIA = 1000000;

		for (unsigned i = 0; i <= OPAKOVANIA / podielRow; i++)
		{
			pool.push_back(1);
		}
		for (unsigned i = 0; i <= OPAKOVANIA / podielColumn; i++)
		{
			pool.push_back(2);
		}
		for (unsigned i = 0; i <= OPAKOVANIA / podielAt; i++)
		{
			pool.push_back(3);
		}
		Milliseconds duration = std::chrono::milliseconds(0);
		
		while (!pool.empty())
		{
			int index = rand() % pool.size();
			switch (pool.at(index))
			{
			case 1:
				SimpleTest::startStopwatch();
				matica.getRowCount();
				SimpleTest::stopStopwatch();
				duration += SimpleTest::getElapsedTime();
				break;

			case 2:
				SimpleTest::startStopwatch();
				matica.getColumnCount();
				SimpleTest::stopStopwatch();
				duration += SimpleTest::getElapsedTime();
				break;

			case 3:
				SimpleTest::startStopwatch();
				matica.at((rand() % matica.getRowCount()), (rand() % matica.getColumnCount()));
				SimpleTest::stopStopwatch();
				duration += SimpleTest::getElapsedTime();
				break;
			}

			pool.erase(pool.begin() + index);
		}

		structures::Logger::getInstance().logDuration(0, duration, "Trval toľkoto: ");
	}

	//-------------------------------------------------------------------------------------------------------------------------------
	IncoherenMatrixUloha3::IncoherenMatrixUloha3():
		SimpleTest("Uloha3")
	{
	}
	void IncoherenMatrixUloha3::test()
	{
		structures::Logger::getInstance().logInfo("Testovanie IncoherenceMatrix Uloha 3 - at");
		const int MAX = 3000;	
		const int KROK = 100;
		const int POC_VELKOST = 100;
		const int POC_OPAKOVANI = 100;
		int xSize, ySize;
		xSize = ySize = POC_VELKOST;

		structures::Logger::getInstance().logInfo("Pocet Riadkov, Pocet stlpcov, Priemerna dlzka na " + std::to_string(POC_OPAKOVANI) + " opakovani");
		SimpleTest::logInfo("Testujem AT");

		while (xSize <= MAX && ySize <= MAX)
		{
			structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));

			xSize += KROK;
			// Pripravene pre testovanie neštvorcových matic
			//structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));
			ySize += KROK;
		}

		structures::Logger::getInstance().logInfo("Testovanie IncoherenceMatrix Uloha 3 - Assign");
		SimpleTest::logInfo("Testujem Assign");
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
	Milliseconds IncoherenMatrixUloha3::cyklusAt(int x, int y, const int POC_OPAKOVANI)
	{
		structures::IncoherentMatrix<int>* matica = new structures::IncoherentMatrix<int>(x, y);
		Milliseconds duration = std::chrono::milliseconds(0); // nastaví premennú na nulu
		for (int i = 0; i < POC_OPAKOVANI; i++)
		{
			duration += durationAt(rand() % x, rand() % y, *matica);
		}
		delete matica;
		return duration / POC_OPAKOVANI;
	}
	Milliseconds IncoherenMatrixUloha3::durationAt(int x, int y, structures::IncoherentMatrix<int>& matica)
	{
		SimpleTest::startStopwatch();
		matica.at(x, y) = 7;
		SimpleTest::stopStopwatch();
		return SimpleTest::getElapsedTime();
	}

	//---------------------------------------------------------------------
	Milliseconds IncoherenMatrixUloha3::cyklusAssign(int x, int y, const int POC_OPAKOVANI)
	{
		structures::IncoherentMatrix<int>* matica = new structures::IncoherentMatrix<int>(x, y);
		structures::IncoherentMatrix<int>* maticaAssign = new structures::IncoherentMatrix<int>(x, y);
		Milliseconds duration = std::chrono::milliseconds(0); // nastaví premennú na nulu
		for (int i = 0; i < POC_OPAKOVANI; i++)
		{
			duration += durationAssign(rand() % x, rand() % y, *matica, *maticaAssign);
		}
		delete matica;
		delete maticaAssign;
		return duration / POC_OPAKOVANI;

	}

	Milliseconds IncoherenMatrixUloha3::durationAssign(int x, int y, structures::IncoherentMatrix<int>& matica, structures::IncoherentMatrix<int>& maticaAssign)
	{
		SimpleTest::startStopwatch();
		matica.assign(maticaAssign);
		SimpleTest::stopStopwatch();
		return SimpleTest::getElapsedTime();
	}


	//-------------------------------------------------------------------------------------------------------------------------------
	CohereneMatrixUloha3::CohereneMatrixUloha3():
		SimpleTest("Uloha 3")
	{
	}

	void CohereneMatrixUloha3::test()
	{
		structures::Logger::getInstance().logInfo("Testovanie CoherenceMatrix Uloha 3 - at");
		const int MAX = 3000;
		const int KROK = 100;
		const int POC_VELKOST = 100;
		const int POC_OPAKOVANI = 100;
		int xSize, ySize;
		xSize = ySize = POC_VELKOST;

		structures::Logger::getInstance().logInfo("Pocet Riadkov, Pocet stlpcov, Priemerna dlzka na " + std::to_string(POC_OPAKOVANI) + " opakovani");
		SimpleTest::logInfo("Testujem AT");
		while (xSize <= MAX && ySize <= MAX)
		{
			structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));

			xSize += KROK;
			// Pripravene pre testovanie neštvorcových matic
			//structures::Logger::getInstance().logDuration(0, cyklusAt(xSize, ySize, POC_OPAKOVANI), std::to_string(xSize) + "," + std::to_string(ySize));
			ySize += KROK;
		}

		structures::Logger::getInstance().logInfo("Testovanie CoherenceMatrix Uloha 3 - Assign");
		SimpleTest::logInfo("Testujem Assign");
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

	//---------------------------------------------------------------------------------
	Milliseconds CohereneMatrixUloha3::cyklusAt(int x, int y, const int POC_OPAKOVANI)
	{
		structures::CoherentMatrix<int>* matica = new structures::CoherentMatrix<int>(x, y);
		Milliseconds duration = std::chrono::milliseconds(0); // nastaví premennú na nulu
		for (int i = 0; i < POC_OPAKOVANI; i++)
		{
			duration += durationAt(rand() % x, rand() % y, *matica);
		}
		delete matica;
		return duration / POC_OPAKOVANI;
	}
	Milliseconds CohereneMatrixUloha3::durationAt(int x, int y, structures::CoherentMatrix<int>& matica)
	{
		SimpleTest::startStopwatch();
		matica.at(x, y) = 7;
		SimpleTest::stopStopwatch();
		return SimpleTest::getElapsedTime();
	}

	//---------------------------------------------------------------------------------

	Milliseconds CohereneMatrixUloha3::cyklusAssign(int x, int y, const int POC_OPAKOVANI)
	{
		structures::CoherentMatrix<int>* matica = new structures::CoherentMatrix<int>(x, y);
		structures::CoherentMatrix<int>* maticaAssign = new structures::CoherentMatrix<int>(x, y);
		Milliseconds duration = std::chrono::milliseconds(0); // nastaví premennú na nulu
		for (int i = 0; i < POC_OPAKOVANI; i++)
		{
			duration += durationAssign(rand() % x, rand() % y, *matica, *maticaAssign);
		}
		delete matica;
		delete maticaAssign;
		return duration / POC_OPAKOVANI;
	}

	Milliseconds CohereneMatrixUloha3::durationAssign(int x, int y, structures::CoherentMatrix<int>& matica, structures::CoherentMatrix<int>& maticaAssign)
	{
		SimpleTest::startStopwatch();
		matica.assign(maticaAssign);
		SimpleTest::stopStopwatch();
		return SimpleTest::getElapsedTime();
	}

}
