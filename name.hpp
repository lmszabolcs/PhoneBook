#include "string5.h"

#ifndef PHONEBOOK_NAME_HPP
#define PHONEBOOK_NAME_HPP

class Name {
    String firstname, lastname, nickname;
public:
    Name(const String &nickname) : nickname(String(nickname)) {}

    Name(const String &firstname, const String &lastname) : firstname(String(firstname)), lastname(String(lastname)) {}

    Name(const String &firstname, const String &lastname, const String &nickname) : firstname(String(firstname)),
                                                                                    lastname(String(lastname)),
                                                                                    nickname(String(nickname)) {}

    String getFirstname() const { return firstname; }

    String getLastname() const { return lastname; }

    String getNickname() const { return nickname; }

    String getName() const;
};

#endif //PHONEBOOK_NAME_HPP
