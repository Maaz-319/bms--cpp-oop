#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person
{
private:
    static int count;

protected:
    int id;
    string name;
    int age;
    string type;
    string phone;
    string address;

public:
    Person();
    virtual void printDetails() = 0;

    // Getters
    virtual string getName();
    virtual int getAge();
    virtual string printType();
    virtual string getPhone();
    virtual string getAddress();
    static int getCount();
    virtual int getId();

    // Setters
    virtual void setName(const string &name);
    virtual void setAge(int age);
    virtual void setType(const string &type);
    virtual void setPhone(const string &phone);
    virtual void setAddress(const string &address);
    virtual void setId(int id);

    // virtual void get_common_inputs();
    // virtual void get_specific_inputs() = 0;

    virtual ~Person();
};
#endif