#include <iostream>
#include "ValueInt.h"

int main() {
    ValueInt intvalue("TestInt", 10);
    intvalue.get(std::cout);
    intvalue.update(20);
    intvalue.get(std::cout);

    return 0;
}