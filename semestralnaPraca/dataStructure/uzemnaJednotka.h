//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"


class UzemnaJednotka : public StoredData {
public:
    UzemnaJednotka();

    UzemnaJednotka(UJTyp typ);

    UzemnaJednotka(const UJTyp typ, const string &pSortNumber, const string &pCode,
                   const string &pOfficialTitle, const string &pMediumTitle,
                   const string &pShortTitle, const string &pNote);

    string getCode() const override;

    string getOfficialTitle() const override;

    void setCode(const string pCode) override;

    void setOfficialTitle(const string pOffTitleName) override;

    void setNextParameter(const string parameter) override;

    int getSize() override;

    ~UzemnaJednotka() override;

    string &at(int index) override;

    UJTyp getUJTyp() const override;

    bool belongsTo(StoredData &VUJednotka) const override;

    bool belongsMe(StoredData *NUJednotka) const override;

    void setVzdelavanie(StoredData *pVzdelanie) override;

    StoredData *getVzdelavanie() const override;

private:
    int dataIndex = 0;
    string sortNumber;
    string code;
    string officialTitle;
    string mediumTitle;
    string shortTitle;
    string note;
    UJTyp typUJ;
    StoredData *vzdelavanie;

};


inline UzemnaJednotka::UzemnaJednotka()
{
}

inline UzemnaJednotka::UzemnaJednotka(UJTyp typ)  :
        typUJ(typ)
{
}

inline UzemnaJednotka::UzemnaJednotka(const UJTyp typ, const string &pSortNumber, const string &pCode,
                                      const string &pOfficialTitle, const string &pMediumTitle,
                                      const string &pShortTitle, const string &pNote) {
    sortNumber = pSortNumber;
    code = pCode;
    officialTitle = pOfficialTitle;
    mediumTitle = pMediumTitle;
    shortTitle = pShortTitle;
    note = pNote;
    typUJ = typ;
}

inline UzemnaJednotka::~UzemnaJednotka() {

}

inline string UzemnaJednotka::getCode() const {
    return code;
}


inline string UzemnaJednotka::getOfficialTitle() const {
    return officialTitle;
}


inline void UzemnaJednotka::setCode(const string pCode) {
    code = pCode;
}


inline void UzemnaJednotka::setOfficialTitle(const string pOffTitleName) {
    officialTitle = pOffTitleName;
}


inline void UzemnaJednotka::setNextParameter(const string parameter) {
    switch (dataIndex) {
        case 0:
            sortNumber = parameter;
            break;
        case 1:
            code = parameter;
            break;
        case 2:
            officialTitle = parameter;
            break;
        case 3:
            mediumTitle = parameter;
            break;
        case 4:
            shortTitle = parameter;
            break;
        case 5:
            note = parameter;
            break;
        default:
            return;

    }
    dataIndex++;
}


inline int UzemnaJednotka::getSize() {
    return 6;
}

inline string &UzemnaJednotka::at(int index) {
    switch (index) {
        case 0:
            return sortNumber;
            break;
        case 1:
            return code;
            break;
        case 2:
            return officialTitle;
            break;
        case 3:
            return mediumTitle;
            break;
        case 4:
            return shortTitle;
            break;
        case 5:
            return note;
            break;

    }
}

inline UJTyp UzemnaJednotka::getUJTyp() const {
    return typUJ;
}

inline bool UzemnaJednotka::belongsTo(StoredData &VUJednotka) const {
    string porovnavanie;
    if (typUJ == UJTyp::Kraj) {
        porovnavanie = note.substr(5, string::npos);
    } else {
        porovnavanie = code;
    }
    if (VUJednotka.getUJTyp() == UJTyp::Neoznacene) {
        return false;
    }
    if (VUJednotka.getUJTyp() == UJTyp::Obec) {
        return false;
    }
    if (VUJednotka.getUJTyp() == typUJ) {
        return false;
    }
    if (typUJ == UJTyp::Stat) {
        return false;
    }
    if (typUJ == UJTyp::Kraj && VUJednotka.getUJTyp() == UJTyp::Okres) {
        return false;
    }

    switch (VUJednotka.getUJTyp()) {
        case UJTyp::Stat:
            return VUJednotka.getCode().substr(0, 2).compare(porovnavanie.substr(0, 2)) == 0;

        case UJTyp::Kraj:
            return VUJednotka.at(5).substr(5, string::npos).compare(porovnavanie.substr(0, 5)) == 0;

        case UJTyp::Okres:
            return VUJednotka.getCode().substr(0, 6).compare(porovnavanie.substr(0, 6)) == 0;
    }

}

inline bool UzemnaJednotka::belongsMe(StoredData *NUJednotka) const {
    string porovnavanie;
    if (typUJ == UJTyp::Kraj) {
        porovnavanie = note.substr(5, string::npos);
    } else {
        porovnavanie = code;
    }
    if (NUJednotka->getUJTyp() == UJTyp::Stat) {
        return false;
    }
    // ak som ja štát tak všetko podo mňa patrí
    if (typUJ == UJTyp::Stat) {
        return true;
    }
    // ak sme rovnaký typ tak false
    if (typUJ == NUJednotka->getUJTyp()) {
        return false;
    }
    // ak som kraj tak spracuvavam iba okresi a obce inak false
    if (typUJ == UJTyp::Kraj) {
        switch (NUJednotka->getUJTyp()) {
            case UJTyp::Okres:
                return porovnavanie.compare(NUJednotka->getCode().substr(0,5));
            case UJTyp::Obec:
                return porovnavanie.compare(NUJednotka->getCode().substr(0,5));
            default:
                return false;
        }
    }
    if (typUJ == UJTyp::Okres) {
        switch (NUJednotka->getUJTyp()) {
            case UJTyp::Obec:
                return porovnavanie.compare(NUJednotka->getCode().substr(0,6));
            default:
                return false;
        }
    }
}

inline void UzemnaJednotka::setVzdelavanie(StoredData *pVzdelanie) {
    vzdelavanie = pVzdelanie;
}

inline StoredData *UzemnaJednotka::getVzdelavanie() const {
    return vzdelavanie;
}



