#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

int pnum=0,lcmno,p[3][100],cap[3][100];

int lcm(int a[],int n);
int gcd(int a, int b);


class pro
{

    public:
        void get()
        {
            fstream file("Input Filellf_5.txt",ios::out | ios::in);
            int t1;
            string temp;

            while (!file.eof())
            {
                file>>temp>>t1>>temp>>p[0][pnum]>>temp>>p[1][pnum]>>temp>>p[2][pnum];
                pnum++;
            }
            pnum--;
            file.close();
            int temp1[100];//array to store periods
            for(int i=0;i<pnum;i++)
            {
                temp1[i]=p[2][i];
            }
            lcmno=lcm(temp1,pnum);
        }

        void display(void )
        {
        	int count;
        	cout<<"Process:";
        	for(count=1;count<=5;count++)
        	{
        		cout<<"\t"<<count;
			}
			cout<<"\n";
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<pnum;j++)
                {
                    if(j==0 && i==0)
                    {
                       cout<<"CPU TIME:\t"<<p[i][j]<<"\t";
                    }
                    else if(j==0 && i==1)
                    {
                        cout<<"Deadline:\t"<<p[i][j]<<"\t";
                    }
                    else if(j==0 && i==2)
                    {
                    	cout<<"Period:\t\t"<<p[i][j]<<"\t";
					}
                    
                    else
                    {
                        cout<<p[i][j]<<"\t";
                    }
                }
                cout<<"\n";
            }
            cout<<"LCM:"<<lcmno<<endl;
        }


        int check()
        {
            int i,n=pnum;
            float in=((float)1/(float)n);
            float u=((n)*(pow(2.0,((float)1/(float)n))-1));
            float ut=0;
            for(i=0;i<pnum;i++)
            {
               ut=ut+((float)p[0][i]/(float)p[2][i]);
            }
            cout<<"Utilization Bond:"<<u;
            cout<<"\nTotal Utilization Time:"<<ut;//utilization bond should be greater
            if(u>ut)
                return 1;
            else
                return 0;

        }
};

int priority();
void sch();

int lcm(int a[],int n)
{
    int ans = a[0];
    for (int i = 1; i < n; i++)
    {
        ans = (((a[i] * ans)) /(gcd(a[i], ans)));
    }
    return ans;
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int llf(int,int);
int priority(int t)
{
    int p=-1,lessp=1000;
    
        for(int i=0;i<pnum;i++)
        {
        	if(cap[0][i]!=0)
        	{
        		if(lessp>llf(i,t))
        		{
        			p=i;
        			lessp=llf(i,t);
				}
			}
        }
    return p;
}
int llf(int i,int t)
{
	int period=cap[2][i];
	int deadline=cap[1][i];
	int cpu=cap[0][i];
	int no=lcmno/period;
	int nrd;
	int k=0;
	int l;
	while(k*period<=t)
	{
		k++;
	}
	k--;
//	for(int j=0;j=no;j++)
//	{
		nrd=k*period + deadline;
		nrd=nrd-t;
//	}	
		l=nrd-cpu;
		return l;
}

void sch()
{
    fstream file("Output Filellf_5.txt",ios::out );
    int t,pr,i;
    for(i=0;i<pnum;i++)
    {
            cap[0][i]=p[0][i];
            cap[1][i]=p[1][i];
            cap[2][i]=p[2][i];
    }


    for(t=0;t<lcmno;t++)
    {
        for(i=0;i<pnum;i++)
        {
            if(cap[0][i]>cap[2][i])
            {
                cout<<"System is not scheduable\n";
                return;
            }
        }
        pr=priority(t);
        if(pr!=-1)
        {
            file<<t<<"-"<<t+1<<"|Process:"<<pr+1<<endl;
        }
        else
        {
            file<<t<<"-"<<t+1<<endl;
        }
        cap[0][pr]--;
        for(i=0;i<pnum;i++)
        {
            cap[2][i]--;
            if(cap[2][i]==0)
            {
                cap[0][i]=p[0][i];
                cap[1][i]=p[1][i];
                cap[2][i]=p[2][i];
            }
        }
    }
    file.close();
}



int main()
{
    pro ob1;

    ob1.get();
    ob1.display();
    int c=ob1.check();

    if(c==0)
    {
        cout<<"\nScheduling is not possible\n";
    }
    else
    {
        cout<<"\nScheduling is possible\n";
        sch();
    }

    return 0;
}



