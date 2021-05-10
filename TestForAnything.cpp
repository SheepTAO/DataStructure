#include <iostream>
using namespace std;
class CDate
{
public:
    int year;
    int month;
    int day;
    CDate(int y=0, int m=0, int d=0):year(y),month(m),day(d){}
    void input() {
        cin >> year >> month >> day;
    }
};
bool leap(int year)
{
    if(year%4==0 && year%100!=0 || year%400==0)
        return true;
    else
        return false;
}
int count_day(CDate &d, int flag)
{
    static int day_tab[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
    int p,i,s;
    if(leap(d.year))
    p=1;
    else
    p=0;
    if(flag)
    {
        s=d.day;
        for(i=1;i<d.month;i++)
        s+=day_tab[p][i-1];
        }
    else
    {
        s=day_tab[p][d.month]-d.day;
        for (i=d.month+1;i<=12;i++)
        s+=day_tab[p][i-1];
        }
    return(s);
}

int SubDay(CDate d1,CDate d2)
{
    int days,day1,day2,y;
    if(d1.year<d2.year)
    {
        days=count_day(d1,0);
        for(y=d1.year+1;y<d2.year;y++)
        if(leap(y))
        days+=366L;
        else
        days+=365L;
        days+=count_day(d2,1);
        }
    else if (d1.year==d2.year)
    {
        day1=count_day(d1,1);
        day2=count_day(d2,1);
        days=day2-day1;
        }
    else
    {
        days=count_day(d2,0);
        for(y=d2.year+1;y<d1.year;y++)
        if(leap(y))
        days+=366L;
        else
        days+=365L;
        days+=count_day(d1,1);
        }
    return days;
}
int main()
{
    CDate day1,day2;
    int  d;
    day1.input();
    day2.input();
    d=SubDay(day1,day2);    //两个日期相差的天数。
    cout<<d<<endl;
    return  0;
}
