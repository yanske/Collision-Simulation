#ifndef PHYSICS_H
#define PHYSICS_H

//class contains variable components
enum SimulationStatus
{
    Moving,
    Colliding,
    Collided,
};

struct Time
{
  double sim_time;
  double run_time;
  double dt;
  double end_time;
};
struct Distance
{
    double x;
    double y;
    double mag;
};

struct Compression
{
    double x;
    double y;
    double mag;
};

struct position2d
    {
        double x;
        double y;
    };
struct velocity2d
    {
        double x;
        double y;
    };
struct acceleration2d
    {
        double x;
        double y;
    };
struct forces2d
    {
        double x;
        double y;
    };

#endif // PHYSICS_H
