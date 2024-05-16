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
    Name(){}
    Name(const String& nickname) : nickname(String(nickname)) {}

    Name(const String& firstname, const String& lastname) : firstname(String(firstname)), lastname(String(lastname)) {}

    Name(const String& firstname, const String& lastname, const String& nickname) : firstname(String(firstname)), lastname(String(lastname)),
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
    Contact(const Name& name, const String& address, const ContactType& type) : name(name), address(address), type(type) {}

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
    PersonalContact(const Name& name, const String& address, const String& personalNumber)
            : Contact(name, address, ContactType::Personal), personalNumber(personalNumber) {}

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
    WorkContact(const Name& name, const String& address, const String& workNumber, const String& email)
            : Contact(name, address, ContactType::Work), workNumber(workNumber), email(email) {}


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
    GenTomb<Contact*> getContacts(){return contacts;}

    PhoneBook searchForName(const String nev)const {
        PhoneBook temp;
        for (size_t i = 0; i < contacts.getSize(); ++i) {
            if (strstr(contacts[i]->getName().c_str(), nev.c_str()) != nullptr) {
                temp.addContact(contacts[i]);
            }
        }
        return temp;
    }


    PhoneBook searchForPhoneNumber(const String& telefonszam)const {
        PhoneBook temp;
        for (size_t i = 0; i < contacts.getSize(); ++i) {
            if (strstr(contacts[i]->getNumber().c_str(), telefonszam.c_str()) != nullptr) {
                temp.addContact(contacts[i]);
            }
        }
        return temp;
    }

    PhoneBook searchForAddress(const String& address)const{
        PhoneBook temp;
        for (size_t i = 0; i < contacts.getSize(); ++i) {
            if (strstr(contacts[i]->getAddress().c_str(), address.c_str()) != nullptr) {
                temp.addContact(contacts[i]);
            }
        }
        return temp;
    }

    void addContact(Contact *contact) {
        contacts.add(contact);
    }

    void deleteContact(const String &param) {
        PhoneBook foundContacts = searchForName(param);
        PhoneBook temp = searchForPhoneNumber(param);

        for (size_t i = 0; i < temp.getSize(); ++i)
            foundContacts.addContact(temp.contacts[i]);

        for (size_t i = 0; i < foundContacts.contacts.getSize(); ++i)
            contacts.remove(foundContacts.contacts[i]);

    }

    void readFromFile(std::fstream& file) {
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for reading");
        }

        char buffer[256];

        while (file.getline(buffer, sizeof(buffer))) {
            int typeInt = std::atoi(buffer);
            ContactType type = static_cast<ContactType>(typeInt);

            file.getline(buffer, sizeof(buffer));
            String firstname(buffer);

            file.getline(buffer, sizeof(buffer));
            String lastname(buffer);

            file.getline(buffer, sizeof(buffer));
            String nickname(buffer);

            file.getline(buffer, sizeof(buffer));
            String address(buffer);

            file.getline(buffer, sizeof(buffer));
            String number(buffer);

            if (type == ContactType::Personal) {
                contacts.add(new PersonalContact(Name(firstname, lastname, nickname), address, number));
            } else if (type == ContactType::Work) {
                file.getline(buffer, sizeof(buffer));
                String email(buffer);
                contacts.add(new WorkContact(Name(firstname, lastname, nickname), address, number, email));
            }
            file.getline(buffer, sizeof(buffer));
        }
    }


    void saveToFile(std::fstream& file) const {
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        const Contact* contact = contacts[i];
        file << contact->getType() << std::endl;
        file << contact->getFirstname() << std::endl;
        file << contact->getLastname() << std::endl;
        file << contact->getNickname() << std::endl;
        file << contact->getAddress() << std::endl;

        if (contact->getType() == ContactType::Personal) {
            file << contact->getNumber() << std::endl;
        } else {
            file << contact->getNumber() << std::endl;
            file << contact->getEmail() << std::endl;
        }
        file << std::endl;
    }
}

    int getSize() const{ return contacts.getSize(); }
};

