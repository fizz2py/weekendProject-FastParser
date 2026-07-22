#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <exception>

#include "parser.h"

int main()
{
    try
    {
        Parser parser;

        // Read CSV file
        parser.readCSV("data/sample.csv");

        // Get all parsed records
        const std::vector<Person>& people = parser.getPeople();

        // Create a new vector and reserve memory
        std::vector<Person> records;
        records.reserve(people.size());

        std::cout << "Reserved Capacity: "
                  << records.capacity() << std::endl;

        // Insert all records
        for (const auto& person : people)
        {
            records.push_back(person);
        }

        std::cout << "Final Size: "
                  << records.size() << std::endl;

        std::cout << "Final Capacity: "
                  << records.capacity() << std::endl;

        // Sort by:
        // 1. Salary (descending)
        // 2. Age (descending)
        // 3. ID (ascending)
        std::sort(records.begin(), records.end(),
            [](const Person& a, const Person& b)
            {
                if (a.salary != b.salary)
                    return a.salary > b.salary;

                if (a.age != b.age)
                    return a.age > b.age;

                return a.id < b.id;
            });

        std::cout << "\n===== Sorted Records =====\n";

        for (const auto& person : records)
        {
            std::cout
                << "ID: " << person.id
                << " | Name: " << person.name
                << " | Age: " << person.age
                << " | Salary: " << person.salary
                << std::endl;
        }

        // Simulate two data streams
        std::unordered_set<int> streamA;
        std::unordered_set<int> streamB;

        for (size_t i = 0; i < records.size(); ++i)
        {
            if (i % 2 == 0)
            {
                streamA.insert(records[i].id);
            }

            if (i % 3 == 0)
            {
                streamB.insert(records[i].id);
            }
        }

        // Find duplicate IDs
        std::cout << "\n===== Duplicate IDs =====\n";

        bool found = false;

        for (const auto& id : streamA)
        {
            if (streamB.find(id) != streamB.end())
            {
                std::cout << id << std::endl;
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "No duplicate IDs found." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: "
                  << e.what()
                  << std::endl;
        return 1;
    }

    return 0;
}