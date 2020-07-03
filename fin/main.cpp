#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//q1

int findOccurrences(const char* cstr, char toFind) //assumption: pointer is to the first letter
{
    int count = 0;
    if (*cstr == '\0')
    {
        return 0; //base case
    }
    if (*cstr == toFind)
    {
        count += 1;
    }
    return count + findOccurrences(cstr + 1, toFind);
}

int main() {
    const char* cstring = "alisha";
    cout << findOccurrences(cstring,'a') <<endl;
    return 0;
}
