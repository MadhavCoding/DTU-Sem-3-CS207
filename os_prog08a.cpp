#include <bits/stdc++.h>
using namespace std;

class LFU
{
    int page_frame;
    vector<int> slots;
    int page_fault;
    vector<int> q;
    int used;
    map<int, int> freq;

public:
    LFU()
    {
        page_fault = 0;
        used = 0;
    }

    void getdata()
    {
        cout << "Enter the no. of Page Frames : ";
        cin >> page_frame;
        slots.resize(page_frame, -1);
        q.resize(page_frame, -1);
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

            freq[x]++;

            bool found = false;
            for (int i = 0; i < page_frame; i++)
            {
                if (slots[i] == x)
                {
                    found = true;

                    int ind = 0;
                    for (; ind < page_frame; ind++)
                    {
                        if (q[ind] == x)
                            break;
                    }
                    for (int j = ind; j < page_frame - 1; j++)
                        q[j] = q[j + 1];

                    ind = page_frame - 2;
                    while (ind >= 0 && freq[q[ind]] > freq[x])
                    {
                        q[ind + 1] = q[ind];
                        ind--;
                    }
                    q[ind + 1] = x;
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
                            int ind = page_frame - 1;
                            while (ind >= 0 && (freq[q[ind]] > freq[x] || q[ind] == -1))
                            {
                                q[ind + 1] = q[ind];
                                ind--;
                            }
                            q[ind + 1] = x;
                            used++;
                            break;
                        }
                    }
                }

                else
                {
                    int previous = *q.begin();
                    for (int j = 0; j < page_frame - 1; j++)
                        q[j] = q[j + 1];

                    for (int i = 0; i < page_frame; i++)
                    {
                        if (slots[i] == previous)
                        {
                            slots[i] = x;
                            break;
                        }
                    }

                    int ind = page_frame - 2;
                    while (ind >= 0 && freq[q[ind]] > freq[x])
                    {
                        q[ind + 1] = q[ind];
                        ind--;
                    }
                    q[ind + 1] = x;
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
    LFU lfu;
    lfu.getdata();
    lfu.input();
    return 0;
}
