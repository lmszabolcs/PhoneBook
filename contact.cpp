#include "contact.hpp"
#include "memtrace.h"


std::ostream &Contact::print(std::ostream &os) {
    os << "\n" << std::setw(25) << std::left << name.getName() << std::setw(25) << address << "\n";
    return os;
}

std::ostream &PersonalContact::print(std::ostream &os) {
    this->Contact::print(os);
    os << std::setw(25) << std::left << "Personal Number: " << personalNumber << "\n";
    return os;
}

std::ostream &WorkContact::print(std::ostream &os) {
    this->Contact::print(os);
    os << std::setw(25) << std::left << "Work Number: " << workNumber << "\n";
    os << std::setw(25) << std::left << "Email: " << email << "\n";
    return os;
}
