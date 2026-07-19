#pragma once

#include <vector>
#include <string>
#include "person.h"

class Parser
{
private:
    std::vector<Person> people;

public:
    void readCSV(const std::string& filename);
    void displayData() const;
    void sortBySalary();
void writeCSV(const std::string& filename) const;
};