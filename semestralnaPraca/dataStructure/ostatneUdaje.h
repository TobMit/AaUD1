#pragma once
#include "storedData.h"


class OstatneUdaje : public StoredData {
private:
    string code;
    string offTitle;
    int pocetOsob = 0;
public:
    OstatneUdaje();

    OstatneUdaje(const string pCode, const string pOffTitle);

    string getCode() const override;

    string getOfficialTitle() const override;

    void setCode(const string pCode) override;

    void setOfficialTitle(const string pOffTitleName) override;

    void setNextParameter(const string parameter) override;

    /// Služí na nastovovanie Int prametrov, podobne ako pre setNextParameter.
    /// \param parameter - parameter ktory sa ma uložiť do ArrListu
    void setNextIntParameter(const int parameter);

    int getSize() override;

    ~OstatneUdaje() override;

    string &at(int index) override;

    /// Podobne ako pri At sprístupňuje dáta s int hodnotou
    /// \param index ktorý chceme sprístupniť
    /// \return int hodnotu príslušného indexu
    int intAt(int index) const;

    UJTyp getUJTyp() const override;

    bool belongsTo(StoredData &VUJednotka) const override;

    bool belongsMe(StoredData *NUJednotka) const override;

    void setVzdelavanie(StoredData *pVzdelanie) override;

    StoredData *getVzdelavanie() const override;

    int getPocOsob() {
        return pocetOsob;
    }

private:
    structures::ArrayList<int> *data = new structures::ArrayList<int>;

};
inline OstatneUdaje::~OstatneUdaje() {
    data->clear();
    delete data;
    data = nullptr;
}

inline OstatneUdaje::OstatneUdaje(const string pCode, const string pOffTitle) :
        code(pCode),
        offTitle(pOffTitle)
{
}


inline string OstatneUdaje::getCode() const {
    return code;
}


inline string OstatneUdaje::getOfficialTitle() const {
    return offTitle;
}


inline void OstatneUdaje::setCode(const string pCode) {
    code = pCode;
}


inline void OstatneUdaje::setOfficialTitle(const string pOffTitleName) {
    offTitle = pOffTitleName;
}


inline void OstatneUdaje::setNextParameter(const string parameter) {
    data->add(stoi(parameter));
    pocetOsob += stoi(parameter);
}

inline void OstatneUdaje::setNextIntParameter(const int parameter) {
    data->add(parameter);
    pocetOsob += parameter;
}

inline int OstatneUdaje::getSize() {
    return data->size();
}


inline string &OstatneUdaje::at(int index) {
    string returnValue = "-1";
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
