#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "parser.h"

int main()
{
    try
    {
        Parser parser;
        parser.readCSV("data/sample.csv");

        std::vector<Person> records = parser.getPeople();

        std::cout << "Loaded Records: "
                  << records.size()
                  << "\n\n";

        // -----------------------------
        // In-place transformation
        // Increase salary by 10%
        // -----------------------------
        std::transform(
            records.begin(),
            records.end(),
            records.begin(),
            [](Person person)
            {
                person.salary *= 1.10;
                return person;
            });

        // -----------------------------
        // Measure filtering time
        // -----------------------------
        auto start = std::chrono::high_resolution_clock::now();

        records.erase(
            std::remove_if(
                records.begin(),
                records.end(),
                [](const Person& person)
                {
                    return person.age <= 0 ||
                           person.salary <= 0;
                }),
            records.end());

        auto end = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(
                end - start);

        std::cout << "Filtering Time: "
                  << duration.count()
                  << " microseconds\n";

        std::cout << "Valid Records: "
                  << records.size()
                  << "\n\n";

        // -----------------------------
        // Create lookup table
        // -----------------------------
        std::unordered_map<int, std::reference_wrapper<Person>> lookup;

        for (auto& person : records)
        {
            lookup.emplace(person.id, person);
        }

        // -----------------------------
        // Display first 10 records
        // -----------------------------
        std::cout << "First 10 Records\n\n";

        size_t count = 0;

        for (const auto& person : records)
        {
            std::cout
                << "ID: " << person.id
                << " | Name: " << person.name
                << " | Age: " << person.age
                << " | Salary: " << person.salary
                << '\n';

            ++count;

            if (count == 10)
                break;
        }

        // -----------------------------
        // Demonstrate lookup
        // -----------------------------
        if (!records.empty())
        {
            int searchId = records.front().id;

            auto it = lookup.find(searchId);

            if (it != lookup.end())
            {
                std::cout << "\nLookup Successful\n";
                std::cout
                    << "ID: " << it->second.get().id
                    << " | Name: " << it->second.get().name
                    << '\n';
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}