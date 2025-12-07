#include <bits/stdc++.h>
using namespace std;
long long ctr;
const int INSERTION_THRESHOLD = 32;

void InsertionSort(int* height, int n, int k) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (height[i] + k < height[j]) {
                ctr++;
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        int key = height[i];
        int j = i - 1;
        while (j >= 0 && height[j] < key) {
            height[j + 1] = height[j];
            j--;
        }
        height[j + 1] = key;
    }
}

void MergeSort(int* height, int n, int k) {
    if (n <= INSERTION_THRESHOLD) {
        InsertionSort(height, n, k);
        return;
    }

    MergeSort(height, n / 2, k);
    MergeSort(height + n / 2, n - n / 2, k);
    int h[n];
    int i = 0, j = n / 2, temp = 0, inw = 0;
    while (i < n / 2 or j < n) {
        if (i >= n / 2) {
            h[temp] = height[j];
            ++j;
        }
        else if (j >= n) {
            h[temp] = height[i];
            ++i;
        }
        else if (height[i] >= height[j]) {
            h[temp] = height[i];
            ++i;
        }
        else {
            h[temp] = height[j];
            while (n / 2 > inw and height[inw] + k >= height[j]) {
                ++inw;
            }
            ctr += n / 2 - inw;
            ++j;
        }
        ++temp;
    }
    for (int i = 0; i < n; ++i)
        height[i] = h[i];

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

        MergeSort(height, n, k);

        for (int x : height) cout << x << ' ';
        cout << '\n';
        cout << ctr << '\n';
    }
}