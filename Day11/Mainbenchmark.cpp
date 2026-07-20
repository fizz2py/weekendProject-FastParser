#include "parser.h"
#include "person.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    try
    {
        const std::string dataPath = "data/sample.csv";

        std::cout << "Loading Person objects from " << dataPath << " ...\n";
        Parser parser;
        parser.readCSV(dataPath);
        const std::vector<Person>& people = parser.getPeople();
        std::cout << "Loaded " << people.size() << " records.\n\n";

        // --- Container Architecture: allocate both competing containers ---
        std::map<std::string, Person> orderedMap;              // Red-Black Tree
        std::unordered_map<std::string, Person> hashMap;       // Hash Table

        hashMap.reserve(people.size());

        // Populate both containers using std::for_each + lambda (no raw loops)
        std::for_each(people.begin(), people.end(),
            [&orderedMap, &hashMap](const Person& p)
            {
                orderedMap.emplace(p.name, p);
                hashMap.emplace(p.name, p);
            });

        std::cout << "std::map size:           " << orderedMap.size() << '\n';
        std::cout << "std::unordered_map size: " << hashMap.size() << "\n\n";

        // --- Build 100,000 random lookup keys drawn from the loaded records ---
        constexpr int kLookups = 100'000;
        std::vector<std::string> lookupKeys;
        lookupKeys.reserve(kLookups);

        std::mt19937 rng(42);
        std::uniform_int_distribution<size_t> dist(0, people.size() - 1);

        std::generate_n(std::back_inserter(lookupKeys), kLookups,
            [&]() { return people[dist(rng)].name; });

        // --- Benchmark std::map lookups ---
        volatile size_t mapHits = 0; // volatile to stop the compiler optimizing the loop away
        auto mapStart = std::chrono::high_resolution_clock::now();

        std::for_each(lookupKeys.begin(), lookupKeys.end(),
            [&orderedMap, &mapHits](const std::string& key)
            {
                if (orderedMap.find(key) != orderedMap.end())
                {
                    ++mapHits;
                }
            });

        auto mapEnd = std::chrono::high_resolution_clock::now();
        auto mapDuration = std::chrono::duration_cast<std::chrono::microseconds>(mapEnd - mapStart);

        // --- Benchmark std::unordered_map lookups ---
        volatile size_t hashHits = 0;
        auto hashStart = std::chrono::high_resolution_clock::now();

        std::for_each(lookupKeys.begin(), lookupKeys.end(),
            [&hashMap, &hashHits](const std::string& key)
            {
                if (hashMap.find(key) != hashMap.end())
                {
                    ++hashHits;
                }
            });

        auto hashEnd = std::chrono::high_resolution_clock::now();
        auto hashDuration = std::chrono::duration_cast<std::chrono::microseconds>(hashEnd - hashStart);

        // --- Results ---
        std::cout << std::fixed << std::setprecision(3);
        std::cout << "===== Benchmark Results (" << kLookups << " random lookups) =====\n";
        std::cout << "std::map (Red-Black Tree)        : "
                  << mapDuration.count() << " microseconds"
                  << "  (" << mapHits << " hits)\n";
        std::cout << "std::unordered_map (Hash Table)  : "
                  << hashDuration.count() << " microseconds"
                  << "  (" << hashHits << " hits)\n\n";

        if (hashDuration.count() > 0)
        {
            double speedup = static_cast<double>(mapDuration.count()) /
                              static_cast<double>(hashDuration.count());
            std::cout << "std::unordered_map was approximately " << speedup
                      << "x faster than std::map for these lookups.\n";
        }
    }
    catch (const std::exception& e)
{
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
}
}
