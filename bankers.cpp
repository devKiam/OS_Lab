#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int no_of_processes, no_of_resource_types;

    cout << "Number of process: " << endl;
    cin >> no_of_processes;
    cout << "Number of resource types: " << endl;
    cin >> no_of_resource_types;

    vector<int> instances;
    cout << "Resource types instances: " << endl;
    for (int i = 0; i < no_of_resource_types; i++)
    {
        int n; cin >> n;
        instances.push_back(n);
    }

    vector< vector<int> > allocation;
    cout << "Allocation: " << endl;
    for (int i = 0; i < no_of_processes; i++)
    {
        vector<int> row;
        for (int j=0; j<no_of_resource_types; j++)
        {
            int n; cin >> n;
            row.push_back(n);
        }
        allocation.push_back(row);
    }

    vector< vector<int> > max;
    cout << "Max: " <<endl;
    for (int i = 0; i < no_of_processes; i++)
    {
        vector<int> row;
        for (int j=0; j<no_of_resource_types; j++)
        {
            int n; cin >> n;
            row.push_back(n);
        }
        max.push_back(row);
    }

    vector<int> available;
    for (int i = 0; i < no_of_resource_types; i++)
    {
        int total = 0;
        for (int j = 0; j < allocation.size(); j++)
        {
            total += allocation[j][i];
        }
        available.push_back( instances[i] - total );
    }
    cout << "Available: " <<endl;
    for (int i = 0; i < available.size(); i++)
    {
        cout << available[i] << " ";
    }
    cout << endl;

    vector< vector<int> > need;
    for (int i = 0; i < no_of_processes; i++)
    {
        vector<int> row;
        for (int j=0; j < no_of_resource_types; j++)
        {
            row.push_back( max[i][j] - allocation[i][j] );
        }
        need.push_back(row);
    }
    cout << "Need: " << endl;
    for (int i = 0; i < need.size(); i++)
    {
        for (int j = 0; j < need[i].size(); j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    vector<int> request;
    int request_i;
    cout << "request i :" << endl;
    cin >> request_i;
    cout << "request instance of resource type values: " << endl;
    for (int i = 0; i < no_of_resource_types; i++)
    {
        int n; cin >> n;
        request.push_back(n);
    }

    // resource request algorithm
    // step 1 : request_i <= need_i
    bool terminate = false;
    for (int i = 0; i < no_of_resource_types; i++)
    {
        if ( request[i] <= need[request_i][i] )
            continue;
        else
        {
            cout << "Error! The process has exceed its maximum claim" << endl;
            terminate = true;
            break;
        }
    }
    // step 2 : request_i <= available_i
    if (!terminate)
    {
        for (int i = 0; i < no_of_resource_types; i++)
        {
            if ( request[i] <= available[i] )
                continue;
            else {
                cout << "Error! the process must wait, since the resources are not available." << endl;
                terminate = true;
                break;
            }
        }
    }
    if (terminate)
        exit(0);
    // step 3 : new available, allocation, need
    for (int i = 0; i < available.size(); i++)
    {
        available[i] = available[i] - request[i];
    }
    for (int i = 0; i < allocation[request_i].size(); i++)
    {
        allocation[request_i][i] = allocation[request_i][i] + request[i];
    }
    for (int i = 0; i < need[request_i].size(); i++)
    {
        need[request_i][i] = need[request_i][i] - request[i];
    }



    cout << "Allocation (New): " << endl;
    for (int i = 0; i < allocation.size(); i++)
    {
        for (int j = 0; j < allocation[i].size(); j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Need (New): " << endl;
    for (int i = 0; i < need.size(); i++)
    {
        for (int j = 0; j < need[i].size(); j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Available (New): " <<endl;
    for (int i = 0; i < available.size(); i++)
    {
        cout << available[i] << " ";
    }
    cout << "\n\n";

    // safety algorithm
    // step 1 :
    vector<bool> finish(no_of_processes, false);
    vector<int> work = available;
    vector<int> process_sequence;
    // step 2 :
    int no_of_falses = no_of_processes;
    for ( int check = 0; check < no_of_processes; check ++)
    {
        for (int i = 0; i < no_of_processes; i++)   // checking P_i th process
        {
            if (finish[i] == false)
            {
                bool satisfied = true;
                for (int j = 0; j < need[i].size(); j++)    // checking row of P_i th process
                {
                    if (need[i][j] > work[j])
                    {
                        satisfied = false;
                        break;
                    }
                }
                if (satisfied)
                {
                    for (int j = 0; j < no_of_resource_types; j++)
                    {
                        work[j] = work[j] + allocation[i][j];
                    }
                    finish[i] = true;
                    no_of_falses--;
                    process_sequence.push_back(i);
                    cout << "Work (new) for done process P" << i << " : " << endl;
                    for (int w = 0; w < no_of_resource_types; w++)
                    {
                        cout << work[w] << " ";
                    }
                    cout << endl ;
                    break;
                }
            }
        }
    }

    if (no_of_falses == 0)
    {
        cout << "System is in safe state" << endl;
        cout << "process sequence : " << endl;
        for ( int i = 0; i < process_sequence.size(); i++)
        {
            cout << process_sequence[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "cannot keep the request" << endl;
    }

}


/*
resource type instances
10 5 7

allocation
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

max
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

request_i
1

request instance of resource type values:
1 0 2
*/














/*
Number of process:
5
Number of resource types:
3
Resource types instances:
10 5 7
Allocation:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Max:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Available:
3 3 2
Need:
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1

request i :
1
request instance of resource type values:
1 0 2
Allocation (New):
0 1 0
3 0 2
3 0 2
2 1 1
0 0 2

Need (New):
7 4 3
0 2 0
6 0 0
0 1 1
4 3 1

Available (New):
2 3 0

Work (new) for done process P1 :
5 3 2
Work (new) for done process P3 :
7 4 3
Work (new) for done process P0 :
7 5 3
Work (new) for done process P2 :
10 5 5
Work (new) for done process P4 :
10 5 7
System is in safe state
process sequence :
1 3 0 2 4

Process finished with exit code 0
 */
