// ThreadPoolCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"ThreadPool.h"

int main()
{
    std::cout << "Hello World!\n";
    ThreadPool poolofthreads(5);
    cout << "Thread Pool created \n" << endl;
    cout << " Enque some tasks \n"<< endl;
    for (int i = 0; i < 5; i++)
    {
        poolofthreads.enque(
            [i]
            {
                cout << " Task " << i << "with thread ID" << get_threadID().c_str()<< endl;
                this_thread::sleep_for(chrono::seconds(5));
            }
            );
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
