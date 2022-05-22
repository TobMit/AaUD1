//
// Created by Tobias on 30/04/2022.
//
#pragma once
#include <fstream>
#include "iostream"
#include "string"

using namespace std;

class DataLoader {
private:
    wfstream *citac;
    wstring delimiter = L";";
    wstring nacitane;
    size_t pos = 0;

public:
    DataLoader(string address) :
        citac(new wfstream())
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

    wstring getNextParameter();
    bool nextLine();

    ~DataLoader(){
        closeLoader();
        delete citac;
    };

    bool hasNextParameter();
};

