#include <bits/stdc++.h>
using namespace std;

struct data1
{
    int process;
    int AT, BT, CT, WT, TAT, priority;
};

class Priority
{
    int n;
    int time;
    int time_quantum;
    double average_WT;
    double average_TAT;
    vector<data1> Data;

    struct comp
    {
        bool operator()(pair<pair<data1, int>, int> &a, pair<pair<data1, int>, int> &b)
        {
            if (a.first.first.priority == b.first.first.priority)
                return a.first.first.AT > b.first.first.AT;
            return a.first.first.priority > b.first.first.priority;
        }
    };

    priority_queue<pair<pair<data1, int>, int>, vector<pair<pair<data1, int>, int>>, comp> pq;

    static bool cmp(data1 a, data1 b)
    {
        return a.AT < b.AT;
    }

    static bool cmp1(data1 a, data1 b)
    {
        return a.process < b.process;
    }

public:
    Priority()
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
            cout << "Enter Priority : ";
            cin >> Data[i].priority;
        }

        sort(Data.begin(), Data.end(), cmp);
    }

    void find_CT()
    {
        pq.push({{Data[0], Data[0].BT}, 0});
        int index = 1;
        while (!pq.empty())
        {
            auto p = pq.top();
            pq.pop();
            auto task = p.first.first;
            int BT = p.first.second;
            int i = p.second;

            time = max(time, task.AT);

            int time_taken = min(time_quantum, BT);
            BT -= time_taken;
            time += time_taken;

            while (index < n && Data[index].AT <= time)
            {
                pq.push({{Data[index], Data[index].BT}, index});
                index++;
            }

            if (BT == 0)
            {
                task.CT = time;
                Data[i] = task;
            }
            else
                pq.push({{task, BT}, i});

            if (pq.empty() && index < n)
            {
                pq.push({{Data[index], Data[index].BT}, index});
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
        cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\t\tWaiting Time\tTurn Around Time" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << Data[i].process << "\t";
            cout << Data[i].AT << '\t' << '\t';
            cout << Data[i].BT << '\t' << '\t';
            cout << Data[i].priority << '\t' << '\t';
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
    Priority priority1;
    priority1.getnum();
    priority1.getdata();
    priority1.find_WT_TAT();
    priority1.display();
    return 0;
}
