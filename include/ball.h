#ifndef BALL_H
#define BALL_H
#include <iostream>
#include "error.h"
#include "physics.h"
#include <math.h>

class Ball
{
private:
    int m_index;
    double m_radius;
    double m_mass;
    double m_k; //spring constant (1478.4Nm of our experimental balls)
    position2d m_position2d;
    velocity2d m_velocity2d;
    acceleration2d m_acceleration2d;
    forces2d m_forces2d;
    Distance m_distance;
    Compression m_compression;

    void requestInput()
    {
        std::cout<<"Enter ball's mass(kg): ";
        do{
            std::cin>>m_mass;
        }while(errorHandling(m_mass));

        std::cout<<"Enter ball's radius(m): ";
        do{
            std::cin>>m_radius;
        }while(errorHandling(m_radius));

        std::cout<<"Enter ball's spring constant(Nm): ";
        do{
            std::cin>>m_k;
        }while(errorHandling(m_k));

        std::cout<<"Enter ball's initial position(m): "<<std::endl<<"x: ";
        do{
            std::cin>>m_position2d.x;
        }while(errorHandling());

        std::cout<<"y: ";
        do{
            std::cin>>m_position2d.y;
        }while(errorHandling());

        std::cout<<"Enter ball's initial velocity(ms-1): "<<std::endl<<"x: ";
        do{
            std::cin>>m_velocity2d.x;
        }while(errorHandling());

        std::cout<<"y: ";
        do{
            std::cin>>m_velocity2d.y;
        }while(errorHandling());
    }

public:

    Ball(int index)
        :m_index(index),m_forces2d{0.0,0.0}, m_acceleration2d{0.0,0.0}, m_distance{0,0,0}, m_compression{0,0,0}
    {
        std::cout<<"Enter values for ball "<<index<<" : "<<std::endl;
        requestInput();
    }

    //return distance by using pythagorean theorem
    void distanceBetweenBalls(Ball &otherball)
    {
        m_distance.x = otherball.m_position2d.x - m_position2d.x;
        m_distance.y = otherball.m_position2d.y - m_position2d.y;
        m_distance.mag=sqrt(pow(m_distance.x,2)+pow(m_distance.y,2));
    }

    //return compression by radius sum minus distance from ball midpoint
    void returnCompression(Ball &otherball)
    {
        m_compression.mag = m_radius+otherball.m_radius-m_distance.mag;
        m_compression.x = m_compression.mag*m_distance.x/m_distance.mag;
        m_compression.y = m_compression.mag*m_distance.y/m_distance.mag;
    }

    //if compression is present, force calculated using Hooke's law
    void updateForce(int linearness)
    {
        if(m_compression.mag>0)
        {
            m_forces2d.x = -m_k*pow(m_compression.x,linearness);
            m_forces2d.y = -m_k*pow(m_compression.y,linearness);
        }
        else
        {
            m_forces2d.x = 0.0;
            m_forces2d.y = 0.0;
        }
    }

    void updateKinematics(const double dt)
    {
        m_acceleration2d.x = m_forces2d.x/m_mass;
        m_acceleration2d.y = m_forces2d.y/m_mass;

        m_velocity2d.x+=m_acceleration2d.x*dt;
        m_velocity2d.y+=m_acceleration2d.y*dt;

        m_position2d.x+= m_velocity2d.x*dt;
        m_position2d.y+= m_velocity2d.y*dt;

    }

    //overloaded cout to output simulation results
    friend std::ostream& operator<<(std::ostream &out, const Ball &ball);
};

std::ostream& operator<<(std::ostream &out, const Ball &ball)
{
    out<<"Ball "<<ball.m_index<<" is at ("<<ball.m_position2d.x<<", "<<ball.m_position2d.y<<") "<<"moving at ( "<<ball.m_velocity2d.x<<", "<<ball.m_velocity2d.y<<")ms-1."<<std::endl;
    return out;
}

#endif // BALL_H
