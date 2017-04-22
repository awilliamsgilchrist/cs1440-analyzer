#include "DenialOfServiceAnalyzer.h"

ResultSet DenialOfServiceAnalyzer::run(std::istream& in)
{
    std::string address;
    std::string timestamp;
    std::string garbage;
    Dictionary<std::string, unsigned int> timestampCountDict;

    while(!in.eof())
    {
        std::getline(in, timestamp, ',');
        std::getline(in, address, ',');
        std::getline(in, garbage);

        try
        {
            timestampCountDict = m_addressSummaryDict.get(address);
        }
        catch(Exception e)
        {
            timestampCountDict = Dictionary<std::string, unsigned int>();
            m_addressSummaryDict.add(address, timestampCountDict);
        }

        try
        {
            timestampCountDict.changeVal(timestamp, timestampCountDict.get(timestamp) + 1);
        }
        catch(Exception e)
        {
            timestampCountDict.add(timestamp, 1);
        }

        m_addressSummaryDict.changeVal(address, timestampCountDict);
    }

    ResultSet result;
    std::vector<std::string> likelyVect;
    std::vector<std::string> possibVect;
    std::vector<std::string> perVect;
    std::vector<std::string> timeVect;


    int timeframe = m_configuration.getValInt("Timeframe");
    timeVect.push_back(std::to_string(timeframe));
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
            possibVect.push_back(addressSummary.getKey());
            perVect.push_back(std::to_string(startTime) + " - " + std::to_string(startTime + timeframe));
        }

        if(messageCount >= likelyThreshold)
        {
            likelyVect.push_back(addressSummary.getKey());
        }

        delete converter;
        converter = nullptr;
    }

    result.data.add("Likely attackers", likelyVect);
    result.data.add("Possible attackers", possibVect);
    result.data.add("Attack periods", perVect);
    result.data.add("Timeframe", timeVect);
    return result;
}