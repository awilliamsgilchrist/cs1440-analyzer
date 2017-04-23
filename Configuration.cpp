#include "Configuration.h"

std::string Configuration::getValStr(std::string key)
{
    return configParams.get(key);
}

int Configuration::getValInt(std::string key)
{
    bool* isValid = new bool(true);
    int result = convertStringToInt(configParams.get(key), isValid);
    delete isValid;
    isValid = nullptr;
    return result;
}

double Configuration::getValDouble(std::string key)
{
    bool* isValid = new bool(true);
    double result = convertStringToDouble(configParams.get(key), isValid);
    delete isValid;
    isValid = nullptr;
    return result;
}

Configuration::Configuration(configType config)
{
    if(config == DenialOfService)
    {
        configParams.add("Timeframe", "100");
        configParams.add("Likely attack message count", "20");
        configParams.add("Possible attack message count", "25");
    }
    else
    {
        configParams.add("Likely attack port count", "3");
        configParams.add("Possible attack port count", "2");
    }
}