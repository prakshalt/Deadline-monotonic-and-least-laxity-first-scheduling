#include<iostream>
#include<fstream>
using namespace std;
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>


int main()
{
    fstream file("Input File.txt",ios::out );
    int i,x;
    srand(time(0));

    for(i=0;i<5;i++)
    {
        file<<"Process: "<<i+1<<"\tCPU_Time: "<<rand()%5+1<<"\tDeadline: "<<rand()%20+1<<"\tPeriod: "<<10*((rand()%3)+1)<<endl;
    }
    file.close();
    return 0;

}
