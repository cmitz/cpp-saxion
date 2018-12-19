#include <utility>
#include <iostream>

//
// Created by Casper Smits on 2018-12-19.
//

#include "ValueInt.h"

ValueInt::ValueInt(std::string key, int value)
    :m_key(std::move(key)), m_value(value) { };

void ValueInt::update(int value) {
    m_value = value;
}

void ValueInt::get(std::ostream &out) const {
    out << m_key << ": " << m_value << " (int)" << std::endl;
}

std::string const &ValueInt::getName() const {
    return m_key;
}





