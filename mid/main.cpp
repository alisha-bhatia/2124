#include <iostream>
#include <vector>
//midterm q1
using namespace std;

/// Phone Number
class PhoneNumber
{
    string type;
    int number;
public:
    PhoneNumber(string type, int number) : number(number), type(type){}
    void set_number(int num_given){this -> number = num_given;}
    void set_type(string type_given){this -> type = type_given;}
    int get_number(){return number;}
    string get_type() {return type;}

};

///Person
class Person
        {
    string name;
    vector <PhoneNumber> phone_nums;


public:
    Person() {}
    Person ( string name): name(name){}
    string get_name(){return this-> name;}
    void addNumber(PhoneNumber const phoneNumber) { phone_nums.push_back(phoneNumber);}
    int search_byType (string type);
    string search_byNumber(int num);
};

int Person::search_byType(string type)
{
    for (int i = 0; i<phone_nums.size(); i++)
    {
        if (phone_nums[i].get_type() == type)
        {
            return phone_nums[i].get_number();
        }
    }
    return -1;
}

string Person::search_byNumber(int num)
{
    for (int i = 0; i<phone_nums.size(); i++)
    {
        if (phone_nums[i].get_number() == num)
        {
            return phone_nums[i].get_type();
        }
    }
    return "";
}




//// Phonebook
class PhoneBook{
    vector <Person> people;
public:
    void add_person (string name, string num_type, int number);
    Person search_person (string name);
    Person search_number (int number);

};

void PhoneBook :: add_person(string name, string num_type, int number)
{
    people.push_back(Person(name));
    people.back().addNumber(PhoneNumber(num_type,number));
}

Person PhoneBook :: search_person(string name)
{
    for (int i=0; i<people.size(); i++)
    {
        if(people[i].get_name() == name)
        {
            return people[i];
        }
    }
    return Person();
}
Person PhoneBook :: search_number(int number)
{
    for (int i=0; i<people.size(); i++)
    {
        if(people[i].search_byNumber(number) != "")
        {
            return people[i];
        }
    }
    return Person();
}

//// main
int main()
{
    PhoneBook book_name;
    book_name.add_person("alisha", "mobile", 1234);
    book_name.add_person("rachel", "home", 3112);
    book_name.add_person("milo", "work", 1234);
    Person person_searched;
    person_searched = book_name.search_person("alisha");
    cout << person_searched.get_name() << endl;
    Person number_searched;
    number_searched = book_name.search_number(3112);
    cout << number_searched.get_name() << endl;

    PhoneNumber number("work", 3122);
    cout<< number.get_number() << endl;
    cout<< number.get_type() << endl;

    Person person_given;
    person_given.addNumber(number);
    cout << person_given.search_byType("work") << endl;




    return 0;
}
