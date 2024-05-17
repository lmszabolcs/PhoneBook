#include <iomanip>
#include "name.hpp"

#ifndef PHONEBOOK_CONTACT_HPP
#define PHONEBOOK_CONTACT_HPP

/** @enum ContactType
 *  @brief Represents the type of contact (Personal or Work).
 */
enum ContactType {
    Personal,
    Work
};

/**
 * @class Contact
 * @brief Abstract base class for representing a contact in a phone book.
 */
class Contact {
private:
    Name name;     ///< Contact's name (object of the Name class)
    std::string address; ///< Contact's address
    ContactType type; ///< Type of contact (Personal or Work)

public:
    /**
     * @brief Constructor for Contact class.
     * @param name Contact's name.
     * @param address Contact's address.
     * @param type Type of contact (Personal or Work).
     */
    Contact(Name name, const std::string &address, const ContactType &type) :
            name(std::move(name)), address(address), type(type) {}

    /**
   * @brief Gets the full formatted name of the contact.
   * @return The full name as a std::string.
   */
    std::string getName() const { return name.getName(); }

    /**
    * @brief Gets the first name of the contact.
    * @return The first name as a std::string.
    */
    std::string getFirstname() const { return name.getFirstname(); }

    /**
    * @brief Gets the last name of the contact.
    * @return The last name as a std::string.
    */
    std::string getLastname() const { return name.getLastname(); }

    /**
     * @brief Gets the nickname of the contact.
     * @return The nickname as a std::string.
     */
    std::string getNickname() const { return name.getNickname(); }

    /**
    * @brief Gets the address of the contact.
    * @return The address as a std::string.
    */
    std::string getAddress() const { return address; }

    /**
    * @brief Gets the type of the contact (Personal or Work).
    * @return The contact type as a ContactType enum value.
    */
    ContactType getType() const { return type; }

    /**
     * @brief Pure virtual function to get the phone number.
     * @return Phone number as a std::string. Must be implemented by derived classes.
     */
    virtual std::string getNumber() const = 0;

    /**
     * @brief Virtual function to get the email (default to empty std::string).
     * @return Email address as a std::string. Can be overridden by derived classes.
     */
    virtual std::string getEmail() const { return ""; }

    /**
     * @brief Virtual function to print contact details to an output stream.
     * @param os Output stream to print to.
     * @return Reference to the output stream.
     */
    virtual std::ostream &print(std::ostream &os);
};


/**
 * @class PersonalContact
 * @brief Represents a personal contact in the phone book.
 */
class PersonalContact : public Contact {
    std::string personalNumber; ///< Personal phone number of the contact

public:
    /**
     * @brief Constructor for PersonalContact class.
     * @param name Contact's name.
     * @param address Contact's address.
     * @param personalNumber Contact's personal phone number.
     */
    PersonalContact(const Name &name, const std::string &address, const std::string &personalNumber)
            : Contact(name, address, ContactType::Personal), personalNumber(personalNumber) {}

    /**
     * @brief Overrides the print function to display personal contact details.
     * @param os Output stream to print to.
     * @return Reference to the output stream.
     */
    std::ostream &print(std::ostream &os) override;

    /**
     * @brief Gets the personal phone number.
     * @return Personal phone number as a std::string.
     */
    std::string getNumber() const override { return personalNumber; }
};

/**
 * @class WorkContact
 * @brief Represents a work contact in the phone book.
 */
class WorkContact : public Contact {
    std::string workNumber; ///< Work phone number of the contact
    std::string email;      ///< Email address of the contact

public:
    /**
     * @brief Constructor for WorkContact class.
     * @param name Contact's name.
     * @param address Contact's address.
     * @param workNumber Contact's work phone number.
     * @param email Contact's email address.
     */
    WorkContact(const Name &name, const std::string &address, const std::string &workNumber, const std::string &email)
            : Contact(name, address, ContactType::Work), workNumber(workNumber), email(email) {}

    /**
     * @brief Gets the work phone number.
     * @return Work phone number as a std::string.
     */
    std::string getNumber() const override { return workNumber; }

    /**
     * @brief Gets the email address.
     * @return Email address as a std::string.
     */
    std::string getEmail() const override { return email; }

    /**
     * @brief Overrides the print function to display work contact details.
     * @param os Output stream to print to.
     * @return Reference to the output stream.
     */
    std::ostream &print(std::ostream &os) override;
};

#endif //PHONEBOOK_CONTACT_HPP
