#include <bits/stdc++.h>
using namespace std;

class FCFS
{
    int end;
    int head;
    int n;
    vector<int> tracks;
    int total_seek;
    double avg_seek;
    vector<int> sequence;

public:
    void get_data()
    {
        cout << "Enter end position : ";
        cin >> end;
        cout << "Enter initial Head position : ";
        cin >> head;
        cout << "Enter no. of tracks : ";
        cin >> n;
        tracks.resize(n);

        cout << "Enter Request Sequence : ";
        for (int i = 0; i < n; i++)
        {
            cin >> tracks[i];
        }

        total_seek = 0;
        avg_seek = 0;
    }

    void scheduling()
    {
        int position = head;

        for (int i = 0; i < n; i++)
        {
            cout << "Head moved from " << position << " to " << tracks[i] << endl;
            total_seek += (abs(tracks[i] - position));
            position = tracks[i];
            sequence.push_back(tracks[i]);
        }

        avg_seek = total_seek / n;
    }

    void display()
    {
        cout << "Sequence : ";
        for (int i = 0; i < sequence.size(); i++)
        {
            cout << sequence[i] << " ";
        }

        cout << "Total Seek Time : " << total_seek << endl;
        cout << "Average Seek Time : " << avg_seek << endl;
    }
};

int main(int argc, char const *argv[])
{
    FCFS fcfs;
    fcfs.get_data();
    fcfs.scheduling();
    fcfs.display();

    return 0;
}