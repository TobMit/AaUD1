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
    OstatneUdaje(const wstring pCode, const wstring pOffTitle);

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
inline OstatneUdaje::~OstatneUdaje() {
    data->clear();
    delete data;
    data = nullptr;
}

inline OstatneUdaje::OstatneUdaje(const wstring pCode, const wstring pOffTitle) :
        code(pCode),
        offTitle(pOffTitle)
{
}


inline wstring OstatneUdaje::getCode() {
    return code;
}


inline wstring OstatneUdaje::getOfficialTitle() {
    return offTitle;
}


inline void OstatneUdaje::setCode(const wstring pCode) {
    code = pCode;
}


inline void OstatneUdaje::setOfficialTitle(const wstring pOffTitleName) {
    offTitle = pOffTitleName;
}


inline void OstatneUdaje::setNextParameter(const wstring parameter) {
    data->add(stoi(parameter));
}


inline int OstatneUdaje::getSize() {
    return data->size();
}


inline wstring &OstatneUdaje::at(int index) {
    wstring returnValue = L"-1";
    return returnValue;
}

inline int &OstatneUdaje::intAt(int index) {
    return data->at(index);
}

