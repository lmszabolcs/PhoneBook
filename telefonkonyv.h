
//Végleges beadásnál természetesen szét lesz szedve több header és cpp fájlra illetve doxygennel kompatibilis kommentek lesznek.

#ifndef TELEFONKONYV_TELEFONKONYV_H
#define TELEFONKONYV_TELEFONKONYV_H

#include <iostream>
#include "string5.h"
#include "gentomb.h"
#include "gtest_lite.h"
#include "memtrace.h"

class Name {
    String firstname, lastname, nickname;
public:
    Name(String nickname) : nickname(String(nickname)) {}

    Name(String firstname, String lastname) : firstname(String(firstname)), lastname(String(lastname)) {}

    Name(String firstname, String lastname, String nickname) : firstname(String(firstname)), lastname(String(lastname)),
                                                               nickname(String(nickname)) {}

    String getName() const {
        if (firstname.size() > 0 && lastname.size() > 0) {
            if (nickname.size() > 0) {
                return firstname + " " + lastname + " (" + nickname + ")";
            } else {
                return firstname + " " + lastname;
            }
        } else
            return nickname;
    }
};

class Contact {
    Name name;
    String personalNumber;
    String workNumber;
    String address;
public:
    Contact(Name name, String personalNumber, String address) : name(Name(name)),
                                                                personalNumber(String(personalNumber)),
                                                                address(String(address)) {}

    Contact(Name name, String personalNumber, String workNumber, String address) : name(Name(name)), personalNumber(
            String(personalNumber)), workNumber(String(workNumber)), address(String(address)) {}

    String getName() const { return name.getName(); }

    String getPersonal() const { return personalNumber; }

    String getWork() const { return workNumber; }

    String getAddress() const { return address; }

    void print(std::ostream &os) const {
        std::cout
                << getName() + " "
                << personalNumber + " "
                << ((workNumber.size() > 0) ? workNumber + " " : "")
                << address + " " << std::endl;
    }
};

class PhoneBook {
    GenTomb<Contact *> contacts;
public:
    void listAllContacts() {
        for (size_t i = 0; i < contacts.getSize(); ++i) {
            std::cout << i + 1 << ". ";
            contacts[i]->print(std::cout);
        }
    }

    PhoneBook searchForName(const String &nev) {
        PhoneBook temp;
        for (size_t i = 0; i < contacts.getSize(); ++i) {
            if (strstr(contacts[i]->getName().c_str(), nev.c_str()) != nullptr) {
                temp.addContact(contacts[i]);
            }
        }
        return temp;
    }


    PhoneBook searchForPhoneNumber(String telefonszam) {
        PhoneBook temp;
        for (size_t i = 0; i < contacts.getSize(); ++i) {
            if (strstr(contacts[i]->getPersonal().c_str(), telefonszam.c_str()) != nullptr) {
                temp.addContact(contacts[i]);
            }
        }
        return temp;
    }

//hasonlo a masik kettohoz
    PhoneBook searchForAddress(String);

    void addContact(Contact *contact) {
        contacts.add(contact);
    }

//kezelni, ha tobb kontaktot is talal
    void deleteContact(String &param) {
        PhoneBook foundContacts = searchForName(param);
        PhoneBook temp = searchForPhoneNumber(param);
        for (size_t i = 0; i < temp.getSize(); ++i)
            foundContacts.addContact(temp.contacts[i]);
        if (foundContacts.getSize() == 1)
            contacts.remove(foundContacts.contacts[0]);
        else {

        }
    }

//formatum, opcionalis szam es nev valtozatok tarolasa?
    void readFromFile(std::fstream);

    void saveToFile(std::fstream) const;

    int getSize() { return contacts.getSize(); }
};


#endif //TELEFONKONYV_TELEFONKONYV_H
