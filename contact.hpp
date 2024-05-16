#include <iomanip>
#include "name.hpp"

#ifndef PHONEBOOK_CONTACT_HPP
#define PHONEBOOK_CONTACT_HPP
enum ContactType {
    Personal,
    Work
};

class Contact {
    Name name;
    String address;
    ContactType type;

public:
    Contact(const Name &name, const String &address, const ContactType &type) : name(name), address(address),
                                                                                type(type) {}

    String getName() const { return name.getName(); }

    String getFirstname() const { return name.getFirstname(); }

    String getLastname() const { return name.getLastname(); }

    String getNickname() const { return name.getNickname(); }

    String getAddress() const { return address; }

    ContactType getType() const { return type; }

    void setType(ContactType type) { type = type; }

    virtual String getNumber() const = 0;

    virtual String getEmail() const { return ""; }

    virtual std::ostream &print(std::ostream &os);
};

class PersonalContact : public Contact {
    String personalNumber;
public:
    PersonalContact(const Name &name, const String &address, const String &personalNumber)
            : Contact(name, address, ContactType::Personal), personalNumber(personalNumber) {}

    std::ostream &print(std::ostream &os) override;

    String getNumber() const { return personalNumber; }
};

class WorkContact : public Contact {
    String workNumber;
    String email;
public:
    WorkContact(const Name &name, const String &address, const String &workNumber, const String &email)
            : Contact(name, address, ContactType::Work), workNumber(workNumber), email(email) {}


    String getNumber() const { return workNumber; }

    String getEmail() const { return email; }

    std::ostream &print(std::ostream &os) override;
};

#endif //PHONEBOOK_CONTACT_HPP
