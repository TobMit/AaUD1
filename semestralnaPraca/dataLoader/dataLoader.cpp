#include "dataLoader.h"

bool DataLoader::nextLine() {
    if (!getline(*citac,nacitane)){
        return false;
    }
    return true;
}

string DataLoader::getNextParameter() {
    pos = nacitane.find(delimiter);
    string retrunValue = nacitane.substr(0, pos);
    int rPos = retrunValue.find("\r");
    if (rPos != 0) {
        retrunValue = retrunValue.substr(0, rPos);
    }
    nacitane.erase(0, retrunValue.size() + delimiter.length());
    return  retrunValue;

}

void DataLoader::openNew(string address) {
    this->closeLoader();
    delete citac;
    citac = nullptr;
    citac = new fstream;
    this->citac->open(address);
}

bool DataLoader::hasNextParameter() {
    return !nacitane.empty();
}
