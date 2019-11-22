#define MIN_VAL 2147483647
#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>
#include<mutex>
#include<chrono>
#include<future>

#include "UserInterruptHandler.h"

using namespace std;

void searchInRange(int *arr, int start, int end, promise<int>&& p){
    int minimum = MIN_VAL;
    for (int i = start; i < end; i++){
        if (arr[i] < minimum) minimum = arr[i];
    }
    p.set_value(minimum);
}

int main(){
    freopen("data.txt", "r", stdin);

    int n;
    cin >> n;
    cout << "Num of elems is " << n << endl;

    int *arr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int min;
    cin >> min;
    cout << "Answer for task is " << min << endl;

    vector <future<int>> futures;
    vector <int> results;
 
    int num_of_threads = 1;
    for (int i = 0; i < 4; i++){
        futures.clear();
        results.clear();

        num_of_threads *= 2;
        cout << "Starting " << num_of_threads << " threads" << endl;

        int step = (int) (n / num_of_threads);
        int start = 0;
        int end = step;

        chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

        for (int j = 0; j < num_of_threads; j++){
            promise <int> p;
            futures.push_back(p.get_future());

            thread t(searchInRange, arr, start, end, move(p));
            start += step;
            end += step;
            if (end > n) end = n;

            t.detach();
        }

        for (int j = 0; j < num_of_threads; j++){
            int res = futures[j].get();
            results.push_back(res);
        }

        chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds> (t2 - t1).count();

        sort(results.begin(), results.end());
        cout << "Answer for " << num_of_threads << " threads is " << results[0] << endl;
        cout << "Time taken: " << duration << " ms" << endl;
    }

    // cout << res << endl;
    // cout << "My answer is " << minimum << endl;

    return 0;
}