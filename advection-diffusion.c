/**
# Using a advection-diffusion equation 

We couple two solvers advection and diffusion to solve 

$$\frac{\partial f}{\partial t} + \vec{u} \nabla f = D \nabla^2 f $$ 


*/
#include "diffusion.h"
#include "advection.h"


scalar f[];
scalar * tracers = {f};
const face vector D[] = { 0.00001 , 0.00001 };

/** Intial condition : a bump placed in (-0.2,-0.2)


 */


#define bump(x,y) (exp(-100.*(sq(x + 0.2) + sq(y + 0.2))))

event init (i = 0)
{
 
  foreach()
    f[] = bump(x,y);

  
}
 
/** Velocity field condition 

Forth and back field in time
 */

event velocity (i++) {
  trash ({u});
  foreach_face(x)
    u.x[] = 1.5*sin(2.*pi*t/5.)*sin((x + 0.5)*pi)*cos((y + 0.5)*pi);
  foreach_face(y)
    u.y[] = - 1.5*sin(2.*pi*t/5.)*cos((x + 0.5)*pi)*sin((y + 0.5)*pi);
  boundary ((scalar *){u});
}

/** Advance diffusion term

Note the use of a particular event  tracer_diffudion which 
overload the correspondig hook in tracer.h

 */
event tracer_diffusion ( i++ )
{
  diffusion (f,dt,D);
  
}

/** Movie


 */

event print ( i += 10 ; i <= 400 )
{
  static FILE * fp1 = popen ("ppm2mpeg > f.mpg", "w");
  output_ppm (f, fp1, linear = true, spread = 4);
}


/** Main 

 */

int main() {
  // coordinates of lower-left corner
  X0 = Y0 = -0.5;
  DT = 1. ;
  // CFL number
  CFL = 0.8;
  //
  N = 64 ;

  dt = 0.01;

  run();
}
