#include "phonebook.hpp"

void PhoneBook::listAllContacts() {
    for (size_t i = 0; i < contacts.getSize(); ++i) {
        contacts[i]->print(std::cout);
    }
}

PhoneBook PhoneBook::search(const std::string &param) const {
    PhoneBook results;
    const char *paramCStr = param.c_str();

    for (size_t i = 0; i < contacts.getSize(); ++i) {

        if (strcasestr(contacts[i]->getName().c_str(), paramCStr) != nullptr ||
            strcasestr(contacts[i]->getNumber().c_str(), paramCStr) != nullptr ||
            strcasestr(contacts[i]->getAddress().c_str(), paramCStr) != nullptr) {
            results.addContact(contacts[i]);
        }
    }
    return results;
}

void PhoneBook::deleteContact(const std::string &param) {
    PhoneBook foundContacts = search(param);

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
        std::string firstname(buffer);

        file.getline(buffer, sizeof(buffer));
        std::string lastname(buffer);

        file.getline(buffer, sizeof(buffer));
        std::string nickname(buffer);

        file.getline(buffer, sizeof(buffer));
        std::string address(buffer);

        file.getline(buffer, sizeof(buffer));
        std::string number(buffer);

        if (type == ContactType::Personal) {
            contacts.add(new PersonalContact(Name(firstname, lastname, nickname), address, number));
        } else if (type == ContactType::Work) {
            file.getline(buffer, sizeof(buffer));
            std::string email(buffer);
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