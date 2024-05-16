#include "telefonkonyv.h"
#include <iostream>
#include <sstream>
#include <string>


// ... (your other includes and class definitions)

#define MY_CUSTOM_TEST(C, N) void C##_##N##_()


// --- Test function definitions OUTSIDE the main function ---

MY_CUSTOM_TEST(PhoneBookTest, AddContact) {
    PhoneBook book;

    // Add valid personal contact
    PersonalContact* personal = new PersonalContact(Name("John", "Doe", "Johnny"), "123 Main St", "555-1212");
    book.addContact(personal);

    // Add valid work contact
    WorkContact* work = new WorkContact(Name("Jane", "Smith"), "456 Elm St", "555-9876", "jane@example.com");
    book.addContact(work);

    // Redirect GTEST_LITE output to a stringstream
    std::ostringstream testOutput;
    gtest_lite::ostreamRedir redirect(gtest_lite::test.os, testOutput);

    // Check if both contacts were added
    EXPECT_EQ(2, book.getSize());

    // Test that the contacts were added with the correct information
    EXPECT_STREQ("John Doe (Johnny)", book.getContacts()[0]->getName().c_str());
    EXPECT_STREQ("555-1212", book.getContacts()[0]->getNumber().c_str());
    EXPECT_STREQ("123 Main St", book.getContacts()[0]->getAddress().c_str());

    EXPECT_STREQ("Jane Smith", book.getContacts()[1]->getName().c_str());
    EXPECT_STREQ("555-9876", book.getContacts()[1]->getNumber().c_str());
    EXPECT_STREQ("jane@example.com", book.getContacts()[1]->getEmail().c_str());
    EXPECT_STREQ("456 Elm St", book.getContacts()[1]->getAddress().c_str());

    // Test adding a duplicate contact (should not be added)
    book.addContact(personal);
    EXPECT_EQ(2, book.getSize()); // Size should remain the same

    // Test adding a null contact (should not be added)
    book.addContact(nullptr);
    EXPECT_EQ(2, book.getSize()); // Size should remain the same

    if (gtest_lite::test.astatus()) {
        std::cout << "PhoneBookTest_AddContact: PASSED\n";
    } else {
        std::cout << "PhoneBookTest_AddContact: FAILED\n";
        std::cout << testOutput.str();
    }

    delete personal;
    delete work;
}

MY_CUSTOM_TEST(PhoneBookTest, SearchForName) {
    PhoneBook book;
    book.addContact(new PersonalContact(Name("John", "Doe", "Johnny"), "123 Main St", "555-1212"));
    book.addContact(new WorkContact(Name("Jane", "Smith"), "456 Elm St", "555-9876", "jane@example.com"));
    // Redirect GTEST_LITE output to a stringstream
    std::ostringstream testOutput;
    gtest_lite::ostreamRedir redirect(gtest_lite::test.os, testOutput);

    PhoneBook result = book.searchForName("John");
    EXPECT_EQ(1, result.getSize());
    EXPECT_STREQ("John Doe (Johnny)", result.getContacts()[0]->getName().c_str());
    // Hibás bemenet tesztelése
    result = book.searchForName("Nonexistent");
    EXPECT_EQ(0, result.getSize());

    if (gtest_lite::test.astatus()) {
        std::cout << "PhoneBookTest_SearchForName: PASSED\n";
    } else {
        std::cout << "PhoneBookTest_SearchForName: FAILED\n";
        std::cout << testOutput.str();
    }
}


MY_CUSTOM_TEST(PhoneBookTest, SearchForPhoneNumber) {
    // Test code for PhoneBook::searchForPhoneNumber

    // Redirection and output
    std::ostringstream testOutput;
    gtest_lite::ostreamRedir redirect(gtest_lite::test.os, testOutput);

    if (gtest_lite::test.astatus()) {
        std::cout << "PhoneBookTest_SearchForPhoneNumber: PASSED\n";
    } else {
        std::cout << "PhoneBookTest_SearchForPhoneNumber: FAILED\n";
        std::cout << testOutput.str();
    }

}
MY_CUSTOM_TEST(PhoneBookTest, SearchForAddress) {
    PhoneBook book;
    book.addContact(new PersonalContact(Name("John", "Doe", "Johnny"), "123 Main St", "555-1212"));
    book.addContact(new WorkContact(Name("Jane", "Smith"), "456 Elm St", "555-9876", "jane@example.com"));

    std::ostringstream testOutput;
    gtest_lite::ostreamRedir redirect(gtest_lite::test.os, testOutput);

    PhoneBook result = book.searchForAddress("Main");
    EXPECT_EQ(1, result.getSize());
    EXPECT_STREQ("John Doe (Johnny)", result.getContacts()[0]->getName().c_str());

    // Hibás bemenet tesztelése
    result = book.searchForAddress("Unknown");
    EXPECT_EQ(0, result.getSize());

    if (gtest_lite::test.astatus()) {
        std::cout << "PhoneBookTest_SearchForAddress: PASSED\n";
    } else {
        std::cout << "PhoneBookTest_SearchForAddress: FAILED\n";
        std::cout << testOutput.str();
    }
}

