#include <bits/stdc++.h>
using namespace std;

class SCAN
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
            cout<<"Enter end position : ";
            cin>>end;
            cout<<"Enter initial Head position : ";
            cin>>head;
            cout<<"Enter no. of tracks : ";
            cin>>n;
            tracks.resize(n);

            cout<<"Enter Request Sequence : ";
            for (int i = 0; i < n; i++)
            {
                cin>>tracks[i];
            }

            total_seek = 0;
            avg_seek = 0;
        }

        void scheduling()
        {
            cout<<"Enter direction (L/R) : ";
            char dir; cin>>dir;

            vector<int> temporary = tracks;
            sort(tracks.begin(), tracks.end());

            if(dir == 'L')
            {
                int index = upper_bound(tracks.begin(), tracks.end(), head) - tracks.begin() - 1;
                int position = head;

                for(int i = index; i >= 0; i--)
                {
                    cout<<"Head moved from "<<position<<" to "<<tracks[i]<<endl;
                    total_seek += (abs(tracks[i] - position));
                    position = tracks[i];
                    sequence.push_back(tracks[i]);
                }
                if(position != 0) 
                {
                    cout<<"Head moved from "<<position<<" to "<<0<<endl;
                    total_seek += (abs(0 - position));
                    sequence.push_back(0);
                }
                position = 0;

                for(int i = index + 1; i < n; i++)
                {
                    cout<<"Head moved from "<<position<<" to "<<tracks[i]<<endl;
                    total_seek += (abs(tracks[i] - position));
                    position = tracks[i];
                    sequence.push_back(tracks[i]);
                }

                avg_seek = total_seek / n;
            }

            else if(dir == 'R')
            {
                int index = lower_bound(tracks.begin(), tracks.end(), head) - tracks.begin();
                int position = head;

                for(int i = index; i < n; i++)
                {
                    cout<<"Head moved from "<<position<<" to "<<tracks[i]<<endl;
                    total_seek += (abs(tracks[i] - position));
                    position = tracks[i];
                    sequence.push_back(tracks[i]);
                }
                if(position != end-1) 
                {
                    cout<<"Head moved from "<<position<<" to "<<end-1<<endl;
                    total_seek += (abs((end - 1) - position));
                    sequence.push_back(end - 1);
                }
                position = end-1;

                for(int i = index - 1; i >= 0; i--)
                {
                    cout<<"Head moved from "<<position<<" to "<<tracks[i]<<endl;
                    total_seek += (abs(tracks[i] - position));
                    position = tracks[i];
                    sequence.push_back(tracks[i]);
                }
            }

            else
            {
                cout<<"Invalid Input"<<endl;
            }

            tracks = temporary;
        }

        void display()
        {
            cout<<"Sequence : ";
            for (int i = 0; i < sequence.size(); i++)
            {
                cout<<sequence[i]<<" ";
            }   
            
            cout<<"Total Seek Time : "<<total_seek<<endl;
            cout<<"Average Seek Time : "<<avg_seek<<endl;
        }
};

int main(int argc, char const *argv[])
{
    SCAN scan;
    scan.get_data();
    scan.scheduling();
    scan.display();

    return 0;
}
