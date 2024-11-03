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
    double average_WT;
    double average_TAT;
    vector<data1> Data;

    queue<pair<pair<data1, int>, int>> q;

    static bool cmp(data1 a, data1 b)
    {
        return a.AT < b.AT;
    }

    static bool cmp1(data1 a, data1 b)
    {
        return a.process < b.process;
    }

public:
    RoundRobin()
    {
        time = 0;
        average_TAT = average_WT = 0;
    }

    void getnum()
    {
        cout << "Enter no. of Processes : ";
        cin >> n;
        Data.resize(n);
        cout << "Enter Time Quantum : ";
        cin >> time_quantum;
    }
    void getdata()
    {
        for (int i = 0; i < n; i++)
        {
            Data[i].process = i + 1;
            cout << "Process " << Data[i].process << endl;
            cout << "Enter Arrival Time : ";
            cin >> Data[i].AT;
            cout << "Enter Burst Time : ";
            cin >> Data[i].BT;
        }

        sort(Data.begin(), Data.end(), cmp);
    }

    void find_CT()
    {
        q.push({{Data[0], Data[0].BT}, 0});
        int index = 1;
        while (!q.empty())
        {
            auto p = q.front();
            q.pop();
            auto task = p.first.first;
            int BT = p.first.second;
            int i = p.second;

            time = max(time, task.AT);

            int time_taken = min(time_quantum, BT);
            BT -= time_taken;
            time += time_taken;

            while (index < n && Data[index].AT <= time)
            {
                q.push({{Data[index], Data[index].BT}, index});
                index++;
            }

            if (BT == 0)
            {
                task.CT = time;
                Data[i] = task;
            }
            else
                q.push({{task, BT}, i});

            if (q.empty() && index < n)
            {
                q.push({{Data[index], Data[index].BT}, index});
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

        average_TAT /= (double)n;
        average_WT /= (double)n;
    }

    void display()
    {
        sort(Data.begin(), Data.end(), cmp1);

        cout << endl;
        cout << "Process\tArrival Time\tBurst Time\tCompletion Time\t\tWaiting Time\tTurn Around Time" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << Data[i].process << "\t";
            cout << Data[i].AT << '\t' << '\t';
            cout << Data[i].BT << '\t' << '\t';
            cout << Data[i].CT << '\t' << '\t' << '\t';
            cout << Data[i].WT << '\t' << '\t';
            cout << Data[i].TAT << '\t' << '\t';
            cout << endl;
        }
        cout << "Average Waiting Time : " << average_WT << endl;
        cout << "Average Turn Around Time : " << average_TAT << endl;
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
