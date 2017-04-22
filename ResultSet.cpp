#include "ResultSet.h"

void ResultSet::print(std::ostream& out)
{
    std::vector<KeyValue<std::string, std::vector<std::string>>> results = data.getAll();

    for(KeyValue<std::string, std::vector<std::string>> entry : results)
    {
        out << entry.getKey() << std::endl;

        for(std::string content : entry.getValue())
        {
            out << content << std::endl;
        }

        out << std::endl;
    }
}