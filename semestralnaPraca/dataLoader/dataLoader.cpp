//
// Created by Tobias on 30/04/2022.
//
#include "dataLoader.h"

bool DataLoader::nextLine() {
    if (!getline(citac,nacitane)){
        return false;
    }
    return true;
}

wstring DataLoader::getNextParameter() {
    pos = nacitane.find(delimiter);
    wstring retrunValue = nacitane.substr(0, pos);
    nacitane.erase(0, retrunValue.size() + delimiter.length());
    return retrunValue;

}
