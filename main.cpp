#include <iostream>
#include "PortScanAnalyzer.h"

int main()
{
    std::ifstream in("testInput.txt");
    if(in.fail())
    {
        std::cout << "File failed to open" << std::endl;
        return 1;
    }
    
    std::string input;
    ResultSet results;
    
    std::cout << "Welcome to the port scanner! Please enter the number of ports you think would constitute a possible attack: ";
    std::cin >> input;
    Configuration portConfig(PortScan);
    portConfig.configParams.changeVal("Possible attack port count", input);
    std::cout << "Please enter the number of ports that you think would almost certainly constitute an attack: ";
    std::cin >> input;
    portConfig.configParams.changeVal("Likely attack port count", input);
    PortScanAnalyzer analyzer(portConfig);
    std::cout << "Please input the relative path of the file containing the data you'd like to test (If the path fails, a default tester will be used instead): ";
    std::cin >> input;
    std::ifstream userInput(input);
    if(userInput.fail())
    {
        std::cout << "Path failed! Switching to default file" << std::endl;
        results = analyzer.run(in);
    }
    else
    {
        results = analyzer.run(userInput);
    }
    
    std::cout << "Printing the results..." << std::endl;
    results.print(std::cout);
    return 0;
}