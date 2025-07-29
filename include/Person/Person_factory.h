#include "Person.h"
#include "Account_Holder.h"
#include <vector>

class Person_factory
{
public:
    static Person *create_person(std::vector<std::string> argument_list)
    {
        Person *person = nullptr;
        if (argument_list[argument_list.size() - 1] == "AccountHolder")
        {
            person = new AccountHolder();
            person->setName(argument_list[1]);
            person->setAge(std::stoi(argument_list[2]));
            person->setPhone(argument_list[3]);
            person->setAddress(argument_list[4]);
        }
        return person;
    }
};