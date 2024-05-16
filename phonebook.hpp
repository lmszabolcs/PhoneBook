#include <iostream>
#include <fstream>
#include "contact.hpp"
#include "gentomb.h"

#ifndef PHONEBOOK_PHONEBOOK_HPP
#define PHONEBOOK_PHONEBOOK_HPP

class PhoneBook {
    GenTomb<Contact *> contacts;
public:
    GenTomb<Contact *> getContacts() { return contacts; }

    int getSize() const { return contacts.getSize(); }

    void addContact(Contact *contact) { contacts.add(contact); }

    void listAllContacts();

    PhoneBook searchForName(const String &nev) const;

    PhoneBook searchForPhoneNumber(const String &telefonszam) const;

    PhoneBook searchForAddress(const String &address) const;

    void deleteContact(const String &param);

    void readFromFile(std::fstream &file);

    void saveToFile(std::fstream &file) const;
};

#endif //PHONEBOOK_PHONEBOOK_HPP
