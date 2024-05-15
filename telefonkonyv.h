#define TELEFONKONYV_TELEFONKONYV_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
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
    String getFirstname()const{return firstname;}
    String getLastname()const{return lastname;}
    String getNickname()const{return nickname;}
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

enum ContactType {
    Personal,
    Work
};

class Contact {
    Name name;
    String address;
    ContactType type;

public:
    Contact(Name name, String address, ContactType type) : name(name), address(address), type(type) {}

    String getName() const { return name.getName(); }
    String getFirstname() const{return name.getFirstname();}
    String getLastname() const{return name.getLastname();}
    String getNickname() const {return name.getNickname();}
    String getAddress() const { return address; }
    ContactType getType() const { return type; }
    void setType(ContactType type){type = type;}
    virtual String getNumber() const = 0;
    virtual String getEmail() const { return ""; }

    virtual std::ostream &print(std::ostream &os) {
        os << "\n" << std::setw(20) << std::left << name.getName() << std::setw(20) << address << "\n";
        return os;
    }
};

class PersonalContact : public Contact {
    String personalNumber;
public:
    PersonalContact(Name name, String address, String personalNumber) : Contact(name, address, ContactType::Personal),
                                                                        personalNumber(String(personalNumber)) { setType(Personal);}

    std::ostream& print(std::ostream& os) override {
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
    WorkContact(Name name, String address, String workNumber, String email) : Contact(name, address, ContactType::Work),
                                                                              workNumber(String(workNumber)),
                                                                              email(String(email)) { setType(Work);}

    String getNumber() const { return workNumber; }

    String getEmail() const { return email; }
    std::ostream& print(std::ostream& os) override {
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
            // További kezelés, ha több kontaktot találtunk
            // ...
        }
    }


    void readFromFile(std::fstream& file) {

    }


    void saveToFile(std::fstream& file) const {
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        const Contact* contact = contacts[i];

        file << "FirstName:" << contact->getFirstname() << std::endl;
        file << "LastName:" << contact->getLastname() << std::endl;
        file << "NickName:" << contact->getNickname() << std::endl;
        file << "Address:" << contact->getAddress() << std::endl;

        if (contact->getType() == ContactType::Personal) {
            file << "PersonalNumber:" << contact->getNumber() << std::endl;
        } else {
            file << "WorkNumber:" << contact->getNumber() << std::endl;
            file << "Email:" << contact->getEmail() << std::endl;
        }
        file << std::endl;
    }
}

    int getSize() { return contacts.getSize(); }
};
