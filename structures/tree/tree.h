#pragma once

#include "../structure.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include <queue>

namespace structures
{
	/// <summary> Vrchol stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class TreeNode : public DataItem<T>
	{
	public:
		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		virtual TreeNode<T>* shallowCopy() = 0;

		/// <summary> Vytvori a vrati hlboku kopiu vrchola (teda skopiruje data a skopiruje celu stromovu strukturu). </summary>
		/// <returns> Hlboka kopia vrchola. </returns>
		virtual TreeNode<T>* deepCopy();

		/// <summary> Test, ci je koren. </summary>
		/// <returns> true, ak je koren, false inak. </returns>
		bool isRoot();

		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		virtual bool isLeaf() = 0;

		/// <summary> Spristupni rodica vrcholu. </summary>
		/// <returns> Rodic vrcholu. </returns>
		TreeNode<T>* getParent();

		/// <summary> Nastavi rodica na nullptr. </summary>
		void resetParent();

		/// <summary> Zmeni rodica vrcholu. </summary>
		/// <param name = "parent"> Novy rodic vrcholu. </param>
		void setParent(TreeNode<T>* parent);

		/// <summary> Spristupni brata vrcholu podla jeho pozicie u spolocneho rodica. </summary>
		/// <param name = "brothersOrder"> Poradie brata u rodica. </param>
		/// <exception cref=""> Vyhodena, ak je korenom. </exception>
		/// <returns> Brat vrcholu. </returns>
		virtual TreeNode<T>* getBrother(int brothersOrder);

		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		virtual TreeNode<T>* getSon(int order) = 0;

		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks>
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov.
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene.
		/// </remarks>
		virtual void insertSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		virtual TreeNode<T>* replaceSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks>
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov.
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene.
		/// </remarks>
		virtual TreeNode<T>* removeSon(int order) = 0;

		/// <summary> Vrati stupen vrcholu. </summary>
		/// <returns> Stupen vrcholu. </returns>
		virtual int degree() = 0;

		/// <summary> Vrati pocet vrcholov v podstrome. </summary>
		/// <returns> Pocet vrcholov v podstrome. </returns>
		virtual size_t sizeOfSubtree();

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		TreeNode(const T& data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol stromu, z ktoreho sa prevezmu vlastnosti. </param>
		TreeNode(TreeNode<T>& other);

		/// <summary> Odkaz na rodica. </summary>
		TreeNode<T>* parent_;
	};

	/// <summary> Strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T>
	class Tree : public Structure, public Iterable<T>
	{
	public:
		/// <summary> Konstruktor, inicializuje prazdny strom. </summary>
		Tree();

		/// <summary> Kopirovaci konstruktor. </summary>
		Tree(Tree<T>& other);

		/// <summary> Destruktor. </summary>
		~Tree();

		/// <summary> Zisti, ci je struktura prazdna. </summary>
		/// <returns> true, ak je struktura prazdna, false inak. </returns>
		bool isEmpty() override;

		/// <summary> Vrati pocet vrcholov v strome. </summary>
		/// <returns> Pocet vrcholov v strome. </returns>
		size_t size() override;

		/// <summary> Vymaze strom. </summary>
		virtual void clear();

		/// <summary> Spristupni koren stromu. </summary>
		/// <returns> Koren stromu. </returns>
		TreeNode<T>* getRoot();

		/// <summary> Nahradi koren stromu. </summary>
		/// <param name = "newRoot">  Novy koren stromu. </param>
		/// <returns> Povodny koren stromu. </returns>
		virtual TreeNode<T>* replaceRoot(TreeNode<T>* newRoot);

		/// <summary> Vytvori a vrati instanciu vrcholu stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu stromu. </returns>
		/// <remarks>
		/// Kazdy strom spravuje vrcholy ineho typu, mali by vsak byt jednotne v celom strome.
		/// Tato tovarenska metoda by mala byt pretazena v kazdom potomkovi stromu tak, aby vracala vrcholy, ktore ten strom ocakava.
		/// Instance vrcholov by mali byt vytvarane vyhradne pomocou tejto metody.
		/// </remarks>
		virtual TreeNode<T>* createTreeNodeInstance() = 0;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() override;

	protected:
		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assignTree(Tree<T>& other);

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equalsTree(Tree<T>* other);

	private:
		/// <summary> Koren stromu. </summary>
		TreeNode<T>* root_;

	protected:
		/// <summary> Iterator pre Tree. </summary>
		class TreeIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			TreeIterator();

			/// <summary> Destruktor. </summary>
			~TreeIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator=(Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;

		protected:
			/// <summary> Prehliadka stromu. </summary>
			std::queue<TreeNode<T>*>* path_;
		};

	public:
		class PreOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PreOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi preorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};

		class PostOrderTreeIterator: public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PostOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi postorder. </summary>
			/// <param name = "path"> Cesta stromom, ktoru zostavuje. </param>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};

		class LevelOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			LevelOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi levelorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};
	};

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::deepCopy()
	{
        // Factory metod"
        // TreeNote<T>* result = shallowCopy()
        // int pocet spracovanych vrcholov = 0
        // for(i = 0; pocet spracovanych vrcholov < degree(); i ++)
        //      syn = getSon(i)
        //      if (syn != nullptr)
        //          result -> replaceSon(syn->deepCopy(), i)
        //          pocet spracovanych synov++
        // return result;

        //Kopiu stromu vytváram ako shallow copy, mám jeden objek ktorý ukazuje na synov to je na začiato (shallowCopy)
        //Druhom kroku sa replace jeden smerník tou kópiou z rekurzie ktorí nam vráti syn->deepCopy() - 253 riadok
        //takto to prechádza pre každý prvok. vytvorí sa nová kopia "otec" ktorý ukazuje na synov smerníkmi ... a takto
        // to ide dokiaľ sa nedostaneme niekde na spodok kde už nie sú žiadny synovia potom sa to postupne returnuje
        // je to lepšie si nakresliť

        auto result = shallowCopy();
        int nuberOfProcessedSons = 0; // pocet spracovanych vrcholov
        for (int i = 0; nuberOfProcessedSons < degree(); ++i) {
            auto son = getSon(i);
            if (son != nullptr) {
                result->replaceSon(son->deepCopy(), i);
                nuberOfProcessedSons++;
            }
        }
        return result;
	}

	template<typename T>
	inline bool TreeNode<T>::isRoot()
	{
		// keď nemá parenta
        return parent_ == nullptr;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getParent()
	{
		return parent_;
	}

	template<typename T>
	inline void TreeNode<T>::resetParent()
	{
		parent_ = nullptr;
	}

	template<typename T>
	inline void TreeNode<T>::setParent(TreeNode<T>* parent)
	{
		parent_ = parent;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getBrother(int brothersOrder)
	{
        if(parent_ == nullptr) {
            throw std::logic_error("Root has no brother! Except from TreeNode<T>::getBrother()");
        } else {
            return parent_->getSon(brothersOrder);
        }
	}

	template<typename T>
	inline size_t TreeNode<T>::sizeOfSubtree()
	{
        // int result =1
        // int pocet spracovanych vrcholov = 0
        // for(i = 0; pocet spracovanych vrcholov < degree(); i ++)
        //      syn = getSon(i)
        //      if (syn != nullptr)
        //          result = syn -> sizeOfSubtree();
        //          pocet spracovanych synov++
        // return result;

        int result = 1;
        int nuberOfProcessedSons = 0; // pocet spracovanych vrcholov
        for (int i = 0; nuberOfProcessedSons < degree(); ++i) {
            auto son = getSon(i);
            if (son != nullptr) {
                result += son->sizeOfSubtree();
                nuberOfProcessedSons++;
            }
        }
        return result;
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(const T& data):
		DataItem<T>(data),
		parent_(nullptr)
	{
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(TreeNode<T>& other):
		DataItem<T>(other),
		parent_(other.parent_)
	{
	}

	template<typename T>
	inline Tree<T>::~Tree()
	{
        // Stačí zavolať deštruktor roota, a root sa postará o deštruktovanie potomka potomok svojich potomkov atď

        // zavolať cleer

        clear();
	}

	template<typename T>
	inline bool Tree<T>::isEmpty()
	{
		return root_ == nullptr ? 0 : root_->sizeOfSubtree();

	}

	template<typename T>
	inline size_t Tree<T>::size()
	{
		// strom si nedrzí size_ keďže môžeme naraz viac prvkov
        // nejaké osetrenie lebo a zavoláme sizeOf subtree

        return root_->sizeOfSubtree();
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getBeginIterator()
	{
		return new PreOrderTreeIterator(root_);
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getEndIterator()
	{
		return new PreOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline Structure& Tree<T>::assignTree(Tree<T>& other)
	{
        // potom vyrieši pretypovanie a keď sú pretipované správne tak sa potom pokračuje tu
        // todo checknút ci to mam spravne
        if (this != &other) {
            clear();
            // mám zaručené že sa mi praví kópia do rootu vyuýžívanie rekurzie
            if (other.root_ != nullptr){
                root_ = other.root_->deepCopy();
            }
        }
        return *this;
	}

	template<typename T>
	inline bool Tree<T>::equalsTree(Tree<T>* other)
	{
        // potom vyrieši pretypovanie a keď sú pretipované správne tak sa potom pokračuje tu

        if (other == nullptr) {
            return false;
        }
        if (this == other) {
            return true;
        }

        auto iteratorThis = Iterable<T>::begin();
        auto iteratorEnd = Iterable<T>::end();
        auto iteratorOteher = other->begin();
        auto iteratorOterEnd = other->end();

        while (iteratorEnd != iteratorEnd) {
            if (*iteratorEnd != *iteratorEnd) {
                return false;
            }
            ++iteratorThis;
            ++iteratorOteher;
        }
        return !(iteratorOteher != iteratorOterEnd);
        //return true;
	}

	template<typename T>
	inline Tree<T>::Tree():
		Structure(),
		Iterable<T>(),
		root_(nullptr)
	{
	}

	template<typename T>
	inline Tree<T>::Tree(Tree<T>& other):
		Tree<T>()
	{
		assignTree(other);
	}

	template<typename T>
	inline void Tree<T>::clear()
	{
        // nastaviť na nullptr - ostal by nam tam pointer na nejaký bordel a program by mohol spadnúť
		delete root_;
        root_ = nullptr;
	}

	template<typename T>
	inline TreeNode<T>* Tree<T>::getRoot()
	{
		return root_;
	}

	template<typename T>
	inline TreeNode<T>* Tree<T>::replaceRoot(TreeNode<T>* newRoot)
	{
		auto result = root_;
        root_ = newRoot;
        return result;
	}

	template<typename T>
	inline Tree<T>::TreeIterator::TreeIterator():
		Iterator<T>(),
		path_(new std::queue<TreeNode<T>*>()) //jedený príklad kedy môžemer používať inú knižnicu ako to čo sme programovali
	{
	}

	template<typename T>
	inline Tree<T>::TreeIterator::~TreeIterator()
	{
		delete path_;
        path_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator=(Iterator<T>& other)
	{
        *path_ = *dynamic_cast<TreeIterator&>(other).path_;
        return *this;
	}

	template<typename T>
	inline bool Tree<T>::TreeIterator::operator!=(Iterator<T>& other)
	{
        return *path_ != *dynamic_cast<TreeIterator&>(other).path_;
	}

	template<typename T>
	inline T Tree<T>::TreeIterator::operator*()
	{
        return path_->front()->accessData();
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator++()
	{
		path_->pop();
        return *this;
	}

	template<typename T>
	inline Tree<T>::PreOrderTreeIterator::PreOrderTreeIterator(TreeNode<T>* startNode):
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PreOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
        if (current != nullptr) {
            TreeIterator::path_->push(current);

            int nuberOfProcessedSons = 0; // pocet spracovanych vrcholov
            for (int i = 0; nuberOfProcessedSons < current->degree(); ++i) {
                auto son = current->getSon(i);
                if (son != nullptr) {
                    populatePath(son);
                    nuberOfProcessedSons++;
                }
            }
        }
	}

	template<typename T>
	inline Tree<T>::PostOrderTreeIterator::PostOrderTreeIterator(TreeNode<T>* startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PostOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
        //todo skontrolovat ci to mam správane
        if (current != nullptr) {

            int nuberOfProcessedSons = 0; // pocet spracovanych vrcholov
            for (int i = 0; nuberOfProcessedSons < current->degree(); ++i) {
                auto son = current->getSon(i);
                if (son != nullptr) {
                    populatePath(son);
                    nuberOfProcessedSons++;
                }
            }
            TreeIterator::path_->push(current);
        }
	}

	template<typename T>
	inline Tree<T>::LevelOrderTreeIterator::LevelOrderTreeIterator(TreeNode<T>* startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::LevelOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		//TODO 07: Tree<T>::LevelOrderTreeIterator
		throw std::runtime_error("Tree<T>::LevelOrderTreeIterator::populatePath: Not implemented yet.");
	}

}

