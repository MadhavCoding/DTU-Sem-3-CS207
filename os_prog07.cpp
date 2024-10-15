#include <bits/stdc++.h>
using namespace std;

class Bankers_Algorithm_Avoidance
{
    vector<int> available;
    vector<vector<int>> maximum;
    vector<vector<int>> allocation;
    vector<vector<int>> need;

    int processes, resources;

    void calculate_need()
    {
        for (int i = 0; i < processes; i++)
        {
            for (int j = 0; j < resources; j++)
            {
                need[i][j] = maximum[i][j] - allocation[i][j];
            }
        }
    }

public:
    void display_allocation()
    {
        cout << "Allocation Matrix" << endl;
        for (int i = 0; i < processes; i++)
        {
            for (int j = 0; j < resources; j++)
            {
                cout << allocation[i][j] << " ";
            }
            cout << endl;
        }
    }

    void display_maximum()
    {
        cout << "Maximum Matrix" << endl;
        for (int i = 0; i < processes; i++)
        {
            for (int j = 0; j < resources; j++)
            {
                cout << maximum[i][j] << " ";
            }
            cout << endl;
        }
    }

    void display_need()
    {
        cout << "Need Matrix" << endl;
        for (int i = 0; i < processes; i++)
        {
            for (int j = 0; j < resources; j++)
            {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }
    }

    void getnum()
    {
        cout << "Enter number of processes : ";
        cin >> processes;
        cout << "Enter numnber of resources : ";
        cin >> resources;

        available.resize(resources);
        maximum.resize(processes, vector<int>(resources));
        allocation.resize(processes, vector<int>(resources));
        need.resize(processes, vector<int>(resources));
    }

    void getdata()
    {
        cout << "Enter the available resources for each type" << endl;
        for (int i = 0; i < resources; i++)
        {
            cout << "Resource " << i + 1 << " : ";
            cin >> available[i];
        }

        cout << "Enter the maximum demand matrix : " << endl;
        for (int i = 0; i < processes; i++)
        {
            cout << "Process " << i + 1 << " : " << endl;
            for (int j = 0; j < resources; j++)
            {
                cout << "Resource " << j + 1 << " : ";
                cin >> maximum[i][j];
            }
        }

        cout << "Enter the allocation matrix : " << endl;
        for (int i = 0; i < processes; i++)
        {
            cout << "Process " << i + 1 << " : " << endl;
            for (int j = 0; j < resources; j++)
            {
                cout << "Resource " << j + 1 << " : ";
                cin >> allocation[i][j];
            }
        }

        calculate_need();

        display_allocation();
        display_maximum();
        display_need();
    }

    // Check if a process can be safely allocated resources
    bool can_allocate(int process, vector<int> &work)
    {
        for (int i = 0; i < resources; i++)
        {
            if (need[process][i] > work[i])
            {
                return false;
            }
        }
        return true;
    }

    // Function to check if the system is in a safe state
    bool isSafe()
    {
        vector<int> work = available;
        vector<bool> finish(processes, false);
        vector<int> safe_sequence;

        for (int count = 0; count < processes; count++)
        {
            for (int i = 0; i < processes; i++)
            {
                if (!finish[i] && can_allocate(i, work))
                {
                    for (int j = 0; j < resources; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safe_sequence.push_back(i + 1);
                    finish[i] = true;
                }
            }
        }

        bool found = true;
        for (int i = 0; i < processes; i++)
        {
            if (!finish[i])
            {
                found = false;
                break;
            }
        }

        if (!found)
        {
            cout << "System is not in a Safe State" << endl;
            return false;
        }

        cout << "System is in a Safe State" << endl;
        cout << "Safe Sequence : ";
        for (int i = 0; i < safe_sequence.size(); i++)
        {
            cout << safe_sequence[i] << " ";
        }
        cout << endl;
        return true;
    }

    // Request resources for a process
    bool request_resources(int process, vector<int> request)
    {
        for (int i = 0; i < resources; i++)
        {
            if (request[i] > need[process][i])
            {
                cout << "Error: Process has exceeded its maximum claim" << endl;
                return false;
            }
            if (request[i] > available[i])
            {
                cout << "Resources not available" << endl;
                return false;
            }
        }

        // Tentatively allocate the resources
        for (int i = 0; i < resources; i++)
        {
            available[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }

        // Check if the system remains in a safe state
        if (isSafe())
        {
            cout << "Resources allocated successfully." << endl;

            display_allocation();
            display_maximum();
            display_need();

            return true;
        }
        else
        {
            // Rollback allocation
            for (int i = 0; i < resources; i++)
            {
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }
            cout << "Resources Allocation leads to an Unsafe State." << endl;
            return false;
        }
    }

    void take_request()
    {
        int process;
        vector<int> request(resources);
        while (true)
        {
            cout << "Enter the process number making a request (Enter -1 to exit) : ";
            cin >> process;

            if (process == -1)
                break;

            process--;
            cout << "Enter the resource request for each type : " << endl;
            for (int i = 0; i < resources; i++)
            {
                cout << "Resource " << i + 1 << " : ";
                cin >> request[i];
            }

            request_resources(process, request);
        }
    }
};

int main(int argc, char const *argv[])
{
    Bankers_Algorithm_Avoidance ba;
    ba.getnum();
    ba.getdata();

    ba.take_request();
    return 0;
}
