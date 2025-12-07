#include <bits/stdc++.h>
using namespace std;

const int THREADS = thread::hardware_concurrency();

atomic<int> available_threads(12);
atomic<long long> ctr;

int threshold = 8;

void MergeSort(int* height, int n, int k, int budget) {
    if (n == 1) return;
    bool parallel = (n >= threshold && budget > 1);

    if (parallel == true) {
        thread t;
        t = thread(MergeSort, height, n / 2, k, budget / 2);
        MergeSort(height + n / 2, n - n / 2, k, budget - budget / 2);
        t.join();
    }
    else {
        MergeSort(height, n / 2, k, 1);
        MergeSort(height + n / 2, n - n / 2, k, 1);
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

    for (int i = 0; i < n; ++i)
        height[i] = h[i];

    ctr.fetch_add(temp_ctr);

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
        for (int& h : height) cin >> h;
        ctr = 0;

        MergeSort(height, n, k, available_threads);

        for (int x : height) cout << x << ' ';
        cout << '\n';
        cout << ctr << '\n';
    }
}