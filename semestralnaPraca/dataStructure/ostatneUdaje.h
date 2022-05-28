//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include "storedData.h"


class OstatneUdaje : public StoredData {
private:
    wstring code;
    wstring offTitle;
public:
    OstatneUdaje();

    OstatneUdaje(const wstring pCode, const wstring pOffTitle);

    wstring getCode() const override;

    wstring getOfficialTitle() const override;

    void setCode(const wstring pCode) override;

    void setOfficialTitle(const wstring pOffTitleName) override;

    void setNextParameter(const wstring parameter) override;

    /// Služí na nastovovanie Int prametrov, podobne ako pre setNextParameter.
    /// \param parameter - parameter ktory sa ma uložiť do ArrListu
    void setNextIntParameter(const int parameter);

    int getSize() override;

    ~OstatneUdaje() override;

    wstring &at(int index) override;

    /// Podobne ako pri At sprístupňuje dáta s int hodnotou
    /// \param index ktorý chceme sprístupniť
    /// \return int hodnotu príslušného indexu
    int intAt(int index) const;

    UJTyp getUJTyp() const override;

    bool belongsTo(StoredData &VUJednotka) const override;

    bool belongsMe(StoredData *NUJednotka) const override;

    void setVzdelavanie(StoredData *pVzdelanie) override;

    StoredData *getVzdelavanie() const override;

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


inline wstring OstatneUdaje::getCode() const {
    return code;
}


inline wstring OstatneUdaje::getOfficialTitle() const {
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

inline void OstatneUdaje::setNextIntParameter(const int parameter) {
    data->add(parameter);
}

inline int OstatneUdaje::getSize() {
    return data->size();
}


inline wstring &OstatneUdaje::at(int index) {
    wstring returnValue = L"-1";
    return returnValue;
}

inline int OstatneUdaje::intAt(int index) const{
    return data->at(index);
}

inline bool OstatneUdaje::belongsMe(StoredData *NUJednotka) const {
    return false;
}

inline UJTyp OstatneUdaje::getUJTyp() const {
    return UJTyp::Neoznacene;
}

inline bool OstatneUdaje::belongsTo(StoredData &VUJednotka) const {
    return false;
}

inline void OstatneUdaje::setVzdelavanie(StoredData *pVzdelanie) {
}

inline StoredData *OstatneUdaje::getVzdelavanie() const {
    return nullptr;
}
