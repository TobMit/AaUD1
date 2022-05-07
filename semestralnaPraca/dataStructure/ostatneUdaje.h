//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include "storedData.h"


class OstatneUdaje : public StoredData{
private:
    string code;
    string offTitle;
public:
    OstatneUdaje() {
    };
    OstatneUdaje(const string &code, const string &offTitle);

    string &getCode() override;

    string &getOfficialTitle() override;

    void setCode(const string &pCode) override;

    void setOfficialTitle(const string &offTitleName) override;

    void setNextParameter(const string &parameter) override;

    int getSize() override;

};


OstatneUdaje::OstatneUdaje(const string &code, const string &offTitle) :
        code(code),
        offTitle(offTitle)
{
}


string &OstatneUdaje::getCode() {
    return code;
}


string &OstatneUdaje::getOfficialTitle() {
    return offTitle;
}


void OstatneUdaje::setCode(const string &pCode) {
    code = pCode;
}


void OstatneUdaje::setOfficialTitle(const string &offTitleName) {
    offTitle = offTitleName;
}


void OstatneUdaje::setNextParameter(const string &parameter) {
    this->data_->add(parameter);
}


int OstatneUdaje::getSize() {
    return this->data_->size();
}

