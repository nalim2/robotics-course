#include <Kin/kin.h>

void execTrajectory(){
  rai::Configuration K("pegArm.g");
  K.sortFrames();
  double noise = .01;
  bool gravity = true;
  uint n=K.getJointStateDimension();

  double tau=.01;
  uint N = 500;
  double T = N*tau;

  arr q,qdot, qddot_desired;
  arr M,F,u(n);
  arr integral = zeros(n);
  arr q0, q_goal;

  q = K.getJointState();
  qdot = zeros(q.N);
  q = q+0.4;
  K.setJointState(q);

  q_goal = zeros(n);
  q0 = q;

  cout <<"initial posture (hit ENTER in the OpenGL window to continue!!)" <<endl;
  K.watch();
  
  ofstream dat("z.q");

  for(uint i=0;i<=N;i++){
    double t = i * tau;
    u = 0.;

    // b) compute desired position, velocity and acceleration with sine motion profile


    
    // c) PD controller


    // d) PID controller


    // e) Inverse dynamics feedforward control
    K.equationOfMotion(M, F, qdot);



    //dynamic simulation (simple Euler integration of the system dynamics, look into the code)
    K.stepDynamics(qdot, u, tau, noise, gravity);
    K.watch(false);
    q = K.getJointState();

    cout  <<" t=" <<tau*t  <<"sec E=" <<K.getEnergy(qdot)  <<"  q = " <<q <<endl;
    dat <<q <<endl;
  }

  gnuplot("plot 'z.q' us 0:1, '' us 0:2, '' us 0:3");
  K.watch(true);
}


int main(int argc,char **argv){

  execTrajectory();
  
  return 0;
}
