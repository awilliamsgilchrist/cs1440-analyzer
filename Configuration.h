#ifndef ITAK_CONFIGURATION_H
#define ITAK_CONFIGURATION_H

#include <string>
#include "Dictionary.h"
#include "Utils.h"

class Configuration {
public:
    Dictionary<std::string, std::string> configParams;

    std::string getValStr(std::string key);
    int getValInt(std::string key);
    double getValDouble(std::string key);

    Configuration() {};
    Configuration(configType config);
};


#endif //ITAK_CONFIGURATION_H
