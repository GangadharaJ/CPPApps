#pragma once
#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>


std::binary_semaphore signal_to_producer(1),
signal_to_consumer(0);
int buffer[5];
using namespace std::chrono_literals;
int buffersize = 5;
void producerservice()
{
    while (1)
    {
        std::cout << "Hello Producer\n" << std::flush;
        const auto start = std::chrono::high_resolution_clock::now();
        signal_to_producer.acquire();
        for (int i = 0; i < buffersize; i++)
        {
            buffer[i] = i * i;
            std::cout << buffer[i] << " " << std::flush;
            std::this_thread::sleep_for(200ms);
        }
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Hello Producer End\n" << elapsed << std::flush;
        signal_to_consumer.release();
    }
}

void consumerservice()
{
    while (1)
    {
        std::cout << "Hello Consumer\n" << std::flush;
        const auto start = std::chrono::high_resolution_clock::now();
        signal_to_consumer.acquire();
        for (int i = (buffersize - 1); i >= 0; i--)
        {
            std::cout << buffer[i] << " " << std::flush;
            buffer[i] = 0;
            std::this_thread::sleep_for(200ms);
        }
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Hello Consumer End\n" << elapsed << std::flush;
        signal_to_producer.release();
    }
}
