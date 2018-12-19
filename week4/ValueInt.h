//
// Created by Casper Smits on 2018-12-19.
//

#ifndef WEEK4_VALUEINT_H
#define WEEK4_VALUEINT_H


#include <string>

class ValueInt {
private:
    std::string m_key;
    int m_value;

public:
    ValueInt(std::string key, int value);

    void update(int value);
    void get(std::ostream &out) const;
    std::string const &getName() const;
};


#endif //WEEK4_VALUEINT_H
