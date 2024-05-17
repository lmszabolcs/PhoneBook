#include <iostream>

#ifndef PHONEBOOK_NAME_HPP
#define PHONEBOOK_NAME_HPP

/**
 * @class Name
 * @brief Represents a person's name, including first name, last name, and nickname.
 */
class Name {
private:
    std::string firstname; ///< Firstname of the person
    std::string lastname;  ///< Lastname of the person
    std::string nickname;  ///< Nickname of the person

public:
    /**
    * @brief Default constructor for Name.
    * This constructor initializes an empty Name object with empty std::strings for the first name, last name, and nickname.
    */
    Name() : firstname(""), lastname(""), nickname("") {}

    /**
     * @brief Constructor for Name when only a nickname is available.
     * @param nickname The person's nickname.
     */
    Name(const std::string &nickname) : firstname(""), lastname(""), nickname(std::string(nickname)) {}

    /**
     * @brief Constructor for Name when first name and last name are available.
     * @param firstname The person's first name.
     * @param lastname The person's last name.
     */
    Name(const std::string &firstname, const std::string &lastname) : firstname(std::string(firstname)), lastname(std::string(lastname)),
                                                            nickname("") {}

    /**
     * @brief Constructor for Name when first name, last name, and nickname are available.
     * @param firstname The person's first name.
     * @param lastname The person's last name.
     * @param nickname The person's nickname.
     */
    Name(const std::string &firstname, const std::string &lastname, const std::string &nickname) : firstname(std::string(firstname)),
                                                                                    lastname(std::string(lastname)),
                                                                                    nickname(std::string(nickname)) {}

    /**
     * @brief Gets the person's first name.
     * @return The first name as a std::string.
     */
    std::string getFirstname() const { return firstname; }

    /**
     * @brief Gets the person's last name.
     * @return The last name as a std::string.
     */
    std::string getLastname() const { return lastname; }

    /**
     * @brief Gets the person's nickname.
     * @return The nickname as a std::string.
     */
    std::string getNickname() const { return nickname; }

    /**
     * @brief Gets the full name in a formatted way.
     * @return The full name as a std::string.
     *         If only first and last name exist, returns "firstname lastname"
     *         If only nickname exists, returns the nickname.
     *         If all three exists, returns "firstname lastname (nickname)".
     */
    std::string getName() const;
};

#endif //PHONEBOOK_NAME_HPP
