#include <bits/stdc++.h>
using namespace std;

class FIFO
{
    int page_frame;
    vector<int> slots;
    int page_fault;
    queue<int> q;
    int used;

public:
    FIFO()
    {
        page_fault = 0;
        used = 0;
    }

    void getdata()
    {
        cout<<"Enter the no. of Page Frames : ";
        cin>>page_frame;
        slots.resize(page_frame, -1);
    }

    void input()
    {
        while (1)
        {
            cout<<"Enter Page Reference to be accessed (Enter -1 to exit) : ";
            int x;
            cin>>x;

            if(x == -1) break;

            bool found = false;
            for(int i = 0; i < page_frame; i++)
            {
                if(slots[i] == x) 
                {
                    found = true;
                    break;
                }
            }

            if(!found)
            {
                page_fault++;

                q.push(x);

                if(used < page_frame)
                {
                    for (int i = 0; i < page_frame; i++)
                    {
                        if(slots[i] == -1)
                        {
                            slots[i] = x;
                            used++;
                            break;
                        }
                    }
                }

                else
                {
                    int previous = q.front(); q.pop();

                    for (int i = 0; i < page_frame; i++)
                    {
                        if(slots[i] == previous)
                        {
                            slots[i] = x;
                            break;
                        }
                    }
                }
            }

            cout<<"Page Fault = "<<page_fault<<endl;
            cout<<"Page Frames"<<endl;
            for (int i = 0; i < page_frame; i++)
            {
                cout<<slots[i]<<" ";
            }
            cout<<endl;
            
        }
    }
};

int main(int argc, char const *argv[])
{
    FIFO fifo;
    fifo.getdata();
    fifo.input();
    return 0;
}