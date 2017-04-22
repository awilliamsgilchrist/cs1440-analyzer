#ifndef ITAK_PORTSCANANALYZER_H
#define ITAK_PORTSCANANALYZER_H

#include "Analyzer.h"

class PortScanAnalyzer : public Analyzer
{
protected:
    Dictionary<std::string, std::vector<int>> m_addressSummaryDict;

public:
    ResultSet run(std::istream& in);

    PortScanAnalyzer(Configuration config): Analyzer(config) {};
};


#endif //ITAK_PORTSCANANALYZER_H
