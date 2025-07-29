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

    // Getters
    string getName();
    int getAge();
    string printType();
    string getPhone();
    string getAddress();
    static int getCount();
    int getId();

    // Setters
    void setName(const string &name);
    void setAge(int age);
    void setType(const string &type);
    void setPhone(const string &phone);
    void setAddress(const string &address);
    void setId(int id);

    void get_common_inputs();

    virtual void get_specific_inputs() = 0;

    virtual void display_info() = 0;

    virtual ~Person();
};
#endif