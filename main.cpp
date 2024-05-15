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
    PersonalContact contact1(name, "123 Elm St", "987-654-3210");
    assert(strcmp(contact1.getName().c_str(), "Alice Smith") == 0);
    assert(strcmp(contact1.getNumber().c_str(), "987-654-3210") == 0);

    Name name2("John", "Doe");
    WorkContact contact2(name2, "456 Oak St", "123-456-7890", "asd123@asd.hu");
    assert(strcmp(contact2.getName().c_str(), "John Doe") == 0);
    assert(strcmp(contact2.getNumber().c_str(), "123-456-7890") == 0);
    assert(strcmp(contact2.getEmail().c_str(), "asd123@asd.hu") == 0);
    assert(strcmp(contact2.getAddress().c_str(), "456 Oak St") == 0);

    contact1.print(std::cout);
}

int main() {
    test1();
    test2();
            // Teszt fájl tartalom
            const char* testFileContent =
                    "FirstName:John\n"
                    "LastName:Doe\n"
                    "Address:123 Main St\n"
                    "PersonalNumber:555-1212\n"
                    "\n"
                    "FirstName:Jane\n"
                    "LastName:Smith\n"
                    "NickName:Janie\n"
                    "Address:456 Elm St\n"
                    "WorkNumber:555-9876\n"
                    "Email:jane.smith@example.com\n\n";

            // Fájl létrehozása és tartalom írása
            std::ofstream outfile("test_contacts.txt");
            outfile << testFileContent;
            outfile.close();

            // Telefonkönyv objektum létrehozása és fájl beolvasása
            PhoneBook phoneBook;
            std::fstream infile("test_contacts.txt", std::ios::in);
            phoneBook.readFromFile(infile);
            infile.close();

            // Kontaktok ellenőrzése (csak a számukat nézzük)
            EXPECT_EQ(2,phoneBook.getSize());
            phoneBook.listAllContacts();

            // Teszt fájl törlése

}