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

    wstring &getCode() override;

    wstring &getOfficialTitle() override;

    void setCode(const wstring &pCode) override;

    void setOfficialTitle(const wstring &offTitleName) override;

    void setNextParameter(const wstring &parameter) override;

    int getSize() override;

};


OstatneUdaje::OstatneUdaje(const wstring &code, const wstring &offTitle) :
        code(code),
        offTitle(offTitle)
{
}


wstring &OstatneUdaje::getCode() {
    return code;
}


wstring &OstatneUdaje::getOfficialTitle() {
    return offTitle;
}


void OstatneUdaje::setCode(const wstring &pCode) {
    code = pCode;
}


void OstatneUdaje::setOfficialTitle(const wstring &offTitleName) {
    offTitle = offTitleName;
}


void OstatneUdaje::setNextParameter(const wstring &parameter) {
    this->data_->add(parameter);
}


int OstatneUdaje::getSize() {
    return this->data_->size();
}

