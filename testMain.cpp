#include <fstream>
#include <iostream>
#include "DenialOfServiceAnalyzer.h"
#include "PortScanAnalyzer.h"


int main()
{
    std::ifstream in("testInput.txt");
    if(in.fail())
    {
        std::cout << "File failed to open" << std::endl;
        return 1;
    }
    
    Configuration portConfig(PortScan);
    portConfig.configParams.changeVal("Possible attack port count", "2");
    portConfig.configParams.changeVal("Likely attack port count", "5");

    PortScanAnalyzer portTest(portConfig);
    ResultSet portResults = portTest.run(in);

    in.clear();

    Configuration denConfig(DenialOfService);
    denConfig.configParams.changeVal("Timeframe", "5");
    denConfig.configParams.changeVal("Possible attack message count", "2");
    denConfig.configParams.changeVal("Likely attack message count", "5");

    DenialOfServiceAnalyzer denialTest(denConfig);
    ResultSet denResults = denialTest.run(in);

    denResults.print(std::cout);
    std::cout << std::endl;
    portResults.print(std::cout);
    std::cout << std::endl;
    return 0;
}