#ifndef ITAK_DENIALOFSERVICEANALYZER_H
#define ITAK_DENIALOFSERVICEANALYZER_H

#include "Analyzer.h"

class DenialOfServiceAnalyzer : public Analyzer
{
protected:
    Dictionary<std::string, Dictionary<std::string, unsigned int>> m_addressSummaryDict;

public:
    ResultSet run(std::istream& in);

    DenialOfServiceAnalyzer(Configuration config): Analyzer(config) {};
};


#endif //ITAK_DENIALOFSERVICEANALYZER_H
