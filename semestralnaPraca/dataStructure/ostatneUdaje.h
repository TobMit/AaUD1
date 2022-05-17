//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include "storedData.h"


class OstatneUdaje : public StoredData{
private:
    wstring code;
    wstring offTitle;
public:
    OstatneUdaje() {
    };
    OstatneUdaje(const wstring &code, const wstring &offTitle);

    wstring getCode() override;

    wstring getOfficialTitle() override;

    void setCode(const wstring pCode) override;

    void setOfficialTitle(const wstring pOffTitleName) override;

    void setNextParameter(const wstring parameter) override;

    int getSize() override;

    ~OstatneUdaje() override;

    wstring &at(int index) override;

    int &intAt(int index);

private:
    structures::ArrayList<int> *data = new structures::ArrayList<int>;

};
OstatneUdaje::~OstatneUdaje() {
    data->clear();
    delete data;
    data = nullptr;
}

OstatneUdaje::OstatneUdaje(const wstring &code, const wstring &offTitle) :
        code(code),
        offTitle(offTitle)
{
}


wstring OstatneUdaje::getCode() {
    return code;
}


wstring OstatneUdaje::getOfficialTitle() {
    return offTitle;
}


void OstatneUdaje::setCode(const wstring pCode) {
    code = pCode;
}


void OstatneUdaje::setOfficialTitle(const wstring pOffTitleName) {
    offTitle = pOffTitleName;
}


void OstatneUdaje::setNextParameter(const wstring parameter) {
    data->add(stoi(parameter));
}


int OstatneUdaje::getSize() {
    return data->size();
}


wstring &OstatneUdaje::at(int index) {
    wstring returnValue = L"-1";
    return returnValue;
}

int &OstatneUdaje::intAt(int index) {
    return data->at(index);
}

