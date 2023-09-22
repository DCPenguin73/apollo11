/*************************************************************
 * 1. Name:
 *      team 7 Daniel & Cayden
 * 2. Assignment Name:
 *      Lab 02: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was adding the while loop while still having a consistant time for the simulation.
 *      We ended up making a new variable called count to handle it.
 * 5. How long did it take for you to complete the assignment?
 *      30 minutes after we finished the problems set assignment. 
 *****************************************************************/


#include <iostream>  // for CIN and COUT
#include <cmath>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2

#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
double PI = (2 * acos(0.0));

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
 // your function goes here
double computeDistance(double s, double v, double a, double t) {
    double s2 = s + (v * t) + (0.5 * a * (t * t));
    return s2;
}

 /**************************************************
  * COMPUTE ACCELERATION
  * Find the acceleration given a thrust and mass.
  * This will be done using Newton's second law of motion:
  *     f = m * a
  * INPUT
  *     f : force, in Newtons (kg * m / s^2)
  *     m : mass, in kilograms
  * OUTPUT
  *     a : acceleration, in meters/second^2
  ***************************************************/
  // your function goes here
double computeAcceleration(double f, double m) {
    double a = f / m;
    return a;
}

  /***********************************************
   * COMPUTE VELOCITY
   * Starting with a given velocity, find the new
   * velocity once acceleration is applied. This is
   * called the Kinematics equation. The
   * equation is:
   *     v = v + a t
   * INPUT
   *     v : velocity, in meters/second
   *     a : acceleration, in meters/second^2
   *     t : time, in seconds
   * OUTPUT
   *     v : new velocity, in meters/second
   ***********************************************/
   // your function goes here
double computeVelocity(double v, double a, double t) {
    double v2 = v + (a * t);
    return v2;
}


   /***********************************************
    * COMPUTE VERTICAL COMPONENT
    * Find the vertical component of a velocity or acceleration.
    * The equation is:
    *     cos(a) = y / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     y : the vertical component of the total
    ***********************************************/
    // your function goes here
double computeVertical(double a, double total) {
    double y = cos(a) * total;
    return y;
}

    /***********************************************
     * COMPUTE HORIZONTAL COMPONENT
     * Find the horizontal component of a velocity or acceleration.
     * The equation is:
     *     sin(a) = x / total
     * This can be expressed graphically:
     *      x
     *    +-----
     *    |   /
     *  y |  / total
     *    |a/
     *    |/
     * INPUT
     *     a : angle, in radians
     *     total : total velocity or acceleration
     * OUTPUT
     *     x : the vertical component of the total
     ***********************************************/
     // your function goes here
double computeHorizontal(double a, double total) {
    double x = sin(a) * total;
    return x;
}

     /************************************************
      * COMPUTE TOTAL COMPONENT
      * Given the horizontal and vertical components of
      * something (velocity or acceleration), determine
      * the total component. To do this, use the Pythagorean Theorem:
      *    x^2 + y^2 = t^2
      * where:
      *      x
      *    +-----
      *    |   /
      *  y |  / total
      *    | /
      *    |/
      * INPUT
      *    x : horizontal component
      *    y : vertical component
      * OUTPUT
      *    total : total component
      ***********************************************/
double computeTotal(double x, double y) {
    double total;
    total = sqrt(x * x + y * y);
        return total;
      }


      /*************************************************
       * RADIANS FROM DEGEES
       * Convert degrees to radians:
       *     radians / 2pi = degrees / 360
       * INPUT
       *     d : degrees from 0 to 360
       * OUTPUT
       *     r : radians from 0 to 2pi
       **************************************************/
double degreesToRadians(double d) {
    double r;
    r = (PI * d) / 180;
    return r;
}

       /**************************************************
        * PROMPT
        * A generic function to prompt the user for a double
        * INPUT
        *      message : the message to display to the user
        * OUTPUT
        *      response : the user's response
        ***************************************************/
double prompt(string message) {
    double response;
    cout << message << endl;
    cin >> response;
    return response;
        }

        /****************************************************************
         * MAIN
         * Prompt for input, compute new position, and display output
         ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double t = 1;
    double x = 0;
    double aRadians = degreesToRadians(aDegrees);            // Angle in radians
    double accelerationThrust = computeAcceleration(THRUST, WEIGHT);  // Acceleration due to thrust 
    double ddxThrust = computeHorizontal(aRadians, accelerationThrust);           // Horizontal acceleration due to thrust
    double ddyThrust = computeVertical(aRadians, accelerationThrust);           // Vertical acceleration due to thrust
    double ddx = ddxThrust;             // Total horizontal acceleration
    double ddy = ddyThrust + GRAVITY;             // Total vertical acceleration
    double v = computeTotal(dx, dy); 
    int count = 0;
    // Go through the simulator five times
    while (y > 0) {
        cout << "For the next 5 seconds with the main engine on, the position of the lander is:" << endl;
        for (int i = 0; i < 5; i++) {
            count++;
            dx = computeVelocity(dx, ddx, t);
            dy = computeVelocity(dy, ddy, t);
            v = computeTotal(dx, dy);
            x = computeDistance(x, dx, ddx, t);
            y = computeDistance(y, dy, ddy, t);
            // Output
            cout.setf(ios::fixed | ios::showpoint);
            cout.precision(2);
            cout << count << "s - x,y:(" << x << ", " << y << ")m ";
            cout << " dx,dy:(" << dx << ", " << dy << ")m/s ";
            cout << " speed:" << v << "m/s ";
            cout << "angle:" << aDegrees << "deg" << endl;
            //cout << "\tNew position:   (" << x << ", " << y << ")m\n";
            //cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
            //cout << "\tTotal velocity:  " << v << "m/s\n\n";
        }
        if (y > 0) {
            aDegrees = prompt("What is the new angle of the LM where 0 is up (degrees)? ");
        }
    }
    
    
    return 0;
}