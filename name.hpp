#include "string5.h"
#ifndef PHONEBOOK_NAME_HPP
#define PHONEBOOK_NAME_HPP

/**
 * @class Name
 * @brief Represents a person's name, including first name, last name, and nickname.
 */
class Name {
private:
    String firstname; ///< Firstname of the person
    String lastname;  ///< Lastname of the person
    String nickname;  ///< Nickname of the person

public:
    /**
    * @brief Default constructor for Name.
    * This constructor initializes an empty Name object with empty Strings for the first name, last name, and nickname.
    */
    Name() : firstname(""), lastname(""), nickname("") {}

    /**
     * @brief Constructor for Name when only a nickname is available.
     * @param nickname The person's nickname.
     */
    Name(const String &nickname) : firstname(""), lastname(""), nickname(String(nickname)) {}

    /**
     * @brief Constructor for Name when first name and last name are available.
     * @param firstname The person's first name.
     * @param lastname The person's last name.
     */
    Name(const String &firstname, const String &lastname) : firstname(String(firstname)), lastname(String(lastname)),
                                                            nickname("") {}

    /**
     * @brief Constructor for Name when first name, last name, and nickname are available.
     * @param firstname The person's first name.
     * @param lastname The person's last name.
     * @param nickname The person's nickname.
     */
    Name(const String &firstname, const String &lastname, const String &nickname) : firstname(String(firstname)),
                                                                                    lastname(String(lastname)),
                                                                                    nickname(String(nickname)) {}

    /**
     * @brief Gets the person's first name.
     * @return The first name as a String.
     */
    String getFirstname() const { return firstname; }

    /**
     * @brief Gets the person's last name.
     * @return The last name as a String.
     */
    String getLastname() const { return lastname; }

    /**
     * @brief Gets the person's nickname.
     * @return The nickname as a String.
     */
    String getNickname() const { return nickname; }

    /**
     * @brief Gets the full name in a formatted way.
     * @return The full name as a String.
     *         If only first and last name exist, returns "firstname lastname"
     *         If only nickname exists, returns the nickname.
     *         If all three exists, returns "firstname lastname (nickname)".
     */
    String getName() const;
};

#endif //PHONEBOOK_NAME_HPP
