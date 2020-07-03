#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
//q1
bool isInVector (const vector <int> &v, int num ) //
// & sign is important bc pass by ref-- can change v if needed
{
    bool ans = false;
    int num_given = num;
    for (int i = 0; i< v.size(); i++)
    {
        if (v[i] == num_given)
        {
            ans = true;
        }
    }
    return ans;
}
vector<int>  makeUnique (const vector <int> &v)
{
    vector <int> wo_duplicates;
    for (int i = 0; i< v.size(); i++) // only need 1 loop because wo_duplicates will always be smaller
    {
            if (!(isInVector (wo_duplicates,v[i]) ))
            {
                wo_duplicates.push_back(v[i]);
            }
    }
    return wo_duplicates;
}
vector<int> fillVecFromFile (vector <int> v)
{
    string filename;
    cout <<"Enter file name" << endl;
    getline (cin, filename);

    ifstream input(filename);
    if (!input.is_open())
    {
        cout <<"cannot open the file"<<endl;
    }
    int val;
    while(input >> val)
    {
        v.push_back(val);
    }
    return v;

}
void writetofile(const vector <int> &v,string filename)
{
    cout <<"Enter file name" << endl;
    getline (cin, filename);

    ofstream output(filename);

    if (!output.is_open())
    {
        cout <<"cannot open the file"<<endl;
    }
    for (int i = 0; i< v.size(); i++)
    {
        output << v[i] << endl;
    }

}

int main()
{

    vector <int> fin_v;

    vector <int> vv = makeUnique(fillVecFromFile(fin_v));
    writetofile(vv, "unique.ints");

}
