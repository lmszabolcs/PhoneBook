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
    PersonalContact contact1(name,  "123 Elm St","987-654-3210");
    assert(strcmp(contact1.getName().c_str(), "Alice Smith") == 0);
    assert(strcmp(contact1.getNumber().c_str(), "987-654-3210") == 0);

    Name name2("John", "Doe");
    WorkContact contact2(name2, "456 Oak St", "123-456-7890", "asd123@asd.hu" );
    assert(strcmp(contact2.getName().c_str(), "John Doe") == 0);
    assert(strcmp(contact2.getNumber().c_str(), "123-456-7890") == 0);
    assert(strcmp(contact2.getEmail().c_str(), "asd123@asd.hu") == 0);
    assert(strcmp(contact2.getAddress().c_str(), "456 Oak St") == 0);

    contact1.print(std::cout);
}

void test3() {
    // PhoneBook osztály tesztjei
    PhoneBook phoneBook;

    Name name1("John", "Doe");
    WorkContact contact1(name1, "123 Main St","123-456-7890", "asdasd@asd.hu");
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
