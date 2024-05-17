#include "phonebook.hpp"
#include "memtrace.h"

void PhoneBook::listAllContacts() {
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        contacts[i]->print(std::cout);
    }
}

PhoneBook PhoneBook::search(const String &param) const {
    PhoneBook results;
    const char *paramCStr = param.c_str();

    for (size_t i = 0; i < contacts.getSize(); ++i) {
        Contact *contact = contacts[i];

        if (strcasestr(contact->getName().c_str(), paramCStr) != nullptr ||
            strcasestr(contact->getNumber().c_str(), paramCStr) != nullptr ||
            strcasestr(contact->getAddress().c_str(), paramCStr) != nullptr) {

            Contact *newContact;
            if (contact->getType() == ContactType::Personal) {
                newContact = new PersonalContact(dynamic_cast<PersonalContact &>(*contact));
            } else {
                newContact = new WorkContact(dynamic_cast<WorkContact &>(*contact));
            }

            results.addContact(newContact);
        }
    }
    return results;
}


void PhoneBook::deleteContact(const String& param) {
    PhoneBook foundContacts = search(param);

    for (size_t i = 0; i < foundContacts.getContacts().getSize(); ++i) {
        delete contacts[i];
        contacts.remove(contacts[i]);
    }
}

void PhoneBook::readFromFile(std::fstream &file) {
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