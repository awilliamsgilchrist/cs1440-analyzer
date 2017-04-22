#ifndef ITAK_RESULTSET_H
#define ITAK_RESULTSET_H

#include <string>
#include <vector>
#include "Dictionary.h"
#include "Utils.h"

class ResultSet {
public:
    Dictionary<std::string, std::vector<std::string>> data;

    void print(std::ostream& out);

    ResultSet() {};
};


#endif //ITAK_RESULTSET_H