MY_CUSTOM_TEST(PhoneBookTest, DeleteContact) {
    PhoneBook book;
    PersonalContact* personal = new PersonalContact(Name("John", "Doe", "Johnny"), "123 Main St", "555-1212");
    WorkContact* work = new WorkContact(Name("Jane", "Smith"), "456 Elm St", "555-9876", "jane@example.com");
    book.addContact(personal);
    book.addContact(work);

    // Redirect GTEST_LITE output to a stringstream
    std::ostringstream testOutput;
    gtest_lite::ostreamRedir redirect(gtest_lite::test.os, testOutput);

    book.deleteContact("John");
    EXPECT_EQ(1, book.getSize());

    // Hibás bemenet tesztelése
    //book.deleteContact("Nonexistent");
    EXPECT_EQ(1, book.getSize());

    if (gtest_lite::test.astatus()) {
        std::cout << "PhoneBookTest_DeleteContact: PASSED\n";
    } else {
        std::cout << "PhoneBookTest_DeleteContact: FAILED\n";
        std::cout << testOutput.str();
    }
}


MY_CUSTOM_TEST(PhoneBookTest, SaveToFile) {
    PhoneBook book;
    book.addContact(new PersonalContact(Name("John", "Doe", "Johnny"), "123 Main St", "555-1212"));
    book.addContact(new WorkContact(Name("Jane", "Smith"), "456 Elm St", "555-9876", "jane@example.com"));

    std::ostringstream testOutput;
    gtest_lite::ostreamRedir redirect(gtest_lite::test.os, testOutput);

    std::fstream file("test_contacts.txt", std::ios::out);
    book.saveToFile(file);
    file.close();

    // Itt ellenőrizhetnéd a fájl tartalmát, hogy megfelel-e az elvártnak.
    if (gtest_lite::test.astatus()) {
        std::cout << "PhoneBookTest_SaveToFile: PASSED\n";
    } else {
        std::cout << "PhoneBookTest_SaveToFile: FAILED\n";
        std::cout << testOutput.str();
    }

}

MY_CUSTOM_TEST(PhoneBookRead, BasicRead) {
PhoneBook phonebook;
std::fstream file("test_contacts.txt", std::ios::in);
phonebook.readFromFile(file);
phonebook.listAllContacts();
// Assertions
EXPECT_EQ(2, phonebook.getSize());
Contact* contact1 = phonebook.getContacts()[0];
EXPECT_EQ(ContactType::Personal, contact1->getType());
EXPECT_STREQ("John", contact1->getFirstname().c_str());
EXPECT_STREQ("Doe", contact1->getLastname().c_str());
EXPECT_STREQ("Johnny", contact1->getNickname().c_str());
EXPECT_STREQ("123 Main St", contact1->getAddress().c_str());
EXPECT_STREQ("555-1212", contact1->getNumber().c_str());

Contact* contact2 = phonebook.getContacts()[1];
EXPECT_EQ(ContactType::Work, contact2->getType());
EXPECT_STREQ("Jane", contact2->getFirstname().c_str());
EXPECT_STREQ("Smith", contact2->getLastname().c_str());
EXPECT_STREQ("", contact2->getNickname().c_str());
EXPECT_STREQ("456 Elm St", contact2->getAddress().c_str());
EXPECT_STREQ("555-9876", contact2->getNumber().c_str());
EXPECT_STREQ("jane@example.com", contact2->getEmail().c_str());

// Close the file AFTER all assertions
file.close();

// Clean up
}


int main() {
    GTINIT(std::cin)

    // Call each test function manually
    PhoneBookTest_AddContact_();
    PhoneBookTest_SearchForName_();  // Add this line
    PhoneBookTest_SearchForPhoneNumber_(); // Add this line
    PhoneBookTest_SearchForAddress_();
    PhoneBookTest_DeleteContact_();
    PhoneBookTest_SaveToFile_();
    PhoneBookRead_BasicRead_();
    GTEND(std::cerr)

    return 0; // Return 0 to indicate successful execution
}
