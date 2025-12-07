#include <bits/stdc++.h>
using namespace std;

const int THREADS = 8; //thread::hardware_concurrency();

const int available_threads(THREADS);

int threshold = 1024;

long long MergeSort(int* height, int* h, int n, int k, int budget) {
    if (n == 1) return 0;
    bool parallel = (n >= threshold && budget > 1);
    long long current_total = 0;

    if (parallel == true) {
        long long left_ctr = 0;
        thread t([&]() {
            left_ctr = MergeSort(height, h, n / 2, k, budget / 2);
        });
        long long right_ctr = MergeSort(height + n / 2, h + n / 2, n - n / 2, k, budget - budget / 2);
        t.join();
        current_total += left_ctr + right_ctr;
    }
    else {
        current_total += MergeSort(height, h, n / 2, k, 1);
        current_total += MergeSort(height + n / 2, h + n / 2, n - n / 2, k, 1);
    }

    // vector<int>h(n);
    int i = 0, j = n / 2, temp = 0, inw = 0;
    long long temp_ctr = 0;

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

    memcpy(height, h, n * sizeof(int));

    return current_total += temp_ctr;

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int z;
    cin >> z;
    for (int alpha = 0; alpha < z; ++alpha) {
        int n, k;
        cin >> n >> k;
        int height[n];
        vector<int> buffer(n);
        for (int& h : height) cin >> h;
        long long ctr = MergeSort(height, buffer.data(), n, k, available_threads);

        for (int x : height) cout << x << ' ';
        cout << '\n';
        cout << ctr << '\n';
    }
}