#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int THREADS = 8;

atomic<int> available_threads(8);
atomic<long long> ctr;


int threshold = 4000;

void MergeSort(int* height, int n, const int k) {
    if (n == 1) return;
    bool parallel = (n >= threshold);

    if (parallel == true) {
#pragma omp task shared(height, n, k)
        {
            MergeSort(height, n / 2, k);
        }
    // #pragma omp task shared(height)
    MergeSort(height + n / 2, n - n / 2, k);
# pragma omp taskwait
    }
    else {
        MergeSort(height, n / 2, k);
        MergeSort(height + n / 2, n - n / 2, k);
    }


    // vector<int>h(n);
    // int i = 0, j = n / 2, temp = 0, inw = 0;
    int temp_ctr = 0;


    // while (i < n / 2 and j < n) {
    //     if (height[i] >= height[j]) {
    //         h[temp] = height[i];
    //         ++i;
    //     }
    //     else {
    //         h[temp] = height[j];
    //         while (n / 2 > inw and height[inw] + k >= height[j]) {
    //             ++inw;
    //         }
    //         temp_ctr += n / 2 - inw;
    //         ++j;
    //     }
    //     ++temp;
    // }
    // while (i < n / 2) {
    //     h[temp++] = height[i++];
    // }
    // while (j < n) {
    //     h[temp++] = height[j++];
    // }

    // memcpy(height, h.data(), n * sizeof(int));


    // ctr.fetch_add(temp_ctr);

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);


    int z;
    cin >> z;
    for (int alpha = 0; alpha < z; ++alpha) {
        int n, k;
        cin >> n >> k;
        vector<int>height(n);
        vector<int> h(n);
        for (int& h : height) cin >> h;
        ctr = 0;
#pragma omp parallel
        {
#pragma omp single
            MergeSort(height.data(), n, k);

        }

        for (int x : height) cout << x << ' ';
        cout << '\n';
        cout << ctr << '\n';
    }
}