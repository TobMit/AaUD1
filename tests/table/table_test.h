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

    //------------------------------------ Uloha 2 ------------------------------------------------

    /// <summary>
    /// Testovanie pre úlohu 2
    /// </summary>
    class TableUloha2
            :public SimpleTest
    {
    public:
        TableUloha2();
        void test() override;
    private:
        // aby som nemusel dlho hladat kluce
        std::vector<int> usedKey;
        std::vector<int> nonUsedKey;
        void cyklus(char oznacenie, int podielInsert, int podielRemove, int podielTryFind, structures::Table<int, int> &pTable);
        int getPomer(int const OPAKOVANIA, int pomer);
        /// Najde nepouzity kluc a presunie ho medzi pouzite
        /// \return Kluc ktory sme este nepouzili.
        int insertKey();
        /// Najde pouzity kluc ktory sa moze pouzit na vymazanie v tabulke a vratiho medzi nepouzite.
        /// \return Kluc ktory sa nachadza v tabulke.
        int removeKey();
        /// Najde pouzity kluc.
        /// \return Vrati pouzity kluc
        int getUsedKey();
    protected:
        virtual structures::Table<int, int> * makeTable() const = 0;
        virtual void info() const = 0;
    };


    class SSTUloha2
            : public TableUloha2
    {
    protected:
        structures::Table<int, int> * makeTable() const override
        {
            return new structures::SortedSequenceTable<int, int>();
        };

        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie SST!");
        }
    };

    class BSTUloha2
            : public TableUloha2
    {
    protected:
        structures::Table<int, int> * makeTable() const override
        {
            return new structures::BinarySearchTree<int, int>();
        };
        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie BST!");
        }
    };

    //------------------------------------------- Uloha 3 -----------------------------------------------
    class TableUloha3
            :public SimpleTest
    {
    public:
        TableUloha3();
        void test() override;
    private:
        // aby som nemusel dlho hladat kluce
        std::vector<int> usedKey;
        std::vector<int> nonUsedKey;

        Microseconds cyklusInsert(int size, const int POC_OPAKOVANI, structures::Table<int, int> &pTable);
        Microseconds durationInsert(int key, int cislo, structures::Table<int, int> &pTable);

        Microseconds cyklusRemove(int size, const int POC_OPAKOVANI, structures::Table<int, int> &pTable);
        Microseconds durationRemove(int key, structures::Table<int, int> &pTable);

        Microseconds cyklusTryFind(int size, const int POC_OPAKOVANI, structures::Table<int, int> &pTable);
        Microseconds durationPeek(int key, int cislo, structures::Table<int, int> &pTable);

        /// rapairQue udrzuje velkost daného frontu na potrebnej dlzke. Keď treba, tak front zväčší a naplni hodnotami a ked je velky tak zmensi
        /// \param SIZE - velkost listu ktora sa ma udrziavat
        /// \param pTable - list kotry sa ma opravit
        void repairTable(const int SIZE, structures::Table<int, int> &pTable);

        /// Najde nepouzity kluc a presunie ho medzi pouzite
        /// \return Kluc ktory sme este nepouzili.
        int insertKey();
        /// Najde pouzity kluc ktory sa moze pouzit na vymazanie v tabulke a vratiho medzi nepouzite.
        /// \return Kluc ktory sa nachadza v tabulke.
        int removeKey();
        /// Najde pouzity kluc.
        /// \return Vrati pouzity kluc
        int getUsedKey();
    protected:
        virtual structures::Table<int, int> * makeTable() const = 0;

    };

    class SSTUloha3
            : public TableUloha3
    {
    protected:
        structures::Table<int, int> *makeTable() const override
        {
            return new structures::SortedSequenceTable<int, int>();
        }
    };

    class BSTUloha3
            : public TableUloha3
    {
    protected:
        structures::Table<int, int>* makeTable() const override
        {
            return new structures::BinarySearchTree<int, int>();
        }

    };

}