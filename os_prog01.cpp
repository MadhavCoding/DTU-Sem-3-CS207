#include <bits/stdc++.h>
using namespace std;

struct data1
{
    int process;
    int AT, BT, CT, WT, TAT;
};

class FCFS
{
    int n;
    int time;
    vector<data1> Data;

    static bool cmp(data1 a, data1 b)
    {
        if(a.AT == b.AT) return true;
        else return a.AT < b.AT;
    }

    static bool cmp1(data1 a, data1 b)
    {
        return a.process < b.process;
    }

    public: 
        FCFS()
        {
            time = 0;
        }

        void getnum()
        {
            cout<<"Enter no. of Processes : ";
            cin>>n;
            Data.resize(n);
        }
        void getdata()
        {
            for (int i = 0; i < n; i++)
            {
                Data[i].process = i+1;
                cout<<"Process "<<Data[i].process<<endl;
                cout<<"Enter Arrival Time : ";
                cin>>Data[i].AT;
                cout<<"Enter Burst Time : ";
                cin>>Data[i].BT;
            }

            sort(Data.begin(), Data.end(), cmp);
        }

        void find_CT()
        {
            for (int i = 0; i < n; i++)
            {
                time = max(Data[i].AT, time);
                time += Data[i].BT;
                Data[i].CT = time;
            }
        }

        void find_WT_TAT()
        {
            find_CT();

            for (int i = 0; i < n; i++)
            {
                Data[i].TAT = Data[i].CT - Data[i].AT;
                Data[i].WT = Data[i].TAT - Data[i].BT;
            }
        }

        void display()
        {
            sort(Data.begin(), Data.end(), cmp1);

            cout<<endl;
            for (int i = 0; i < n; i++)
            {
                cout<<"Process : "<<Data[i].process<<endl;
                cout<<"Arrival Time : "<<Data[i].AT<<endl;
                cout<<"Burst Time : "<<Data[i].BT<<endl;
                cout<<"Completion Time : "<<Data[i].CT<<endl;
                cout<<"Waiting Time : "<<Data[i].WT<<endl;
                cout<<"Turn Around Time : "<<Data[i].TAT<<endl;
                cout<<endl;
            }
        }
};

int main(int argc, char const *argv[])
{
    FCFS fcfs1;
    fcfs1.getnum();
    fcfs1.getdata();
    fcfs1.find_WT_TAT();
    fcfs1.display();
    return 0;
}