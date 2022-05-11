#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../structures/queue/explicit_queue.h"

namespace structures
{
	/// <summary> Triedenie Merge sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class MergeSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Merge sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
    private:
        void spoj(int n, ExplicitQueue<TableItem<K,T>*> frontSpoj, ExplicitQueue<TableItem<K,T>*> rozdel1, ExplicitQueue<TableItem<K,T>*> rozdel2);
        void rozdel(int n, ExplicitQueue<TableItem<K,T>*> frontSpoj, ExplicitQueue<TableItem<K,T>*> rozdel1, ExplicitQueue<TableItem<K,T>*> rozdel2);
    };

	template<typename K, typename T>
	inline void MergeSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
        ExplicitQueue<TableItem<K,T>*> *frontRozdel1 = new ExplicitQueue<TableItem<K,T>*>;
        ExplicitQueue<TableItem<K,T>*> *frontRozdel2 = new ExplicitQueue<TableItem<K,T>*>;
        ExplicitQueue<TableItem<K,T>*> *frontSpoj = new ExplicitQueue<TableItem<K,T>*>;

        for (auto item: *table) {
            frontSpoj->push(item);
        }

        int i = 1;
        for (; i < table.size(); i *= 2) {
            rozdel(i, frontSpoj, frontRozdel1, frontRozdel2);
            spoj(i, frontSpoj, frontRozdel1, frontRozdel2);
        }
        rozdel(i, frontSpoj, frontRozdel1, frontRozdel2);
        spoj(i, frontSpoj, frontRozdel1, frontRozdel2);
        table.clear();
        while (!frontSpoj->isEmpty()) {
            auto par = frontSpoj->pop();
            table.insert(par->getKey(), par->accessData());
        }

        delete frontSpoj;
        delete frontRozdel1;
        delete frontRozdel2;

	}


    template<typename K, typename T>
    void MergeSort<K, T>::rozdel(int n, ExplicitQueue<TableItem<K,T>*> frontSpoj, ExplicitQueue<TableItem<K,T>*> rozdel1, ExplicitQueue<TableItem<K,T>*> rozdel2){
        int pocet = 0;
        bool prvy = true;
        while (!frontSpoj.isEmpty()) {
            if (frontSpoj.size() % n == 0) {
                pocet = 0;
                prvy = !prvy;
            }
            if (prvy){
                rozdel1.push(frontSpoj.pop());
            } else {
                rozdel2.push(frontSpoj.pop());
            }
            pocet++;
        }
    }

    template<typename K, typename T>
    void MergeSort<K, T>::spoj(int n, ExplicitQueue<TableItem<K,T>*> frontSpoj, ExplicitQueue<TableItem<K,T>*> rozdel1, ExplicitQueue<TableItem<K,T>*> rozdel2) {
        int prvych = 0;
        int druhych = 0;
        do {
            if (prvych == 0 && druhych == 0) {
                prvych = std::min(n, rozdel1.size());
                druhych = std::min(n, rozdel2.size());
            }
            int kluc1 = prvych > 0 ? rozdel1.peek()->getKey() : nullptr;
            int kluc2 = prvych > 0 ? rozdel2.peek()->getKey() : nullptr;

            if (kluc1 != nullptr && kluc2 = nullptr) {
                if (kluc1 < kluc2) {
                    prvych--;
                    frontSpoj.push(rozdel1.pop());
                } else{
                    druhych--;
                    frontSpoj.push(rozdel2.pop());
                }
            } else {
                if (kluc1 != nullptr) {
                    prvych--;
                    frontSpoj.push(rozdel1.pop());
                } else {
                    druhych--;
                    frontSpoj.push(rozdel2.pop());
                }
            }

        } while (!rozdel1.isEmpty() || !rozdel2.isEmpty());
    }
}