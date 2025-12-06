#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int THREADS = 8;

atomic<int> available_threads(8);

int threshold = 1024;

long long MergeSort(int* height, int n, const int k) {
    if (n == 1) return 0;
    bool parallel =(n >= threshold);

    long long left_ctr = 0, right_ctr = 0;

    if (parallel == true) {
#pragma omp task shared(height, left_ctr) //firstprivate(n, depth)
        {
            left_ctr = MergeSort(height, n / 2, k);
        }
#pragma omp task shared(height, right_ctr) //firstprivate(n, depth)
        {
            right_ctr = MergeSort(height + n / 2, n - n / 2, k);
        }
# pragma omp taskwait
    }
    else {
        left_ctr = MergeSort(height, n / 2, k);
        right_ctr = MergeSort(height + n / 2, n - n / 2, k);
    }

    vector<int>h(n);
    int i = 0, j = n / 2, temp = 0, inw = 0;
    int temp_ctr = 0;


    while (i < n / 2 and j < n) {
        if (height[i] >= height[j]) {
            h[temp] = height[i];
            ++i;
        }
        else {
            h[temp] = height[j];
            while (n / 2 > inw and height[inw] + k >= height[j]) {
                ++inw;
            }
            temp_ctr += n / 2 - inw;
            ++j;
        }
        ++temp;
    }
    while (i < n / 2) {
        h[temp++] = height[i++];
    }
    while (j < n) {
        h[temp++] = height[j++];
    }

    memcpy(height, h.data(), n * sizeof(int));

    return left_ctr + right_ctr +  temp_ctr;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);

    int z;
    cin >> z;
    // vector<vector<int>> all_heights(z);  // optional: store all arrays if needed
    vector<vector<int>> sorted_arrays(z);  // store arrays
    vector<long long> counters(z);

#pragma omp parallel
    {
#pragma omp single
        {
            for (int alpha = 0; alpha < z; ++alpha) {
                int n, k;
                cin >> n >> k;
                vector<int> height(n);
                for (int& h : height) cin >> h;

#pragma omp task firstprivate(alpha, n, k)
                {
                    long long ctr = MergeSort(height.data(), n, k);

                    // #pragma omp critical
                    //                     {
                                            // for (int x : height) cout << x << ' ';
                                            // cout << '\n';
                                            // cout << ctr << '\n';
                    sorted_arrays[alpha] = std::move(height);  // move the sorted array instead of copying
                    counters[alpha] = ctr;
                    // }
                }
            }
#pragma omp taskwait
            for (int i = 0; i < z; ++i) {
                for (int x : sorted_arrays[i]) cout << x << ' ';
                cout << '\n';
                cout << counters[i] << '\n';
            }
        } // end single
    } // end parallel
}
