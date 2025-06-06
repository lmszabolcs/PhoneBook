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
    String address; ///< Contact's address
    ContactType type; ///< Type of contact (Personal or Work)

public:
    /**
     * @brief Constructor for Contact class.
     * @param name Contact's name.
     * @param address Contact's address.
     * @param type Type of contact (Personal or Work).
     */
    Contact(const Name &name, const String &address, const ContactType &type)
            : name(name), address(address), type(type) {}

    /**
   * @brief Gets the full formatted name of the contact.
   * @return The full name as a String.
   */
    String getName() const { return name.getName(); }

    /**
    * @brief Gets the firstname of the contact.
    * @return The firstname as a String.
    */
    String getFirstname() const { return name.getFirstname(); }

    /**
    * @brief Gets the lastname of the contact.
    * @return The lastname as a String.
    */
    String getLastname() const { return name.getLastname(); }

    /**
     * @brief Gets the nickname of the contact.
     * @return The nickname as a String.
     */
    String getNickname() const { return name.getNickname(); }

    /**
    * @brief Gets the address of the contact.
    * @return The address as a String.
    */
    String getAddress() const { return address; }

    /**
    * @brief Gets the type of the contact (Personal or Work).
    * @return The contact type as a ContactType enum value.
    */
    ContactType getType() const { return type; }

    /**
     * @brief Pure virtual function to get the phone number.
     * @return Phone number as a String. Must be implemented by derived classes.
     */
    virtual String getNumber() const = 0;

    /**
     * @brief Virtual function to get the email (default to empty String).
     * @return Email address as a String. Can be overridden by derived classes.
     */
    virtual String getEmail() const { return ""; }

    /**
     * @brief Virtual function to print contact details to an output stream.
     * @param os Output stream to print to.
     * @return Reference to the output stream.
     */
    virtual std::ostream &print(std::ostream &os);

    /**
    * @brief Destructor for the Contact class.
    */
    virtual ~Contact() = default;
};

/**
 * @class PersonalContact
 * @brief Represents a personal contact in the phone book.
 */
class PersonalContact : public Contact {
    String personalNumber; ///< Personal phone number of the contact

public:
    /**
     * @brief Constructor for PersonalContact class.
     * @param name Contact's name.
     * @param address Contact's address.
     * @param personalNumber Contact's personal phone number.
     */
    PersonalContact(const Name &name, const String &address, const String &personalNumber)
            : Contact(name, address, ContactType::Personal), personalNumber(personalNumber) {}

    /**
     * @brief Overrides the print function to display personal contact details.
     * @param os Output stream to print to.
     * @return Reference to the output stream.
     */
    std::ostream &print(std::ostream &os) override;

    /**
     * @brief Gets the personal phone number.
     * @return Personal phone number as a String.
     */
    String getNumber() const override { return personalNumber; }

    /**
    * @brief Destructor for the PersonalContact class.
    */
    ~PersonalContact() override = default;
};

/**
 * @class WorkContact
 * @brief Represents a work contact in the phone book.
 */
class WorkContact : public Contact {
    String workNumber; ///< Work phone number of the contact
    String email;      ///< Email address of the contact

public:
    /**
     * @brief Constructor for WorkContact class.
     * @param name Contact's name.
     * @param address Contact's address.
     * @param workNumber Contact's work phone number.
     * @param email Contact's email address.
     */
    WorkContact(const Name &name, const String &address, const String &workNumber, const String &email)
            : Contact(name, address, ContactType::Work), workNumber(workNumber), email(email) {}

    /**
     * @brief Gets the work phone number.
     * @return Work phone number as a String.
     */
    String getNumber() const override { return workNumber; }

    /**
     * @brief Gets the email address.
     * @return Email address as a String.
     */
    String getEmail() const override { return email; }

    /**
     * @brief Overrides the print function to display work contact details.
     * @param os Output stream to print to.
     * @return Reference to the output stream.
     */
    std::ostream &print(std::ostream &os) override;

    /**
    * @brief Destructor for the WorkContact class.
    */
    ~WorkContact() override = default;
};

#endif //PHONEBOOK_CONTACT_HPP
