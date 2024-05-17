#include <iostream>
#include <fstream>
#include "gtest_lite.h"
#include "phonebook.hpp"
#include "string5.h"
#include "name.hpp"
#include "contact.hpp"
#include "memtrace.h"

int main() {

    // ------------------------ Name Class Tests ----------------------------

    TEST(NameTest, GetName)
        {
            Name n1("John", "Doe", "Johnny");
            EXPECT_STREQ("John Doe (Johnny)", n1.getName().c_str());
            EXPECT_STREQ("John", n1.getFirstname().c_str());
            EXPECT_STREQ("Doe", n1.getLastname().c_str());

            Name n2("Nickname");
            EXPECT_STREQ("Nickname", n2.getNickname().c_str());

            Name n3; // Empty name
            EXPECT_STREQ("", n3.getName().c_str());
        }
            END


    // ------------------------ Contact Class Tests ----------------------------

    TEST(ContactTest, BaseClassFunctionality)
        {
            Name testName("Test", "Person");
            String testAddress("123 Test Street");

            PersonalContact *testContact = new PersonalContact(testName, testAddress, "555-1234");
            EXPECT_STREQ("Test Person", testContact->getName().c_str());
            EXPECT_STREQ("123 Test Street", testContact->getAddress().c_str());
            EXPECT_EQ(ContactType::Personal, testContact->getType());
        }
            END

    TEST(PersonalContactTest, SpecificFunctionality)
        {
            PersonalContact pc(Name("Alice", "Johnson"), "789 Oak St.", "555-4321");
            EXPECT_STREQ("555-4321", pc.getNumber().c_str());
            EXPECT_STREQ("", pc.getEmail().c_str()); // Personal contacts have no email
        }
            END

    TEST(WorkContactTest, SpecificFunctionality)
        {
            WorkContact wc(Name("Bob", "Williams"), "234 Pine St.", "555-7890", "bob@example.com");
            EXPECT_STREQ("555-7890", wc.getNumber().c_str());
            EXPECT_STREQ("bob@example.com", wc.getEmail().c_str());
        }
            END


    // ------------------------ PhoneBook Class Tests ----------------------------

    TEST(PhoneBookTest, AddSearchDelete)
        {
            PhoneBook pb;
            pb.addContact(new PersonalContact(Name("Alice", "Johnson"), "789 Oak St.", "555-4321"));
            pb.addContact(new WorkContact(Name("Bob", "Williams"), "234 Pine St.", "555-7890", "bob@example.com"));
            pb.addContact(new WorkContact(Name("Bob", "Wilson"), "235 Pine St.", "555-7891", "bwilson@example.com"));

            PhoneBook foundByName = pb.search("Alice");
            EXPECT_EQ(1, foundByName.getSize());

            PhoneBook foundByNumber = pb.search("555-4321");
            EXPECT_EQ(1, foundByNumber.getSize());

            // Test partial name search
            PhoneBook partialNameSearch = pb.search("Bob");
            EXPECT_EQ(2, partialNameSearch.getSize());

            // Test deleting by name
            pb.deleteContact("Alice");
            EXPECT_EQ(2, pb.getSize());

            // Test deleting by number
            pb.deleteContact("555-7890");
            EXPECT_EQ(1, pb.getSize());
        }
            END

    // ------------------------ File I/O Tests ----------------------------

    TEST(FileIOTest, ReadAndWrite)
        {
            PhoneBook pb;
            std::fstream file("test_phonebook.txt", std::ios::in | std::ios::out | std::ios::trunc);

            pb.addContact(new PersonalContact(Name("Eve", "Davis"), "567 Maple St.", "555-2345"));
            pb.addContact(
                    new WorkContact(Name("Charlie", "Brown"), "890 Cedar St.", "555-6789", "charlie@example.com"));

            pb.saveToFile(file);
            file.clear();
            file.seekg(0, std::ios::beg);

            PhoneBook pb2;
            pb2.readFromFile(file);

            EXPECT_EQ(2, pb2.getSize());
            EXPECT_STREQ("Eve Davis", pb2.getContacts()[0]->getName().c_str());
            EXPECT_STREQ("555-2345", pb2.getContacts()[0]->getNumber().c_str());
            EXPECT_STREQ("Charlie Brown", pb2.getContacts()[1]->getName().c_str());
            EXPECT_STREQ("555-6789", pb2.getContacts()[1]->getNumber().c_str());
            EXPECT_STREQ("charlie@example.com", pb2.getContacts()[1]->getEmail().c_str());
        }
            END

    return 0;
}


