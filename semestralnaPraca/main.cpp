//
// Created by Tobias on 30/04/2022.
//

//todo sort(nejaka tabulka<K,T>, bool vzostp, kriteria<T,R>)
// volá sa to evaluator, to jest že sort používa krtiéria
//todo do tabuľky sa dá dostať aj cez getItemAtIndex
// poto sa to dá cez kritería getovať vlastnosti a tie porovnávať
// T data = tabs.getItemAtIndex(i)->accessData
// R vlastnostI = krti.evaluate(data)
// if(zostupne) {
//  vlastnostI < vlastnostJ
// }

//todo filter preberie ktritérium a sptía sa či to funguje, rozširuje sa to iba potomkami
// vytvoriť metódy na kritéria a návratova hodnota by bola to kritérim a poto ho viem využiť na viacerých miestach
// vytvoriť kritérium pre názov , opýtať sa aký nazov chce a potom to vyhodnocuje
#include "aplikacia.h"

int main()
{
    Aplikacia *aplikacia = new Aplikacia();


    delete aplikacia;
    aplikacia = nullptr;
    return 0;
}