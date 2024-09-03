#include <bits/stdc++.h>
using namespace std;

struct data1
{
    int process;
    int AT, BT, CT, WT, TAT;
};

class SJF
{
    int n;
    int time;
    vector<data1> Data;

    struct comp
    {
        bool operator()(data1& a, data1& b) 
        {
            return a.BT > b.BT;  
        }
    };

    priority_queue<data1, vector<data1>, comp> pq;

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
        SJF()
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
            pq.push(Data[0]);
            int index = 1;
            while (!pq.empty())
            {
                auto task = (pq.top()); pq.pop();
                time = max(time, task.AT);
                time += task.BT;
                task.CT = time;
                Data[task.process - 1] = task;

                while(index < n && Data[index].AT <= time) 
                {
                    pq.push(Data[index]);
                    index++;
                }
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
    SJF sjf1;
    sjf1.getnum();
    sjf1.getdata();
    sjf1.find_WT_TAT();
    sjf1.display();
    return 0;
}
