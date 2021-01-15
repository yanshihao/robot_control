#include "../include/robot_control/ultils.h"
#include "Trajectory.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
int main()
{
    double time = 0;
    std::shared_ptr<Trajectory> trajectory(new TurningLeftTrajectory2);
    while(1)
    {
        PathInfo info = trajectory->getPathInfo(time);
        cout << info ;
        this_thread::sleep_for(chrono::milliseconds(200));
        time += 0.1;
    }
    return 0;
}