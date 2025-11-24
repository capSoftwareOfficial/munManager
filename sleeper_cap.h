#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


void delayMs(int ms)
{
    sleep_for(milliseconds(ms));
    return;
}

void waitMs(int ms)
{
    sleep_until(system_clock::now() + milliseconds(ms));
}
