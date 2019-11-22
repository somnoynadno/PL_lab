#define MAX_WORK_TIME 8
#include <chrono>
#include <condition_variable>
#include <ctime>
#include <deque>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdio.h>
#include <thread>
#include <vector>

#include "Request.hpp"
#include "Request.cpp"
#include "UserInterruptHandler.h"

using namespace std;

// global ending
bool finish;

void produce(mutex& m, priority_queue<Request, vector<Request>, less<vector<Request>::value_type>>* requests_queue, int max_size, int class_num){
    srand(time(0));
    cout << "Start producing" << endl;
    
    while(!finish){
        int n = rand() % max_size;
        m.lock();
        for (int i = 0; i < n; i++){
            // if queue is not full
            if (requests_queue->size() < max_size){
                int p = rand() % 3 + 1;
                int c = rand() % class_num;
                Request request = Request(c, p);
                requests_queue->push(request);
            }
            else {
                break;
            }
        }
        m.unlock();
        this_thread::sleep_for(chrono::seconds(2));
    }
    m.lock();
    cout << "Producer exit" << endl;
    m.unlock();
}

void consume(mutex& m, int group, int number, int **time, priority_queue<Request, vector<Request>, less<vector<Request>::value_type>>* requests_queue){
    m.lock();
    cout << "Start work" << endl;
    m.unlock();
    while(!finish){
        // check for work
        m.lock();
        if (!requests_queue->empty()){
            Request r = requests_queue->top();
            int i = r.get_class_number();
            // if work found
            if (group == i){
                // do work
                requests_queue->pop();
                m.unlock();
                int work_time = rand() % MAX_WORK_TIME + 1;
                time[group][number] = work_time;
                this_thread::sleep_for(chrono::seconds(work_time));
                continue;
            }
        }
        m.unlock();
        // else sleep
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    m.lock();
    cout << "Job done: Group " << group+1 << " Device " << number+1 << endl;
    m.unlock();
}

void print_queue_status(priority_queue<Request, vector<Request>, less<vector<Request>::value_type>> requests_queue, int max_size){
    cout << "Queue: " << requests_queue.size() << "/" << max_size << endl;
}

void print_devices_status(int **time, int n, int m){
    for (int i = 0; i < n; i++){
        cout << "Group " << i+1 << endl;
        for (int j = 0; j < m; j++){
            int t = time[i][j];
            cout << "Device " << j+1 << ": ";
            if (t == 0) cout << "free" << endl;
            else cout << "busy ("  << t << "s remaining)" << endl;
        }
    }
}

void set_time_to_zero(int **time, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            time[i][j] = 0;
        }
    }
}

void tick(int **time, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (time[i][j] > 0) time[i][j]--;
        }
    }
}

void clear(){
    printf("\033[H\033[J");
}

int main(){
    srand(time(0));
    int size, n, m;
    finish = false;
    // getting variables
    cout << "Enter queue size:" << endl;
    cin >> size;
    cout << "Enter number of groups:" << endl;
    cin >> n;
    cout << "Enter number of devices in each group:" << endl;
    cin >> m;
    clear();

    mutex mtx;    
    vector <thread> threads;
    priority_queue<Request, vector<Request>, less<vector<Request>::value_type>> requests_queue;

    // table with time
    int **time = new int* [n];
    for (int i = 0; i < n; i++){
        time[i] = new int [m];
    }
    set_time_to_zero(time, n, m);

    // create producer
    threads.push_back(thread(produce, ref(mtx), &requests_queue, size, n));

    // create consumers    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            threads.push_back(thread(consume, ref(mtx), i, j, time, &requests_queue));
        }
    }

    // monitoring
    UserInterruptHandler h;
    while (!h.checkInterruption()){
        clear();
        print_queue_status(requests_queue, size);
        print_devices_status(time, n, m);
        // decrement time
        tick(time, n, m);
        // and sleep for a second
        this_thread::sleep_for(chrono::seconds(1));
    }

    // on interrupt
    clear();
    set_time_to_zero(time, n, m);
    finish = true;
    // wait for other threads to finish
    this_thread::sleep_for(chrono::seconds(MAX_WORK_TIME));

    // join threads
    for (int i = 0; i < threads.size(); i++){
        threads[i].join();
    }

    // free memory
    for (int i = 0; i < n; i++){
        delete time[i];
    }
    delete time;

    mtx.lock();
    cout << "Nice" << endl;
    mtx.unlock();

    return 0;
}