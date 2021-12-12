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
            bool frame_has_empty_block = false;
            //  check if frame has empty block
            for (int frame_index = 0; frame_index < frame.size(); frame_index++)
            {
                if (frame[frame_index] == -1)
                {
                    frame[frame_index] = reference_string[i];
                    frame_has_empty_block = true;
                    break;
                }
            }

            if (frame_has_empty_block == false)
            {
                vector<int> block_to_get_new_value(frame_size, 9999);
                //  traversing frame to compare with rest of the reference string
                for (int frame_index = 0; frame_index < frame.size(); frame_index++)
                {
                    for (int reference_string_index = i; reference_string_index >= 0; reference_string_index--)
                    {
                        if (frame[frame_index] == reference_string[reference_string_index])
                        {
                            block_to_get_new_value[frame_index] = reference_string_index;
                            break;
                        }
                    }
                }

                int frame_index_for_new_value = 0;
                int minimum_value = 999;
                //  which frame index will get the new value
                for (int block_new_index = 0; block_new_index < block_to_get_new_value.size(); block_new_index++)
                {
                    if (block_to_get_new_value[block_new_index] < minimum_value)
                    {
                        frame_index_for_new_value = block_new_index;
                        minimum_value = block_to_get_new_value[block_new_index];
                    }
                }
                frame[frame_index_for_new_value] = reference_string[i];
            }
            total_page_fault++;

            // printing frame for a reference string
            for (int frame_index = 0; frame_index < frame.size(); frame_index++)
            {
                cout << frame[frame_index] << " ";
            }
            cout << "\tpage fault";
        }
        cout << endl;

    }
    cout << "Total page fault : " << total_page_fault << endl;

}
