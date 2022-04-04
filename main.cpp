
#include "tests/vector/vector_test.h"
#include "tests/array/array_test.h"
#include "tests/list/list_test.h"
#include "tests/stack/stack_test.h"
#include "tests/queue/queue_test.h"
#include "tests/priority_queue/priority_queue_test.h"
#include "tests/table/table_test.h"
#include "tests/tree/tree_test.h"
#include "ui/ui_keeper.h"
#include "ui/console.h"
#include "file_log_consumer.h"
#include "matrix/matrix_test.h"
#include <cstdio>

int main()
{
	ui::UiKeeper keeper;
	structures::Logger::getInstance().registerConsumer(&keeper);

    auto fileLogConsumer = new structures::FileLogConsumer("log.csv");
    structures::Logger::getInstance().registerConsumer(fileLogConsumer);

	// TODO 01: Vector
	keeper.registerTest(new tests::VectorTestOverall());

	// TODO 02: Array
	keeper.registerTest(new tests::ArrayTestOverall());

	// TODO 03: List
	keeper.registerTest(new tests::ListTestOverall());

	// TODO 05: Stack
	keeper.registerTest(new tests::StackTestOverall());

	// TODO 05: Queue
	//keeper.registerTest(new tests::QueueTestOverall());

	// TODO 06: PriorityQueue
	//keeper.registerTest(new tests::PriorityQueueTestOverall());

	// TODO 07: Tree
	//keeper.registerTest(new tests::TreeTestOverall());

	// TODO 08: Table
	//keeper.registerTest(new tests::TableTestOverall());

    // TODO Zadanie na doma 01
    //keeper.registerTest(new tests::MatrixTestOverall());

	bool run = true;
	do
	{
		keeper.printTestMenu();
		std::vector<int> choice = keeper.readTestChoice();
		keeper.markTests(choice);
		keeper.resetTests();
		keeper.runTests();
		keeper.showTestResults();
		keeper.showLog();
		keeper.clearLog();
		run = keeper.readShouldContinue();
	}
	while (run);
}