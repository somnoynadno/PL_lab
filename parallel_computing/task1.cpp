#include<iostream>
#include<thread>
#include<ctime>
#include<vector>
#include<mutex>
#include<chrono>
#include<condition_variable>

#include "UserInterruptHandler.h"

using namespace std;

condition_variable cv;
bool ready;
bool flag; // global end

void printNum(mutex& m, int num){
    while (!flag){
        unique_lock <mutex> lck(m);
        if (!ready) cv.wait(lck);
        cout << "Thread " << num << " is here"<< endl;
        ready = false;
    }

    m.lock();
    cout << "Thread " << num << ": " << "I quit" << endl;
    m.unlock();
    return;
}

int main(){
    srand(time(0));
    ready = false;
    flag = false;
    vector <thread> threads;
    mutex mtx;
    UserInterruptHandler h;
    // num of threads
    int n;
    cin >> n;
    cout << n << endl;

    for (int i = 0; i < n; i++){
        threads.push_back(thread(printNum, ref(mtx), i+1));
    }

    while(!h.checkInterruption()){
        ready = true;
        cv.notify_one();
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << endl;
    flag = true;
    ready = true;
    cv.notify_all();

    for (int i = 0; i < n; i++){
        if (threads[i].joinable()) threads[i].join();
    }

    cout << "Nice" << endl;
    return 0;
}