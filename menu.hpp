#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "phonebook.hpp"

/**
 * @brief Class for managing the menu system of the phonebook application.
 */
class Menu {
public:
    /**
     * @brief Enumeration representing the different states of the menu.
     */
    enum MenuState {
        MAIN_MENU = 0,  ///< Main menu state
        CONTACT_ADD = 1,  ///< Add contact state
        CONTACT_LIST = 2,  ///< List contacts state
        CONTACT_SEARCH = 3,  ///< Search contacts state
        CONTACT_DELETE = 4,  ///< Delete contact state
        FILE_READ = 5,  ///< Read from file state
        FILE_SAVE = 6,  ///< Save to file state
        EXIT = 7  ///< Exit state
    };

private:
    MenuState state;  ///< The current state of the menu
    PhoneBook &phonebook;  ///< Reference to the phonebook object

private:
    /**
     * @brief Function to display the main menu and handle user input.
     * @return The menu state chosen by the user.
     */
    static MenuState mainMenu();

    /**
     * @brief Function to handle adding a new contact.
     * @return The main menu state (MAIN_MENU).
     */
    MenuState contactAdd();

    /**
     * @brief Function to handle listing all contacts.
     * @return The main menu state (MAIN_MENU).
     */
    MenuState contactList() const;

    /**
     * @brief Function to handle searching for contacts.
     * @return The main menu state (MAIN_MENU).
     */
    MenuState contactSearch() const;

    /**
     * @brief Function to handle deleting a contact.
     * @return The main menu state (MAIN_MENU).
     */
    MenuState contactDelete();

    /**
     * @brief Function to handle saving the phonebook to a file.
     * @return The main menu state (MAIN_MENU).
     */
    MenuState saveFile() const;

    /**
    * @brief Function to handle reading from a file.
    * @return The main menu state (MAIN_MENU).
    */
    MenuState readFile();

public:
    /**
     * @brief Constructor for the Menu class.
     * @param pb Reference to the phonebook object.
     */
    Menu(PhoneBook &pb) : state(MAIN_MENU), phonebook(pb) {}

    /**
     * @brief Function to run the main menu loop.
     */
    void show();

    /**
     * @brief Function to handle exceptions.
     * @param e The exception object.
     */
    static void handleException(const std::exception &e);
};

#endif // MENU_HPP
