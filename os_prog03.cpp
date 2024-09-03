#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct data1
{
    int process;
    int AT, BT, CT, WT, TAT;
};

class RoundRobin
{
    int n;
    int time;
    int time_quantum;
    vector<data1> Data;

    queue<pair<data1, int>> q;

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
        RoundRobin()
        {
            time = 0;
        }

        void getnum()
        {
            cout<<"Enter no. of Processes : ";
            cin>>n;
            Data.resize(n);
            cout<<"Enter Time Quantum : ";
            cin>>time_quantum;
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
            q.push({Data[0], Data[0].BT});
            int index = 1;
            while (!q.empty())
            {
                auto p = q.front(); q.pop();
                auto task = p.first;
                int BT = p.second;

                time = max(time, task.AT);

                int time_taken = min(time_quantum, BT);
                BT -= time_taken;
                time += time_taken;

                while(index < n && Data[index].AT <= time) 
                {
                    q.push({Data[index], Data[index].BT});
                    index++;
                }

                if(BT == 0)
                {
                    task.CT = time;
                    Data[task.process - 1] = task;
                }
                else q.push({task, BT});
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
    RoundRobin roundrobin1;
    roundrobin1.getnum();
    roundrobin1.getdata();
    roundrobin1.find_WT_TAT();
    roundrobin1.display();
    return 0;
}
