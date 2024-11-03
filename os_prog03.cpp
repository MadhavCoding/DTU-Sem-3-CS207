#include <bits/stdc++.h>
using namespace std;

struct memory_block
{
    int ID;
    int size;

    bool operator==(const memory_block &other)
    {
        return (ID == other.ID && size == other.size);
    }
};

struct data1
{
    int process;
    int AT;
    int size;
    memory_block memory_loc;
};

class memory_allocate
{
    int n, m;
    vector<data1> Data;
    vector<memory_block> memory;

    static bool cmp(data1 a, data1 b)
    {
        return a.AT < b.AT;
    }

    static bool cmp1(data1 a, data1 b)
    {
        return a.process < b.process;
    }

    static bool cmp2(memory_block m1, memory_block m2)
    {
        return m1.size > m2.size;
    }

public:
    void get_memory()
    {
        cout << "Enter no. of memory blocks : ";
        cin >> m;
        memory.resize(m);

        for (int i = 0; i < m; i++)
        {
            memory[i].ID = i + 1;
            cout << "Enter size of memory block " << i + 1 << " : ";
            cin >> memory[i].size;
        }
    }

    void getnum()
    {
        cout << "Enter no. of Processes : ";
        cin >> n;
        Data.resize(n);
    }

    void getdata()
    {
        for (int i = 0; i < n; i++)
        {
            Data[i].process = i + 1;
            cout << "Process " << Data[i].process << endl;
            cout << "Enter Arrival Time : ";
            cin >> Data[i].AT;
            cout << "Enter Size : ";
            cin >> Data[i].size;
        }

        sort(Data.begin(), Data.end(), cmp);
    }

    void display()
    {
        sort(Data.begin(), Data.end(), cmp1);

        cout << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "Process : " << Data[i].process << '\t';
            cout << "Arrival Time : " << Data[i].AT << '\t';

            if (Data[i].memory_loc.ID == -1)
            {
                cout << "No Memory Allocated" << '\t';
            }
            else
            {
                cout << "Memory Block ID : " << Data[i].memory_loc.ID << '\t';
                cout << "Memory Block Size : " << Data[i].memory_loc.size << '\t';
            }
            cout << endl;
        }
    }

    void Worst_Fit()
    {
        for (int i = 0; i < n; i++)
            Data[i].memory_loc.ID = -1;

        vector<memory_block> mem = memory;
        sort(mem.begin(), mem.end(), cmp2);
        int index = 0;

        for (int i = 0; i < n && index < m; i++)
        {
            if (mem[index].size >= Data[i].size)
            {
                Data[i].memory_loc = mem[index];
                index++;
            }
        }

        cout << "Worst Fit" << endl;
        display();
    }

    void Best_Fit()
    {
        for (int i = 0; i < n; i++)
            Data[i].memory_loc.ID = -1;

        vector<memory_block> mem = memory;
        sort(mem.begin(), mem.end(), cmp2);
        reverse(mem.begin(), mem.end());

        for (int i = 0; i < n; i++)
        {
            int low = 0, high = mem.size() - 1;
            while (low <= high)
            {
                int mid = low + (high - low) / 2;
                if (mem[mid].size >= Data[i].size)
                    high = mid - 1;
                else
                    low = mid + 1;
            }

            if (low != mem.size())
            {
                Data[i].memory_loc = mem[low];
                mem.erase(find(mem.begin(), mem.end(), mem[low]));
            }
        }

        cout << "Best Fit" << endl;
        display();
    }

    void First_Fit()
    {
        for (int i = 0; i < n; i++)
            Data[i].memory_loc.ID = -1;

        vector<memory_block> mem = memory;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < mem.size(); j++)
            {
                if (mem[j].size >= Data[i].size)
                {
                    Data[i].memory_loc = mem[j];
                    mem.erase(find(mem.begin(), mem.end(), mem[j]));
                    break;
                }
            }
        }

        cout << "First Fit" << endl;
        display();
    }
};

int main(int argc, char const *argv[])
{
    memory_allocate Memory;
    Memory.get_memory();
    Memory.getnum();
    Memory.getdata();
    Memory.Worst_Fit();
    Memory.Best_Fit();
    Memory.First_Fit();
    return 0;
}