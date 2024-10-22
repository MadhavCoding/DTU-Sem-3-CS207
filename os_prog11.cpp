#include <bits/stdc++.h>
using namespace std;

class OPTIMAL
{
    int page_frame;
    vector<int> slots;
    int page_fault;

    struct Compare
    {
        bool operator()(const pair<int, int> &a, const pair<int, int> &b)
            const
        {
            return a.second < b.second;
        }
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    int used;
    vector<int> inputs;

public:
    OPTIMAL()
    {
        page_fault = 0;
        used = 0;
    }

    void getdata()
    {
        cout << "Enter the no. of Page Frames : ";
        cin >> page_frame;
        slots.resize(page_frame, -1);
    }

    void input()
    {
        while (1)
        {
            cout << "Enter Page Reference to be accessed (Enter -1 to exit) : ";
            int x;
            cin >> x;

            if (x == -1)
                break;

            inputs.push_back(x);
        }

        for (int index = 0; index < inputs.size(); index++)
        {
            int x = inputs[index];
            cout << "Input : " << x << endl;

            bool found = false;
            for (int i = 0; i < page_frame; i++)
            {
                if (slots[i] == x)
                {
                    found = true;
                    int ind = index + 1;
                    for (; ind < inputs.size(); ind++)
                        if (inputs[ind] == x)
                            break;

                    pq.push({x, ind});

                    break;
                }
            }

            if (!found)
            {
                page_fault++;

                if (used < page_frame)
                {
                    for (int i = 0; i < page_frame; i++)
                    {
                        if (slots[i] == -1)
                        {
                            slots[i] = x;

                            int ind = index + 1;
                            for (; ind < inputs.size(); ind++)
                                if (inputs[ind] == x)
                                    break;

                            pq.push({x, ind});

                            used++;
                            break;
                        }
                    }
                }

                else
                {
                    auto p = pq.top();
                    pq.pop();
                    int previous = p.first;

                    for (int i = 0; i < page_frame; i++)
                    {
                        if (slots[i] == previous)
                        {
                            slots[i] = x;

                            int ind = index + 1;
                            for (; ind < inputs.size(); ind++)
                                if (inputs[ind] == x)
                                    break;

                            pq.push({x, ind});

                            break;
                        }
                    }
                }
            }

            cout << "Page Fault = " << page_fault << endl;
            cout << "Page Frames" << endl;
            for (int i = 0; i < page_frame; i++)
            {
                cout << slots[i] << " ";
            }
            cout << endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    OPTIMAL optimal;
    optimal.getdata();
    optimal.input();
    return 0;
}