#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//question 1
void reverse (char * front) // no const because needs to modify letters- by knowing address of first-
// you can access entire string
{
    char * rear = front;
    while(*rear != '\0')// null character would hold a char-- hypothetically
    {
        rear++; //*rear- would be accessing the letter, need to increase the address location
    }
    rear--;
    while(front<rear)// addresses are stored in increasing order--- this works
    {
        char temp = *front;
        *front = * rear;
        *rear = temp;
        front++;
        rear--;
    }

}
//question 2
void enlarge(int*& array, int size, int new_num)
{
    int* new_array = new int[size + 1];
    int x = 0;
    bool check = true;
    for (int i = 0; i < size; i++)
    {
        if (new_num > array[i] or new_num < array[i] or !check)
        {
            new_array[x] = array[i];
        }
        else if (check) {
            new_array[x] = new_num;
            new_array[x + 1] = array[i];
            x++;

            check = false;
        }
        x++;
    }
    for (int i = 0; i < size + 1; i++)
    {
        cout << new_array[i] << " " << endl;
    }
}

//question 3
void histogram()
{
    int max;
    int input;
    vector <int> numbers;
    cout<< "enter numbers, press -1 to end"<<endl;
    while(input != -1)
    {
        cin >>input;
        numbers.push_back(input);
    }
    numbers.pop_back();
    for (int i =0; i<numbers.size();i++)
    {
        max = numbers[0];
        if (numbers[i] > numbers[0])
        {
            max = numbers[i];
        }
        //cout<<numbers[i]<<endl;
    }
    //cout<< max<<endl;
    int * arr = new int[max+1];
    for (int i=0; i< numbers.size();i++)
    {
        arr[numbers[i]]+=1;
    }
    for (int i=0; i< max+1; i++)
    {
        if ( arr[i]>0)
        {
            cout << "Number of " << i << "'s " << arr[i]<< endl;
        }
    }

}






int main() {
    char array[] = "alisha";
    reverse(array);
    cout<<array<< endl;
   // histogram();


}
