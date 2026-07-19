#include "person.h"

Person::Person()
    : id(0), name(""), age(0), salary(0.0)
{
}

Person::Person(int id, const std::string& name, int age, double salary)
    : id(id), name(name), age(age), salary(salary)
{
}