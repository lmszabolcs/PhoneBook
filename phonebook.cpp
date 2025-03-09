#include "phonebook.hpp"
#include "memtrace.h"

PhoneBook PhoneBook::searchContact(const String &param) const {
    PhoneBook results;
    const char *paramCStr = param.c_str();

    for (size_t i = 0; i < contacts.getSize(); ++i) {
        Contact *contact = contacts[i];

        if (strcasestr(contact->getName().c_str(), paramCStr) != nullptr ||
            strcasestr(contact->getNumber().c_str(), paramCStr) != nullptr ||
            strcasestr(contact->getAddress().c_str(), paramCStr) != nullptr) {

            Contact *newContact;
            if (contact->getType() == ContactType::Personal) {
                newContact = new PersonalContact(
                        Name(contact->getFirstname(), contact->getLastname(), contact->getNickname()),
                        contact->getAddress(), contact->getNumber());
            } else {
                newContact = new WorkContact(
                        Name(contact->getFirstname(), contact->getLastname(), contact->getNickname()),
                        contact->getAddress(), contact->getNumber(), contact->getEmail());
            }

            results.addContact(newContact);
        }
    }
    return results;
}


void PhoneBook::deleteContact(const String &param) {
    PhoneBook foundContacts = searchContact(param);

    for (size_t j = 0; j < foundContacts.getContacts().getSize(); ++j) {
        Contact *toDelete = foundContacts.getContacts()[j];

        for (size_t i = 0; i < contacts.getSize(); ++i) {
            if (strcmp(contacts[i]->getName().c_str(), toDelete->getName().c_str()) == 0) {
                delete contacts[i];
                contacts.remove(contacts[i]);
                break;
            }
        }
    }
}

void PhoneBook::readFromFile(std::fstream &file) {
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }

    String buffer;

    while (getline(file, buffer)) {
        int typeInt = std::atoi(buffer.c_str());
        ContactType type = static_cast<ContactType>(typeInt);

        getline(file, buffer);
        String firstname(buffer);

        getline(file, buffer);
        String lastname(buffer);

        getline(file, buffer);
        String nickname(buffer);

        getline(file, buffer);
        String address(buffer);

        getline(file, buffer);
        String number(buffer);

        if (type == ContactType::Personal) {
            contacts.add(new PersonalContact(Name(firstname, lastname, nickname), address, number));
        } else if (type == ContactType::Work) {
            getline(file, buffer);
            String email(buffer);
            contacts.add(new WorkContact(Name(firstname, lastname, nickname), address, number, email));
        }
        getline(file, buffer);
    }
}


void PhoneBook::saveToFile(std::fstream &file) const {
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        const Contact *contact = contacts[i];
        file << contact->getType() << std::endl;
        file << contact->getFirstname() << std::endl;
        file << contact->getLastname() << std::endl;
        file << contact->getNickname() << std::endl;
        file << contact->getAddress() << std::endl;
        file << contact->getNumber() << std::endl;

        if (contact->getType() == Work) {
            file << contact->getEmail() << std::endl;
        }
        file << std::endl;
    }
}

PhoneBook::~PhoneBook() {
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        delete contacts[i];
    }
}