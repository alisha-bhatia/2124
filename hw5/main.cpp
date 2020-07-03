#include <iostream>
#include <iomanip>
using namespace std;

class Time
{
    int day;
    int hour;
    int minute;

public:

    Time() : day(0), hour(0), minute(0) {}
    Time(int day, int hour, int minute) : day(day)
    {
        setHour(hour);
        setMinute(minute);
    }

    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }

    void setHour(int newHour)
    {
        if (newHour < 0)
        {
            newHour -= 24;
            day += newHour / 24;
            hour = (newHour % 24) + 24;
        }
        else
        {
            day += newHour / 24;
            hour = newHour % 24;
        }
    }

    void setMinute(int newMinute)
    {
        if (newMinute < 0)
        {
            newMinute -= 60;
            setHour(hour + newMinute / 60);
            minute = (newMinute % 60) + 60;
        }
        else
        {
            setHour(hour + newMinute / 60);
            minute = newMinute % 60;
        }
    }

    Time operator+(const Time & T1)
    {
        return Time(this->day + T1.day, this->hour + T1.hour, this->minute + T1.minute);
    }

    // todo operator-

    Time& operator++()	// pre-increment
    {
        setMinute(minute + 1);
        return *this;
    }

    Time operator++(int)	// post-increment
    {
        Time copy(*this);
        ++(*this);
        return copy;
    }

    // todo operator-- pre and post
};

ostream& operator<<(ostream& os, const Time& T1)
{
    os << setfill('0');
    os << T1.getHour() << ':' << setw(2) << T1.getMinute() << " (" << T1.getDay() << ")";
    return os;
}

int main()
{
    Time T1, T2(7, 30, -5);
    cout << T1 << endl;
    cout << T2 << endl;
    cout << endl;

    T2 = T2 + (++T1);
    cout << T1 << endl;
    cout << T2 << endl;
    cout << endl;

    T2 = T2 + (T1++);
    cout << T1 << endl;
    cout << T2 << endl;
    cout << endl;

    return 0;
}
