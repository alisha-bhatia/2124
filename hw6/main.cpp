#include <iostream>
#include <string>
#include <iostream>
using namespace std;

// The StringSet class does not permit duplicate strings,
// much like a typical "set".
class StringSet
{
private:

    string* arr;
    size_t size;
    size_t capacity;

    size_t find(const string&) const;

public:

    StringSet(string arr[], size_t size);
    StringSet(const StringSet&);
    ~StringSet();

    StringSet& operator= (const StringSet&);

    void add_string_to_set(const string&);
    // Only adds if argument is not a duplicate of a string already in the set.
    void remove_string_from_set(const string&);

    bool contains(const string&) const;

    void clear();

    size_t get_size() const;

    void print() const;

    StringSet operator+ (const StringSet&) const;
    StringSet operator* (const StringSet&) const;

};

int main()
{
    string test_arr[] = { "Hi", "Go", "Ha", "Ugh", "Ha", "He" };
    string test_arr3[] = { "Go", "Ho", "He", "Ugh", "Hi","Alisha" };

    StringSet Set1(test_arr, sizeof(test_arr) / sizeof(string));
    StringSet Set3(test_arr3, sizeof(test_arr3) / sizeof(string));

    cout << "Set1 = ";
    Set1.print();
    cout << "\nSet3 = ";
    Set3.print();

    StringSet Set5 = Set1 + Set3;
    cout << "\nSet1 union Set3 = ";
    Set5.print();

    StringSet Set4 = Set1 * Set3;
    cout << "\nSet1 intersect Set3 = ";
    Set4.print();

    StringSet Set2(Set1);
    cout << "\nSet2 (copy-constructed from Set1) = ";
    Set2.print();

    Set1.remove_string_from_set("Hi");
    Set1.remove_string_from_set("Ho");
    cout << "\nSet1 after removing \"Hi\" and \"Ho\" = ";
    Set1.print();

    Set2.remove_string_from_set("Go");
    Set2.remove_string_from_set("Ugh");
    cout << "\nSet2 after removing \"Go\" and \"Ugh\" = ";
    Set2.print();

    Set1.clear();
    cout << "\nSet1 after clearing = ";
    Set1.print();

    Set1.add_string_to_set("Yeah");
    cout << "\nSet1 after adding \"Yeah\" = ";
    Set1.print();

    Set2 = Set1;
    cout << "\nSet2 after copy assignment from Set1 = ";
    Set2.print();

    return 0;
}



StringSet::StringSet(string arr[], size_t size)
{
    this->arr = new string[size];
    capacity = size;
    this->size = 0;

    for (size_t i = 0; i < size; ++i)
        add_string_to_set(arr[i]);
}

StringSet::StringSet(const StringSet& SS)
        : arr(nullptr), size(0), capacity(0)
{
    *this = SS;	// Calls the assignment operator
}

StringSet::~StringSet()
{
    clear();
}

StringSet& StringSet::operator= (const StringSet& SS)
{
    if (capacity < SS.size)
    {
        clear();
        capacity = SS.size;
        arr = new string[capacity];
    }
    size = SS.size;

    // Copy all strings from SS to this
    for (size_t i = 0; i < size; ++i)
        arr[i] = SS.arr[i];

    // Empty the strings in any extra cells of this
    for (size_t i = size; i < capacity; ++i)
        arr[i].clear();

    return *this;
}

// Only adds if argument is not a duplicate of a string already in the set.
void StringSet::add_string_to_set(const string& str)
{
    // First check for duplicate of str already in the array
    if (contains(str))
        return;

    // If not a duplicate, then add the new string
    if (size == capacity)
    {
        if (capacity == 0)
            capacity = 1;

        string* temp = new string[capacity *= 2];

        for (size_t i = 0; i < size; ++i)
            temp[i] = arr[i];

        delete[] arr;
        arr = temp;
    }
    arr[size] = str;
    ++size;
}

void StringSet::remove_string_from_set(const string& str)
{
    size_t i = find(str);

    if (i == size)
        return;	// Didn't find str, so nothing to remove

    // Move the last element into the ith position
    arr[i] = arr[--size];
    arr[size].clear();
}

size_t StringSet::find(const string& str) const
{
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] == str)
            return i;
    }
    return size;
}

bool StringSet::contains(const string& str) const
{
    return find(str) != size;
}

void StringSet::clear()
{
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}

size_t StringSet::get_size() const
{
    return size;
}

void StringSet::print() const
{
    cout << "{";
    if (size > 0)
    {
        cout << arr[0];
        for (size_t i = 1; i < size; ++i)
            cout << ", " << arr[i];
    }
    cout << "}";
}

StringSet StringSet::operator+ (const StringSet& SS) const
{
    StringSet unioned(*this);

    for (size_t w = 0; w < SS.size; ++w)
        unioned.add_string_to_set(SS.arr[w]);

    return unioned;
}

StringSet StringSet::operator* (const StringSet& SS) const
{
    StringSet intersection(*this);

    for (size_t i = 0; i < intersection.size; )
    {
        if (SS.contains(intersection.arr[i]))
            ++i;
        else
            intersection.remove_string_from_set(intersection.arr[i]);
    }

    return intersection;
}

// this:	["A"]["B"]["C"]["D"]["E"]
// SS:		["F"]["G"]["D"]["H"]["A"]

// return:  ["A"]["D"]

// copy this:	["A"]["B"]["C"]["D"]["E"]