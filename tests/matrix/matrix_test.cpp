#include "matrix_test.h"
#include "../../structures/matrix/coherent_matrix.h"
#include "../../structures/matrix/incoherent_matrix.h"

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
	}

	IncoherentMatrixTestOverall::IncoherentMatrixTestOverall() :
		ComplexTest("IncoherentMatrix")
	{
		addTest(new IncoherentMatrixTestInterface());
	}

	MatrixTestOverall::MatrixTestOverall() :
		ComplexTest("Matrix")
	{
		addTest(new CoherentMatrixTestOverall());
		addTest(new IncoherentMatrixTestOverall());
	}


	// Moje Testovanie
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
		copyMatica->at(1, 3) = 7777;
		SimpleTest::logInfo(std::to_string(copyMatica->at(1, 3)));
		SimpleTest::logInfo(std::to_string(matica->at(1, 3)));
		SimpleTest::assertFalse(matica->equals(*copyMatica), "Porovnavam matice ci su rovnake, nemali by byt.");

	}
}
