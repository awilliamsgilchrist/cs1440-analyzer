#include "PortScanAnalyzer.h"

ResultSet PortScanAnalyzer::run(std::istream &in)
{
    std::string address;
    int destinationPort;
    std::string garbage;
    std::vector<int> portList;

    while(!in.eof())
    {
        std::getline(in, garbage, ',');
        std::getline(in, address, ',');
        std::getline(in, garbage, ',');
        std::getline(in, garbage);
        destinationPort = std::stoi(garbage);

        try
        {
            portList = m_addressSummaryDict.get(address);
        }
        catch(MyException e)
        {
            m_addressSummaryDict.add(address, portList);
        }

        if(portList.size() == 0)
        {
            portList.push_back(destinationPort);
        }
        for(unsigned int i = 0; i < portList.size(); i++)
        {
            if(portList[i] == destinationPort)
            {
                break;
            }

            if(i == portList.size() - 1)
            {
                portList.push_back(destinationPort);
            }
        }
    }

    ResultSet results;
    std::vector<std::string> likeVect;
    std::vector<std::string> possVect;
    std::vector<std::string> portVect;
    int likelyThreshold = m_configuration.getValInt("Likely attack port count");
    int possThreshold = m_configuration.getValInt("Possible attack port count");
    int numPorts = 0;

    for(KeyValue<std::string, std::vector<int>> addressSummary : m_addressSummaryDict.getAll())
    {
        if(addressSummary.getValue().size() >= possThreshold)
        {
            possVect.push_back(addressSummary.getKey());
            if(addressSummary.getValue().size() >= likelyThreshold)
            {
                likeVect.push_back(addressSummary.getKey());
            }
        }

        numPorts += addressSummary.getValue().size();
    }

    portVect.push_back(std::to_string(numPorts));

    results.data.add("Likely attackers", likeVect);
    results.data.add("Possible attackers", possVect);
    results.data.add("Port count", portVect);
    return results;
}

