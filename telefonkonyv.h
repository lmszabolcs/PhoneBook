
//Végleges beadásnál természetesen szét lesz szedve több header és cpp fájlra illetve doxygennel kompatibilis kommentek lesznek.

#ifndef TELEFONKONYV_TELEFONKONYV_H
#define TELEFONKONYV_TELEFONKONYV_H

#include <iostream>
#include <iomanip>
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
    String address;
public:
    Contact(Name name, String address) : name(Name(name)), address(String(address)) {}

    String getName() const { return name.getName(); }

    String getAddress() const { return address; }

    virtual String getNumber() const = 0;
    virtual std::ostream& print(std::ostream& os) {
        os <<"\n"<< std::setw(20) << std::left << name.getName() << std::setw(20) << address << "\n";
        return os;
    }


};

class PersonalContact : public Contact {
    String personalNumber;
public:
    PersonalContact(Name name, String address, String personalNumber) : Contact(name, address),
                                                                        personalNumber(String(personalNumber)) {}
    std::ostream& print(std::ostream& os) {
        this->Contact::print(os);
        os << std::setw(20) << std::left << "Personal Number: " << personalNumber << "\n";
        return os;
    }
    String getNumber() const { return personalNumber; }
};

class WorkContact : public Contact {
    String workNumber;
    String email;
public:
    WorkContact(Name name, String address, String workNumber, String email) : Contact(name, address),
                                                                              workNumber(String(workNumber)),
                                                                              email(String(email)) {}

    String getNumber() const { return workNumber; }

    String getEmail() const { return email; }
    std::ostream& print(std::ostream& os) {
        this->Contact::print(os);
        os << std::setw(20) << std::left << "Work Number: " << workNumber << "\n";
        os << std::setw(20) << std::left << "Email: " << email << "\n";
        return os;
    }
};

class PhoneBook {
    GenTomb<Contact *> contacts;
public:
    void listAllContacts() {
        for (size_t i = 0; i < contacts.getSize(); ++i) {
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
            if (strstr(contacts[i]->getNumber().c_str(), telefonszam.c_str()) != nullptr) {
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

    void saveToFile(std::fstream) const {

    }

    int getSize() { return contacts.getSize(); }
};


#endif //TELEFONKONYV_TELEFONKONYV_H
