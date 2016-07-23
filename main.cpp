#include <iostream>
#include "ball.h"
#include "physics.h"
#include "error.h"
/*
2D collision simulation
Yan Ke
*/
//request input to rerun simulation and returns bool
bool runAgain(Time &time)
{
    char input;
    std::cout<<"Run again for "<<time.run_time<<"s ?(y/n): ";
    do{
        std::cin>>input;
    }while(errorHandling(input, 'y', 'n'));

    if(input=='y')
    {
        time.end_time +=time.run_time;
        return true;
    }
    return false;
}

void runSimulation(Ball &b1, Ball &b2)
{
    SimulationStatus status(Moving);
    const int linearness = 1; //the power the distance in Hooke's formula is raised to
    Time time{0.0,0.0,0.00001,0.0};

    //run the simulation until ...
    std::cout<<"Enter runtime (s): ";
        do{
            std::cin>>time.run_time;
        }while(errorHandling(time.run_time));

        time.end_time = time.run_time;

    do{
        while(time.sim_time<time.end_time)
        {
            b1.distanceBetweenBalls(b2);
            b2.distanceBetweenBalls(b1);

            b1.returnCompression(b2);
            b2.returnCompression(b1);

            //if compression is present, force is present
            b1.updateForce(linearness);
            b2.updateForce(linearness);

            b1.updateKinematics(time.dt);
            b2.updateKinematics(time.dt);

            //increment time
            time.sim_time+=time.dt;
        }
        //return simulation results using overloaded operators
        std::cout<<"At "<<time.sim_time<<"s: "<<std::endl<<b1<<std::endl<<b2<<std::endl;
    }while(runAgain(time));
}

int main()
{
    Ball b1(1);
    Ball b2(2);
    runSimulation(b1,b2);
    return 0;

}
