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
    double average_WT;
    double average_TAT;
    vector<data1> Data;

    struct comp
    {
        bool operator()(pair<data1, int>& a, pair<data1, int>& b) 
        {
            if(a.first.BT == b.first.BT) return a.first.AT > b.first.AT;
            return a.first.BT > b.first.BT;  
        }
    };

    priority_queue<pair<data1, int>, vector<pair<data1, int>>, comp> pq;

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
            average_TAT = average_WT = 0;
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
            pq.push({Data[0], 0});
            int index = 1;
            while (!pq.empty())
            {
                auto p = pq.top(); pq.pop();
                auto task = p.first;
                int i = p.second;
                time = max(time, task.AT);
                time += task.BT;
                task.CT = time;
                Data[i] = task;

                while(index < n && Data[index].AT <= time) 
                {
                    pq.push({Data[index], index});
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
                average_TAT += Data[i].TAT;
                average_WT += Data[i].WT;
            }

            average_TAT /= (double) n;
            average_WT /= (double) n;
        }

        void display()
        {
            sort(Data.begin(), Data.end(), cmp1);

            cout<<endl;
            for (int i = 0; i < n; i++)
            {
                cout<<"Process : "<<Data[i].process<<'\t';
                cout<<"Arrival Time : "<<Data[i].AT<<'\t';
                cout<<"Burst Time : "<<Data[i].BT<<'\t';
                cout<<"Completion Time : "<<Data[i].CT<<'\t';
                cout<<"Waiting Time : "<<Data[i].WT<<'\t';
                cout<<"Turn Around Time : "<<Data[i].TAT<<'\t';
                cout<<endl;
            }
            cout<<"Average Waiting Time : "<<average_WT<<endl;
            cout<<"Average Turn Around Time : "<<average_TAT<<endl;
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
