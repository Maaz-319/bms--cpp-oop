#include "Person.h"
#include "../Utility/UI/Utility_UI.h"

#include <iostream>

int Person::count = 0;
Person::Person() : name(""), age(0), type("Person"), phone(""), address(""), id(-1) { count++; }

// Getters
string Person::getName() { return this->name; }
int Person::getAge() { return this->age; }
string Person::printType() { return this->type; }
string Person::getPhone() { return this->phone; }
string Person::getAddress() { return this->address; }
int Person::getCount() { return count; }
int Person::getId() { return this->id; }

// Setters
void Person::setName(const string &name) { this->name = name; }
void Person::setAge(int age) { this->age = age; }
void Person::setType(const string &type) { this->type = type; }
void Person::setPhone(const string &phone) { this->phone = phone; }
void Person::setAddress(const string &address) { this->address = address; }
void Person::setId(int id) { this->id = id; }

void Person::get_common_inputs(){
    this->setName(Utility_UI::take_string_input("Name"));
    this->setAge(Utility_UI::take_integer_input(18, 100, "Age"));
    this->setPhone(Utility_UI::take_phone_input());
    this->setAddress(Utility_UI::take_string_input("Address"));
}

Person::~Person()
{
    count--;
}