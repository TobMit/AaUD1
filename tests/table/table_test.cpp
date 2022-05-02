#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
        addTest(new BSTFunctionTest());
        addTest(new BSTUloha2());
	}

	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
        addTest(new SSTFunctionTest());
        addTest(new SSTUloha2());
	}

	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
	}

	TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		addTest(new HashTableTestOverall());
		addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		addTest(new TreapTestOverall());
		addTest(new UnsortedSequenceTableTestOverall());
	}

    // ---------------------------- Testy funkcnosti --------------------------------
    TableFunctionsTest::TableFunctionsTest() :
            SimpleTest("Complex test")
    {
    }
    void TableFunctionsTest::test()
    {
        /*
        structures::Table<int, int>* table = this->makeTable();
        for (int i = 1; i <= 10; ++i) {
            table->push(i, i);
        }

        /*for (int i = 1; i <= 100; ++i) {
            // vkladanie s nahodnou prioritov
            int cislo = rand()%1000;
            table->push(cislo, cislo);
        }*/
        /*
        SimpleTest::assertTrue(table->size() == 10, "Velkost PriorityQueue by mala byt 10 a je: " + std::to_string(table->size()));

        structures::Table<int, int>* copyTable = this->makeTable(*table);
        SimpleTest::assertTrue(copyTable->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::assertTrue(table->peek() == 1, "Hodnota peek by mala byt 1 a je " + std::to_string(table->peek()));
        SimpleTest::assertTrue(table->peekPriority() == 1, "Hodnota peekPriority by mala byt 1 a je " + std::to_string(table->peekPriority()));
        int hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 1, "Hodnota pop by mala byt 1 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 2, "Hodnota pop by mala byt 2 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 3, "Hodnota pop by mala byt 3 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 4, "Hodnota pop by mala byt 4 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 5, "Hodnota pop by mala byt 5 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 6, "Hodnota pop by mala byt 6 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 7, "Hodnota pop by mala byt 7 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 8, "Hodnota pop by mala byt 8 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 9, "Hodnota pop by mala byt 9 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 10, "Hodnota pop by mala byt 10 a je " + std::to_string(hodnota));

        structures::Table<int, int>* assignQueue = this->makeTable();
        assignQueue->assign(*copyTable);
        SimpleTest::assertTrue(assignQueue->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::logInfo(" \"Ocna\" kontrola copyTable assign. Cisla v riadkoch maju bit rovnake a ist od 1 do 10 ");
        for (int i = 1; i <= 10; ++i) {
            int peek = copyTable->peek();
            int peekPr = copyTable->peekPriority();
            SimpleTest::logInfo(std::to_string(peek) + " " + std::to_string(peekPr) + " " + std::to_string(copyTable->pop()));
            //na macos mi to zoborie aj takto ale vo visual to nefunguje správne
            //SimpleTest::logInfo(std::to_string(copyTable->peek()) + " " + std::to_string(copyTable->peekPriority()) + " " + std::to_string(copyTable->pop()));
        }

        SimpleTest::logPass("Complet");
        delete assignQueue;
        delete copyTable;
        delete table;*/
    }

    //--------------------------------------------------- Uloha 2 ------------------------------------------------------------
    TableUloha2::TableUloha2()
            : SimpleTest("Uloha2")
    {

    }
    void TableUloha2::test()
    {
        this->info();
        structures::Logger::getInstance().logInfo("Testovanie Uloha2!");
        // scenár A
        structures::Table<int, int>* table = this->makeTable();
        cyklus('A', 35, 35, 30, *table);
        delete table;

        // Scenár B
        table = this->makeTable();
        cyklus('B', 50, 30, 20, *table);
        delete table;

        // Scenár C
        table = this->makeTable();
        cyklus('C', 70, 25, 5, *table);
        delete table;

    }
    void TableUloha2::cyklus(char oznacenie, int podielInsert, int podielRemove, int podielTryFind,
                             structures::Table<int, int> &pTable)
    {
        static const int OPAKOVANIA = 100000;
        static const int MAX_DATA_VALUE_IN_QUEUE = 100;
        static const int MAX_PRIORITY = 100000;

        structures::Logger::getInstance().logInfo("Zacal sa Scenar " + std::string(1, oznacenie) + "!");
        structures::Logger::getInstance().logInfo("Celkovo Push, Celkovo Pop, Celkovo Peek, celkova dlzka Scenara!");

        int opPush = getPomer(OPAKOVANIA, podielInsert);
        int opPop = getPomer(OPAKOVANIA, podielRemove);
        int opPeek = getPomer(OPAKOVANIA, podielTryFind);

        std::vector<char>pool;
        for (unsigned i = 0; i < opPush; i++)
        {
            pool.push_back(1);
        }
        for (unsigned i = 0; i < opPop; i++)
        {
            pool.push_back(2);
        }
        for (unsigned i = 0; i < opPeek; i++)
        {
            pool.push_back(3);
        }


        Microseconds durationPush = std::chrono::microseconds(0);
        Microseconds durationPop = std::chrono::microseconds(0);
        Microseconds durationPeek = std::chrono::microseconds(0);

        while (!pool.empty())
        {
            int index = rand() % pool.size();
            int cislo;
            int priority;
            switch (pool.at(index))
            {
                case 1:
                    cislo = rand() % MAX_DATA_VALUE_IN_QUEUE;
                    priority = rand() % MAX_PRIORITY;
                    SimpleTest::startStopwatch();
                    pTable.push(priority, cislo);
                    SimpleTest::stopStopwatch();
                    durationPush += SimpleTest::getElapsedTime();

                    break;

                case 2:
                    if (!pTable.isEmpty()) {
                        SimpleTest::startStopwatch();
                        pTable.pop();
                        SimpleTest::stopStopwatch();
                        durationPop += SimpleTest::getElapsedTime();
                    }
                    break;

                case 3:
                    if (!pTable.isEmpty()) {
                        SimpleTest::startStopwatch();
                        pTable.peek();
                        SimpleTest::stopStopwatch();
                        durationPeek += SimpleTest::getElapsedTime();
                    }
                    break;

            }

            pool.erase(pool.begin() + index);
        }

        structures::Logger::getInstance().logDuration(0, durationPush + durationPop + durationPeek, std::to_string(durationPush.count() ) + "," + std::to_string(durationPop.count()) + "," + std::to_string(durationPeek.count()));
    }

    int TableUloha2::getPomer(int const OPAKOVANIA, int pomer)
    {
        return (pomer * OPAKOVANIA) / 100;
    }

}