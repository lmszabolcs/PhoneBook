#include "name.hpp"

std::string Name::getName() const {
    if (firstname.size() > 0 && lastname.size() > 0) {
        if (nickname.size() > 0) {
            return firstname + " " + lastname + " (" + nickname + ")";
        } else {
            return firstname + " " + lastname;
        }
    } else
        return nickname;
}