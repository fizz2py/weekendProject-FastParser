#include "parser.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

void Parser::readCSV(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        throw std::runtime_error("Failed to open file.");
    }

    std::string line;

    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string id;
        std::string name;
        std::string age;
        std::string salary;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, age, ',');
        std::getline(ss, salary, ',');

        Person person(
            std::stoi(id),
            name,
            std::stoi(age),
            std::stod(salary)
        );

        people.push_back(std::move(person));
    }

    file.close();
}

void Parser::displayData() const
{
    for (const auto& person : people)
    {
        std::cout
            << person.id << " "
            << person.name << " "
            << person.age << " "
            << person.salary << '\n';
    }
}

void Parser::sortBySalary()
{
    std::sort(people.begin(), people.end(),
        [](const Person& a, const Person& b)
        {
            return a.salary > b.salary;
        });
}

const std::vector<Person>& Parser::getPeople() const
{
    return people;
}

void Parser::writeCSV(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file)
    {
        throw std::runtime_error("Failed to create output file.");
    }

    file << "ID,Name,Age,Salary\n";

    for (const auto& person : people)
    {
        file << person.id << ","
             << person.name << ","
             << person.age << ","
             << person.salary << "\n";
    }

    file.close();
}