#include <iostream>
#include <fstream>
#include "contact.hpp"
#include "gentomb.h"

#ifndef PHONEBOOK_PHONEBOOK_HPP
#define PHONEBOOK_PHONEBOOK_HPP

/**
 * @class PhoneBook
 * @brief A class representing a phone book to manage contacts.
 */
class PhoneBook {
    GenTomb<Contact *> contacts;

public:
    /**
     * @brief Get a container of all contacts.
     * @return A GenTomb containing an array of pointers to Contact objects.
     */
    const GenTomb<Contact *>& getContacts() const { return contacts; }

    /**
     * @brief Get the number of contacts in the phone book.
     * @return The size of the contact list.
     */
    int getSize() const { return contacts.getSize(); }

    /**
     * @brief Add a new contact to the phone book.
     * @param contact A pointer to the Contact object to add.
     */
    void addContact(Contact *contact) { contacts.add(contact); }

    /**
     * @brief Search for contacts by name, number or address.
     * @param param The name, number or address to search for.
     * @return A new PhoneBook object containing matching contacts.
     */
    PhoneBook searchContact(const String &param) const;

    /**
     * @brief Delete one or multiple contacts based on name or phone number.
     * @param param The name or phone number of the contacts to delete.
     */
    void deleteContact(const String &param);

    /**
     * @brief Read contacts from a file.
     * @param file The file stream to read from.
     * @throws std::runtime_error If the file cannot be opened.
     */
    void readFromFile(std::fstream &file);

    /**
     * @brief Save contacts to a file.
     * @param file The file stream to write to.
     * @throws std::runtime_error If the file cannot be opened.
     */
    void saveToFile(std::fstream &file) const;

    /**
    * @brief Destructor for the PhoneBook class.
    * This destructor is responsible for cleaning up the memory used by the PhoneBook object.
    */
    ~PhoneBook();
};

#endif //PHONEBOOK_PHONEBOOK_HPP
