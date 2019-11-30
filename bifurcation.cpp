#include <iostream>
#include <cmath>
#include <stdlib.h>
#include<fstream>

//Global variables declaring
const double G=9.8;
const double dt=0.01; //Step for th method //M_PI/300.0;
const double eps=0.001;
//theta''+g/l theta + q theta' = F_d sin(Omega t)

class Pendulum
{
public:
  double L; //Lenght
  double q; //Friction coeficient
  double Fd; //External Force
  double Omega; //External force frequency
  double W; //Angular velocity 
  double Theta; //Angle
  Pendulum();// Initial values for the class
  ~Pendulum();//Anihilator
};
Pendulum::Pendulum()
{
  L=0.0;
  q=0.0;
  Fd=0.0;
  Omega=0.0;
  W=0.0;
  Theta=0.0;
}
Pendulum::~Pendulum()
{
}

//------------------------------Function declaring----------------------------
void initial_conditions(Pendulum & p, double Fd);
void euler_cromer(Pendulum & p,double dt,double t);


int main(int argc, char** argv)
{
  Pendulum p;
  double t=0.0;//Time 
  double t_modulo=0.0;
  int N = atoi(argv[1]);//steps of evolution
  double Fd = 1.41;//steps of evolution
  double step= 0.0000786;
  // intialization
initial_conditions(p, Fd);
for (int ii=1; ii<=N; ii++)
{
    t+=dt;
    t_modulo+=dt;
    euler_cromer(p,dt,t);
    if(t_modulo>(3*M_PI))
    {
        p.Fd=Fd;
        std::cout << p.Theta << "\t" << Fd<< std::endl;  
        Fd+= step;
        t_modulo= 0;
    }
}
  return 0;
}


// ------------------- Functions ------------------------------------
void euler_cromer(Pendulum & p,double dt,double t)
{
  // Euler- Cromer
  p.W=p.W+(-(G/p.L)*sin(p.Theta) - p.q*p.W + p.Fd*sin(p.Omega*t))*dt;
  p.Theta=p.Theta + p.W*dt;
  if(p.Theta < - M_PI)
    {
      p.Theta += 2*M_PI;
    }
  else if(p.Theta > M_PI)
    {
      p.Theta += -2*M_PI;
    }
} 
 
void initial_conditions(Pendulum & p, double Fd)
{
  p.q=0.5;
  p.Fd=Fd;
  p.Omega=0.666;
  p.L=G;
  p.W=0.0;
  p.Theta=0.2;  
}