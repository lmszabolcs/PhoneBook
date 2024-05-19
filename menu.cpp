#include "menu.hpp"
#include <iostream>
#include "memtrace.h"

using std::cout;
using std::cin;
using std::endl;
using std::getline;

void Menu::show() {
    while (state != EXIT) {
        try {
            switch (state) {
                case MAIN_MENU:
                    state = mainMenu();
                    break;
                case CONTACT_ADD:
                    state = contactAdd();
                    break;
                case CONTACT_LIST:
                    state = contactList();
                    break;
                case CONTACT_SEARCH:
                    state = contactSearch();
                    break;
                case CONTACT_DELETE:
                    state = contactDelete();
                    break;
                case FILE_READ:
                    state = readFile();
                    break;
                case FILE_SAVE:
                    state = saveFile();
                    break;
                case EXIT:
                    break;
            }
        } catch (const std::exception &e) {
            handleException(e);
            state = MAIN_MENU;
        }
    }
}

Menu::MenuState Menu::mainMenu() {
    cout << "Főmenü\n";
    cout << "1 - Névjegy hozzáadása\n";
    cout << "2 - Névjegyek listázása\n";
    cout << "3 - Névjegyek keresése\n";
    cout << "4 - Névjegyek törlése\n";
    cout << "5 - Beolvasás fájlból\n";
    cout << "6 - Mentés fájlba\n";
    cout << "7 - Kilépés\n";

    int choice;
    do {
        cout << "Választás: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Érvénytelen bemenet. Kérlek, adj meg egy számot 0 és 5 között." << endl;
        }
    } while (choice < 0 || choice > 7);

    return static_cast<MenuState>(choice);
}

Menu::MenuState Menu::contactAdd() {
    cout << "Névjegy hozzáadása\n";
    String lastname, firstname, nickname, address, number, email;
    int type;

    cout << "Vezetéknév: ";
    cin >> lastname;
    cout << "Keresztnév: ";
    cin >> firstname;
    cout << "Becenév (opcionális): ";
    cin.ignore();
    getline(cin, nickname);
    cout << "Cím: ";
    getline(cin, address);

    cout << "Telefonszám: ";
    cin >> number;
    cout << "Típus (0: Személyes, 1: Munkahelyi): ";
    while (!(cin >> type) || (type != 0 && type != 1)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Érvénytelen típus! Kérlek, adj meg 0-t (Személyes) vagy 1-et (Munkahelyi): ";
    }

    if (type == 0) {
        phonebook.addContact(new PersonalContact(Name(firstname, lastname, nickname), address, number));
    } else if (type == 1) {
        cout << "Email cím: ";
        cin >> email;
        phonebook.addContact(new WorkContact(Name(firstname, lastname, nickname), address, number, email));
    } else {
        cout << "Érvénytelen típus!\n";
    }
    return MAIN_MENU;
}

Menu::MenuState Menu::contactList() const{
    cout << "Névjegyek listázása\n";
    for (size_t i = 0; i < phonebook.getContacts().getSize(); ++i) {
        phonebook.getContacts()[i]->print(std::cout);
    }
    return MAIN_MENU;
}

Menu::MenuState Menu::contactSearch() const{
    cout << "Névjegyek keresése\n";
    String searchParam;
    cout << "Keresendő név/szám/cím: ";
    cin >> searchParam;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    PhoneBook found = phonebook.searchContact(searchParam);
    if (found.getSize() == 0) {
        cout << "Nincs találat.\n";
    } else {
        contactList();
    }
    return MAIN_MENU;
}

Menu::MenuState Menu::contactDelete() {
    cout << "Névjegyek törlése\n";
    String deleteParam;
    cout << "Törlendő név/szám: ";
    cin >> deleteParam;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    phonebook.deleteContact(deleteParam);
    return MAIN_MENU;
}

Menu::MenuState Menu::saveFile() const {
    cout << "Mentés fájlba\n";
    std::fstream file("phonebook.txt", std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Nem sikerült megnyitni a fájlt írásra.");
    }
    phonebook.saveToFile(file);
    file.close();
    cout << "Névjegyek sikeresen mentve a phonebook.txt fájlba.\n";
    return MAIN_MENU;
}

Menu::MenuState Menu::readFile() {
    cout << "Névjegyek betöltése fájlból\n";
    std::fstream file("phonebook.txt", std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error("Nem sikerült megnyitni a fájlt olvasásra.");
    }

    phonebook.readFromFile(file);
    file.close();

    cout << "Névjegyek sikeresen betöltve a phonebook.txt fájlból.\n";
    return MAIN_MENU;
}

void Menu::handleException(const std::exception &e) {
    std::cerr << "Hiba történt: " << e.what() << std::endl;
}
