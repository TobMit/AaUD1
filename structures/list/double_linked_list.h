#pragma once

#include "linked_list.h"

namespace structures
{
	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.

    template<typename T>
    class DoubleLinkedListItem : public LinkedListItem<T>
    {
    public:
        /// Konstruktor
        /// \param data Data, ktore uchovavam
        DoubleLinkedListItem(T data) :
            LinkedListItem<T>(data),
            previous_ (nullptr)
            {
            };

        /// Kopirovaci Konstruktor
        /// \param other Prvoj jednostranne zretazeneho zooznamu, z kotrého sa prevezmu vlastnosti...
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
            LinkedListItem<T>(other),
            previous_(other.previous_)
        {
        };

        /// Destruktor
        ~DoubleLinkedListItem(){
            previous_ = nullptr;

        };

        /// Geter predchadzajúceho prvku
        /// \return Predchadzajúci prvok zretazeneho zoznamu
        DoubleLinkedListItem<T>* getPrevious() {
            return previous_;
        };

        /// Setter predchadzajuceho prvku zretazeneho zoznamu
        /// \param previous Predchadzajuci prvok zretazeneho zoznamu
        void setPrevious(DoubleLinkedListItem<T>* previous) {
            previous_ = previous;
        };
    private:
        DoubleLinkedListItem<T>* previous_;
    };


    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public LinkedList<T>
	{
    public:

        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        //Riesi dedicnost
        //size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        //Rieši dedičnosť
        //Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        //Rieši dedičnost
        //bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        //Rieši dedičnost
        //T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        //Riesi dedicnost
        //bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    private:
        DoubleLinkedListItem<T>* getItemAtIndex(int index);
	};

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() :
            LinkedList<T>()
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other)
    {
        this->assign(other);
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();
    }

    //Riesi dedicnost
    /*
    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        throw std::runtime_error("DoubleLinkedList<T>::size: Not implemented yet.");
    }*/

    // Rieši dedičnosť
    /*
    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
    }*/

    //Rieši dedičnost
    /*
    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        throw std::runtime_error("DoubleLinkedList<T>::equals: Not implemented yet.");
    }*/

    //Rieši dedičnost
    /*
    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
        throw std::runtime_error("DoubleLinkedList<T>::at: Not implemented yet.");
    }*/

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        auto newLLI = new DoubleLinkedListItem<T>(data); // c++ si to automaticky detekuje, co je na lavo tak to prida to prava
        if (this->size_ == 0) {
            this->first_ = newLLI;
        }
        else {
            this->last_->setNext(newLLI);
        }
        DoubleLinkedListItem<T>* oldLLI = dynamic_cast<DoubleLinkedListItem<T>*>(this->last_);
        newLLI->setPrevious(oldLLI);
        this->last_ = newLLI;
        this->size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        if (index == this->size_) {
            add(data);
        }
        else {
            Utils::rangeCheckExcept(index, this->size_, "Invalid index! Except from DoubleLinkedList<T>::insert()");
            auto newLLI = new DoubleLinkedListItem<T>(data);
            if (index == 0) {
                DoubleLinkedListItem<T>* oldLLI = dynamic_cast<DoubleLinkedListItem<T>*>(this->first_); // stačí pridat predchadzajúci prvok iba do pôvodneho, kedže nový je na začiatu
                oldLLI->setPrevious(newLLI);
                newLLI->setNext(this->first_);
                this-> first_ = newLLI;
            }
            else {
                //todo skontrolovat ci na spravne miesto pridalo prvok
                auto pred = getItemAtIndex(index - 1);
                DoubleLinkedListItem<T>* po = dynamic_cast<DoubleLinkedListItem<T>*>(getItemAtIndex(index));
                po->setPrevious(newLLI);
                newLLI->setNext(pred->getNext());
                newLLI->setPrevious(pred);
                pred->setNext(newLLI);
            }

            this->size_++;
        }
    }

    //Rieši dedičnost
    /*
    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
        throw std::runtime_error("DoubleLinkedList<T>::tryRemove: Not implemented yet.");
    }*/

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        //todo skontrolovat ci maze správny (da sa to spravit tak že si chcdekcnem ze ceknem prvok ktorý mi vráti)
        Utils::rangeCheckExcept(index, this->size_, "Invalid index! Except form DoubleLinkedList<T>::removeAt()");
        DoubleLinkedListItem<T>* delItem;
        if (index == 0) {
            delItem = dynamic_cast<DoubleLinkedListItem<T>*>(this->first_);
            this->first_ = this->first_->getNext();
            DoubleLinkedListItem<T>* newFirst = dynamic_cast<DoubleLinkedListItem<T>*>(this->first_);
            newFirst->setPrevious(nullptr);
            //todo skontrolovat spravanie keď je prvok posledny a maze sa
            if (this->last_ == delItem) {
                this->last_ = nullptr;
            }
        }
        else {
            auto pred = dynamic_cast<DoubleLinkedListItem<T>*>(getItemAtIndex(index-1));
            delItem = dynamic_cast<DoubleLinkedListItem<T>*>(pred->getNext());
            pred->setNext(delItem->getNext());
            //todo skontrolovat spravanie pri posledom prvku
            if (this->last_ == delItem) {
                this->last_ = pred;
            } else {
                //ak to nieje prvok tak nech sa prvok po prvku ktorý sa zmazal upravi previous_
                DoubleLinkedListItem<T>* po = dynamic_cast<DoubleLinkedListItem<T>*>(pred->getNext());
                po->setPrevious(pred);
            }
        }

        T result = delItem->accessData();
        delete delItem;
        this->size_--;
        return result;
    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::getIndexOf: Not implemented yet.");
    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::clear: Not implemented yet.");
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::getBeginIterator: Not implemented yet.");
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        //TODO Zadanie 2: DoubleLinkedList
        throw std::runtime_error("DoubleLinkedList<T>::getEndIterator: Not implemented yet.");

    }

    template<typename T>
    // todo skontrolovat ci to dava správne
    DoubleLinkedListItem<T> *DoubleLinkedList<T>::getItemAtIndex(int index) {
        if (index == this->size_ - 1) {
            return dynamic_cast<DoubleLinkedListItem<T>*>(this->last_);
        }
        else {
            // pozriem z ktorej strany sa tam rýchlejšie dostanem
            if (index <= this->size_ / 2) {
                auto current = this->first_;
                for (int i = 0; i < index; i++) {
                    current = current->getNext();
                }
                return dynamic_cast<DoubleLinkedListItem<T>*>(current);
            } else {
                auto current = dynamic_cast<DoubleLinkedListItem<T>*>(this->last_);
                for (int i = 0; i > index; i--) {
                    current = current->getPrevious();
                }
                return dynamic_cast<DoubleLinkedListItem<T>*>(current);
            }

        }
    }
}