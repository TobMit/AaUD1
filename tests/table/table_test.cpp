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

}