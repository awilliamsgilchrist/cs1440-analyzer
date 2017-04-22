#include "DenialOfServiceAnalyzer.h"

ResultSet DenialOfServiceAnalyzer::run(std::istream& in)
{
    std::string address;
    std::string timestamp;
    std::string garbage;
    Dictionary<std::string, unsigned int>* timestampCountDict;

    while(!in.eof())
    {
        std::getline(in, timestamp, ',');
        std::getline(in, address, ',');
        std::getline(in, garbage);

        try
        {
            timestampCountDict = m_addressSummaryDict.getRef(address);
        }
        catch(Exception e)
        {
            timestampCountDict = new Dictionary<std::string, unsigned int>();
            m_addressSummaryDict.add(address, *timestampCountDict);
        }

        try
        {
            timestampCountDict->changeVal(timestamp, timestampCountDict->get(timestamp) + 1);
        }
        catch(Exception e)
        {
            timestampCountDict->add(timestamp, 1);
        }
    }
    timestampCountDict = nullptr;

    ResultSet result;
    result.data.add("Likely attackers", std::vector<std::string>());
    result.data.add("Possible attackers", std::vector<std::string>());
    result.data.add("Attack periods", std::vector<std::string>());
    result.data.add("Timeframe", std::vector<std::string>());

    int timeframe = m_configuration.getValInt("Timeframe");
    int likelyThreshold = m_configuration.getValInt("Likely attack message count");
    int possibleThreshold = m_configuration.getValInt("Possible attack message count");

    for(KeyValue<std::string, Dictionary<std::string, unsigned int>> addressSummary : m_addressSummaryDict.getAll())
    {
        bool isNewAddress = true;
        bool* converter = new bool(true);
        int messageCount = 0;
        int startTime;

        for(KeyValue<std::string, unsigned int> timeCount : addressSummary.getValue().getAll())
        {
            if(isNewAddress)
            {
                startTime = convertStringToInt(timeCount.getKey(), converter);
                isNewAddress = false;
            }

            if(convertStringToInt(timeCount.getKey(), converter) > startTime + timeframe)
            {
                break;
            }

            messageCount += timeCount.getValue();
        }

        if(messageCount >= possibleThreshold)
        {
            result.data.getRef("Possible attackers")->push_back(addressSummary.getKey());
            result.data.getRef("Atttack periods")->push_back(std::to_string(startTime) + " - " + std::to_string(startTime + timeframe));
        }

        if(messageCount >= likelyThreshold)
        {
            result.data.getRef("Likely attackers")->push_back(addressSummary.getKey());
        }

        delete converter;
        converter = nullptr;
    }

    return result;
}