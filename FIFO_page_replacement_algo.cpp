#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cout << "size of reference string : " << endl;
    int reference_string_size; cin >> reference_string_size;

    cout << "Enter reference string : " << endl;
    vector<int> reference_string;
    for (int i = 0; i < reference_string_size; i++)
    {
        int n; cin >> n; reference_string.push_back(n);
    }

    cout << "Frame size : " << endl;
    int frame_size; cin >> frame_size;
    vector<int> frame(frame_size, -1);  // -1 denotes empty frame block

    int frame_pointer = 0;
    int total_page_fault = 0;
    for (int i = 0; i < reference_string.size(); i++)
    {
        bool string_is_inside_frame = false;

        //  searching if the string is inside frame
        for (int search = 0; search < frame.size(); search++)
        {
            if (reference_string[i] == frame[search])
            {
                string_is_inside_frame = true;
                // no change in frame pointer
                break;
            }
        }

        cout << reference_string[i] << " : ";
        if (string_is_inside_frame == false)
        {
            frame[frame_pointer] = reference_string[i];
            frame_pointer++;
            total_page_fault++;

            // printing frame for a reference string
            for (int frame_index = 0; frame_index < frame.size(); frame_index++)
            {
                cout << frame[frame_index] << " ";
            }
            cout << "\tpage fault";
        }
        cout << endl;

        if (frame_pointer > frame_size - 1)
        {
            frame_pointer = 0;
        }
    }
    cout << "Total page fault : " << total_page_fault << endl;

}
