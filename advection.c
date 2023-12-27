//#include "grid/cartesian.h"
#include "advection.h"
//#include "diffusion.h"


scalar f[];
scalar * tracers = {f};
//vector D[];
//scalar rhs[];


void parameters()
{
 
}

#define bump(x,y) (exp(-100.*(sq(x + 0.2) + sq(y + .2))))

event init (i = 0)
{
  foreach()
    f[] = bump(x,y);

  // foreach()
  //    rhs[] = 0.0 ;
  
}
 
event velocity (i++) {
  trash ({u});
  foreach_face(x)
    u.x[] = 1.5*sin(2.*pi*t/5.)*sin((x + 0.5)*pi)*cos((y + 0.5)*pi);
  foreach_face(y)
    u.y[] = - 1.5*sin(2.*pi*t/5.)*cos((x + 0.5)*pi)*sin((y + 0.5)*pi);
  boundary ((scalar *){u});
}

event running ( i++ )
{
 
  //diffusion (f,rhs,dt);
}

event print ( i += 10 ; i <= 400 )
{
  static FILE * fp1 = popen ("ppm2mpeg > f.mpg", "w");
  output_ppm (f, fp1, linear = true, spread = 4);
}

int main() {
  // coordinates of lower-left corner
  X0 = Y0 = -0.5;
  // maximum timestep
  DT = .1;
  // CFL number
  CFL = 0.8;
  //
  N = 64 ;

  dt = 0.01;

  run();
}
