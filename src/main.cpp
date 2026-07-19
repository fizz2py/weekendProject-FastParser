#include "parser.h"
#include <iostream>

int main()
{
    try
    {
        Parser parser;

parser.readCSV("data/sample.csv");
parser.sortBySalary();
parser.displayData();
parser.writeCSV("output.csv");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}