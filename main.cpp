#include <iostream>
#include <cassert>
#include "telefonkonyv.h"

void test1() {
    // Name osztály teszjei
    Name name1("John", "Doe");
    Name name2("Bob");
    Name name3("Lisa", "Smith", "Liz");

    assert(strcmp(name1.getName().c_str(), "John Doe") == 0);
    assert(strcmp(name2.getName().c_str(), "Bob") == 0);
    assert(strcmp(name3.getName().c_str(), "Lisa Smith (Liz)") == 0);
}

void test2() {
    // Contact osztály tesztjei
    Name name("Alice", "Smith");
    Contact contact1(name, "987-654-3210", "123 Elm St");
    assert(strcmp(contact1.getName().c_str(), "Alice Smith") == 0);
    assert(strcmp(contact1.getPersonal().c_str(), "987-654-3210") == 0);

    Name name2("John", "Doe");
    Contact contact2(name2, "123-456-7890", "555-555-123", "456 Oak St");
    assert(strcmp(contact2.getName().c_str(), "John Doe") == 0);
    assert(strcmp(contact2.getPersonal().c_str(), "123-456-7890") == 0);
    assert(strcmp(contact2.getWork().c_str(), "555-555-123") == 0);
    assert(strcmp(contact2.getAddress().c_str(), "456 Oak St") == 0);

    contact1.print(std::cout);
}

void test3() {
    // PhoneBook osztály tesztjei
    PhoneBook phoneBook;

    Name name1("John", "Doe");
    Contact contact1(name1, "123-456-7890", "123 Main St");
    phoneBook.addContact(&contact1);

    phoneBook.listAllContacts();

    String searchName = "John Doe";
    phoneBook.deleteContact(searchName);
    PhoneBook p1 = phoneBook.searchForName(searchName);
    p1.listAllContacts();
    std::cout<<"\n";
    phoneBook.listAllContacts();
}

int main() {
    test1();
    test2();
    test3();
}
