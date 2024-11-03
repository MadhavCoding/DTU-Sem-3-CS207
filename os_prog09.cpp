#include <bits/stdc++.h>
using namespace std;

class Semaphore
{
    int S;

public:
    void init(int x)
    {
        S = x;
    }

    void wait()
    {
        S--;
    }

    void signal()
    {
        S++;
    }

    int value()
    {
        return S;
    }
};

class Producer_Consumer
{
    int n;
    Semaphore mutex;
    Semaphore empty;
    Semaphore full;
    queue<int> q;

public:
    Producer_Consumer()
    {
        cout << "Enter size of Buffer : ";
        cin >> n;
        mutex.init(1);
        empty.init(n);
        full.init(0);
    }

    void Producer()
    {
        if (mutex.value() == 0 || empty.value() == 0)
        {
            cout << "Buffer is Full" << endl;
            return;
        }

        mutex.wait();
        empty.wait();

        int produced;
        cout << "Enter Produced Item : ";
        cin >> produced;
        q.push(produced);
        cout << "Item is Produced" << endl;

        mutex.signal();
        full.signal();
    }

    void Consumer()
    {
        if (full.value() == 0 || mutex.value() == 0)
        {
            cout << "Buffer is Empty" << endl;
            return;
        }

        full.wait();
        mutex.wait();

        int x = q.front();
        q.pop();
        cout << "Consumed Item : " << x << endl;
        cout << "Item is Consumed" << endl;

        mutex.signal();
        empty.signal();
    }
};

int main(int argc, char const *argv[])
{
    Producer_Consumer ps;

    while (true)
    {
        cout << "1. Producer \n2. Consumer \n3.Exit" << endl;
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            ps.Producer();
        }
        else if (choice == 2)
        {
            ps.Consumer();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Enter a Valid Input" << endl;
        }
    }

    return 0;
}
