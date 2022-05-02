#pragma once

#include "../test.h"
//#include "../../strductures/table/table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/binary_search_tree.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania tabulky avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class TableTestInterface
		: public SimpleTest
	{
	public:
		TableTestInterface();
		void test() override;

	protected:
		virtual structures::Table<int, int>* makeTable() = 0;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class BinarySearchTreeTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class HashTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class LinkedTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class SortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class TreapTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zavola vsetky metody danej tabulky.
	/// </summary>
	class UnsortedSequenceTableTestInterface
		: public TableTestInterface
	{
	protected:
		structures::Table<int, int>* makeTable() override;
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class BinarySearchTreeTestOverall
		: public ComplexTest
	{
	public:
		BinarySearchTreeTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class HashTableTestOverall
		: public ComplexTest
	{
	public:
		HashTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class LinkedTableTestOverall
		: public ComplexTest
	{
	public:
		LinkedTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class SortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		SortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class TreapTestOverall
		: public ComplexTest
	{
	public:
		TreapTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju danu tabulku.
	/// </summary>
	class UnsortedSequenceTableTestOverall
		: public ComplexTest
	{
	public:
		UnsortedSequenceTableTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju tabulku.
	/// </summary>
	class TableTestOverall
		: public ComplexTest
	{
	public:
		TableTestOverall();
	};
    //-------------------------------- TESTY FUNKCNOSTI --------------------------------------
    /// <summary>
    /// Test ktory skontroluje ci funguje add a insert v V oboch implementáciach Listu
    /// </summary>
    class TableFunctionsTest
            : public SimpleTest {
    public:
        TableFunctionsTest();
        void test() override;

    protected:
        virtual structures::Table<int, int> * makeTable() const = 0;
        virtual structures::Table<int, int> * makeTable(structures::Table<int, int> &other) const = 0;
    };

    class SSTFunctionTest
            :public TableFunctionsTest {
    protected:
        structures::Table<int, int> * makeTable() const override {
            return new structures::SortedSequenceTable<int, int>();
        };
        structures::Table<int, int> * makeTable(structures::Table<int, int> &other) const override {
            structures::SortedSequenceTable<int, int>& table = dynamic_cast<structures::SortedSequenceTable<int, int>&>(other);
            return new structures::SortedSequenceTable<int, int>(table);
        };
    };

    class BSTFunctionTest
            :public TableFunctionsTest {
    protected:
        structures::BinarySearchTree<int, int> * makeTable() const override {
            return new structures::BinarySearchTree<int, int>();
        };
        structures::Table<int, int> * makeTable(structures::Table<int, int> &other) const override {
            structures::BinarySearchTree<int, int>& tree = dynamic_cast<structures::BinarySearchTree<int, int>&>(other);
            return new structures::BinarySearchTree<int, int>(tree);
        };
    };

}