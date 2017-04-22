#ifndef ITAK_ANALYZER_H
#define ITAK_ANALYZER_H

#include "Configuration.h"
#include "ResultSet.h"

class Analyzer
{
protected:
    Configuration m_configuration;

public:
    virtual ResultSet run(std::istream& in) = 0;

    Analyzer() {};
    Analyzer(Configuration config): m_configuration(config) {};
};

#endif //ITAK_ANALYZER_H
