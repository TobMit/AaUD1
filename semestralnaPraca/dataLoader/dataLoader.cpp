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
    int rPos = retrunValue.find(L"\r");
    if (rPos != 0) {
        retrunValue = retrunValue.substr(0, rPos);
    }
    nacitane.erase(0, retrunValue.size() + delimiter.length());
    return  retrunValue;

}

void DataLoader::openNew(string address) {
    this->closeLoader();
    this->citac.open(address);
}

bool DataLoader::hasNextParameter() {
    return !nacitane.empty();
}
