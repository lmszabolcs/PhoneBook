#include "phonebook.hpp"
#include "gtest_lite.h"
#include "memtrace.h"

#ifdef CPORTA

int main() {     // ------------------------ Name Class Tests ----------------------------

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
            delete testContact;
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

    TEST(GenTombTest, RemoveFromEmpty)
        {
            GenTomb<Contact *> emptyTomb; // Create an empty GenTomb

            Contact *dummyContact = new PersonalContact(Name("Dummy", "Contact"), "Dummy Address", "Dummy Number");

            // Attempt to remove a contact from the empty array
            EXPECT_NO_THROW(emptyTomb.remove(dummyContact));

            // Check that the size remains 0
            EXPECT_EQ(size_t(0), emptyTomb.getSize());

            delete dummyContact; // Clean up the dummy contact
        }
            END

    // ------------------------ File I/O Tests ----------------------------

    TEST(FileIOTest, ReadAndWrite)
        {
            PhoneBook pb;
            std::fstream file("test_phonebook.txt", std::ios::in | std::ios::out | std::ios::trunc);

            // Test successful writing
            pb.addContact(new PersonalContact(Name("Eve", "Davis"), "567 Maple St.", "555-2345"));
            pb.addContact(
                    new WorkContact(Name("Charlie", "Brown"), "890 Cedar St.", "555-6789", "charlie@example.com"));
            ASSERT_NO_THROW(pb.saveToFile(file));

            // Test successful reading
            file.clear(); // Clear any error flags
            file.seekg(0, std::ios::beg); // Rewind the file to the beginning

            PhoneBook pb2;
            ASSERT_NO_THROW(pb2.readFromFile(file));

            EXPECT_EQ(2, pb2.getSize());
            EXPECT_STREQ("Eve Davis", pb2.getContacts()[0]->getName().c_str());
            EXPECT_STREQ("555-2345", pb2.getContacts()[0]->getNumber().c_str());
            EXPECT_STREQ("Charlie Brown", pb2.getContacts()[1]->getName().c_str());
            EXPECT_STREQ("555-6789", pb2.getContacts()[1]->getNumber().c_str());
            EXPECT_STREQ("charlie@example.com", pb2.getContacts()[1]->getEmail().c_str());
        }
            END

    TEST(FileIOTest, ReadLargeFile)
        {
            PhoneBook pb;

            // Test reading from the larger file
            std::fstream largeFile("phonebook_large.txt", std::ios::in);
            ASSERT_NO_THROW(pb.readFromFile(largeFile));

            // Assert the correct number of contacts
            EXPECT_EQ(20, pb.getSize());

            // Verify details of the first
            EXPECT_STREQ("Alice Johnson", pb.getContacts()[0]->getName().c_str());
            EXPECT_STREQ("202-555-0123", pb.getContacts()[0]->getNumber().c_str());
            EXPECT_EQ(ContactType::Personal, pb.getContacts()[0]->getType());

            // Verify details of the last contact
            EXPECT_STREQ("Daniel Gonzalez (Danny)", pb.getContacts()[19]->getName().c_str());
            EXPECT_STREQ("503-555-0142", pb.getContacts()[19]->getNumber().c_str());
            EXPECT_STREQ("daniel.gonzalez@firm.biz", pb.getContacts()[19]->getEmail().c_str());
            EXPECT_EQ(ContactType::Work, pb.getContacts()[19]->getType());

        }
            END


    TEST(FileIOTest, FailedRead)
        {
            PhoneBook pb;
            std::fstream file("nonexistent_file.txt", std::ios::in);

            EXPECT_THROW(pb.readFromFile(file), std::runtime_error);
        }
            END

    TEST(FileIOTest, FailedWrite)
        {
            PhoneBook pb;
            pb.addContact(new PersonalContact(Name("Test", "Person"), "Test Address", "Test Number"));

            std::fstream file("/nonexistent_directory/test_phonebook.txt", std::ios::out);

            EXPECT_THROW(pb.saveToFile(file), std::runtime_error);
        }
            END
}

#else

#include "menu.hpp"

int main() {
    PhoneBook phonebook;
    Menu menu(phonebook);
    menu.show();
    return 0;
}

#endif
