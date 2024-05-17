#include "phonebook.hpp"

void PhoneBook::listAllContacts() {
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        contacts[i]->print(std::cout);
    }
}

PhoneBook PhoneBook::searchForName(const String &name) const {
    PhoneBook temp;
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        if (strstr(contacts[i]->getName().c_str(), name.c_str()) != nullptr) {
            temp.addContact(contacts[i]);
        }
    }
    return temp;
}


PhoneBook PhoneBook::searchForPhoneNumber(const String &number) const {
    PhoneBook temp;
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        if (strstr(contacts[i]->getNumber().c_str(), number.c_str()) != nullptr) {
            temp.addContact(contacts[i]);
        }
    }
    return temp;
}

PhoneBook PhoneBook::searchForAddress(const String &address) const {
    PhoneBook temp;
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        if (strstr(contacts[i]->getAddress().c_str(), address.c_str()) != nullptr) {
            temp.addContact(contacts[i]);
        }
    }
    return temp;
}

void PhoneBook::deleteContact(const String &param) {
    PhoneBook foundContacts = searchForName(param);
    PhoneBook temp = searchForPhoneNumber(param);

    for (size_t i = 0; i < temp.getSize(); ++i)
        foundContacts.addContact(temp.contacts[i]);

    for (size_t i = 0; i < foundContacts.contacts.getSize(); ++i)
        contacts.remove(foundContacts.contacts[i]);

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