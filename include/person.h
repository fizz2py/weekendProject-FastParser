#pragma once

#include <string>

class Person
{
public:
    int id;
    std::string name;
    int age;
    double salary;

    Person();
    Person(int id, const std::string& name, int age, double salary);
};