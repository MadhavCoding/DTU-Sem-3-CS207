#include <bits/stdc++.h>
using namespace std;

class LRU
{
    int page_frame;
    vector<int> slots;
    int page_fault;
    vector<int> q;
    int used;

    struct comp
    {
        bool operator()(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
        {
            if (a.second.second == b.second.second)
                return a.second.first > b.second.first;
            return a.second.second > b.second.second;
        }
    };

public:
    LRU()
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

            bool found = false;
            for (int i = 0; i < page_frame; i++)
            {
                if (slots[i] == x)
                {
                    found = true;

                    auto it = find(q.begin(), q.end(), x);
                    if (it != q.end())
                        q.erase(it);
                    q.push_back(x);

                    break;
                }
            }

            if (!found)
            {
                page_fault++;
                q.push_back(x);

                if (used < page_frame)
                {
                    for (int i = 0; i < page_frame; i++)
                    {
                        if (slots[i] == -1)
                        {
                            slots[i] = x;
                            used++;
                            break;
                        }
                    }
                }

                else
                {
                    int previous = *q.begin();
                    q.erase(q.begin());

                    for (int i = 0; i < page_frame; i++)
                    {
                        if (slots[i] == previous)
                        {
                            slots[i] = x;
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
    LRU lru;
    lru.getdata();
    lru.input();
    return 0;
}
