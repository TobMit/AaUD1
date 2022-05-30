#pragma once
#include <fstream>
#include "iostream"
#include "string"

using namespace std;

class DataLoader {
private:
    fstream *citac;
    string delimiter = ";";
    string nacitane;
    size_t pos = 0;

public:
    DataLoader(string address) :
        citac(new fstream())
    {
        citac->open(address);
    };
    DataLoader() {

    };

    void openNew(string address);

    bool isOpen() {
        return citac->is_open();
    };

    void closeLoader(){
        citac->close();
    };

    string getNextParameter();
    bool nextLine();

    ~DataLoader(){
        closeLoader();
        delete citac;
    };

    bool hasNextParameter();
};

