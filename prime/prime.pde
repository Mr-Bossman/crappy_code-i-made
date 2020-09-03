
import grafica.*;
import java.lang.Math;
double ln(double n){
  return Math.log(n);
}

GPlot plot1;
int test = 10000;
int start = 8000;
GPointsArray points = new GPointsArray(test); //Amber Point Array
GPointsArray points1 = new GPointsArray(test); // Red Point Array
GPointsArray points2 = new GPointsArray(test); //Green Point Array
GPointsArray allPoints = new GPointsArray(test); //Green Point Array

void setup()
{
  

  
  fullScreen();
  plot1 = new GPlot(this);
  plot1.setPos(0,0);
  plot1.setDim(width-100, height-100);
  plot1.getTitle().setText("Title");
  plot1.getXAxis().getAxisLabel().setText("XLabel");
  plot1.getYAxis().getAxisLabel().setText("YLabel"); 

}

void draw()
{
  int l = 2;
  int limit = 100000;
  if (limit > 2) 
            System.out.print(2 + " "); 
  
        if (limit > 3) 
            System.out.print(3 + " "); 
  
        // Initialise the sieve array with 
        // false values 
        boolean sieve[] = new boolean[limit]; 
  
        for (int i = 0; i < limit; i++) 
            sieve[i] = false; 
  
        /* Mark siev[n] is true if one of the 
        following is true: 
        a) n = (4*x*x)+(y*y) has odd number  
           of solutions, i.e., there exist  
           odd number of distinct pairs  
           (x, y) that satisfy the equation  
           and    n % 12 = 1 or n % 12 = 5. 
        b) n = (3*x*x)+(y*y) has odd number  
           of solutions and n % 12 = 7 
        c) n = (3*x*x)-(y*y) has odd number  
           of solutions, x > y and n % 12 = 11 */
        for (int x = 1; x * x < limit; x++) { 
            for (int y = 1; y * y < limit; y++) { 
  
                // Main part of Sieve of Atkin 
                int n = (4 * x * x) + (y * y); 
                if (n <= limit && (n % 12 == 1 || n % 12 == 5)) 
  
                    sieve[n] ^= true; 
  
                n = (3 * x * x) + (y * y); 
                if (n <= limit && n % 12 == 7) 
                    sieve[n] ^= true; 
  
                n = (3 * x * x) - (y * y); 
                if (x > y && n <= limit && n % 12 == 11) 
                    sieve[n] ^= true; 
            } 
        } 
  
        // Mark all multiples of squares as 
        // non-prime 
        for (int r = 5; r * r < limit; r++) { 
            if (sieve[r]) { 
                for (int i = r * r; i < limit; 
                     i += r * r) 
                    sieve[i] = false; 
            } 
        } 
  
        // Print primes using sieve[] 
        for (int a = 5; a < limit; a++) {
            if (sieve[a]) {
              l++;
              float k = (float)(l*(ln(l)+ln(ln(l))-1));
              points.add((float)l,k);
              if(k>100&& 105 >k)
                System.out.print(k + " "+ a + " " +l); 
              points1.add(l,a);
            }
        }
  /*String[] primes = loadStrings("H:/code/prime/primes1.txt");
  for(int x =start;x<test;x++){
      
    points1.add(x, int(primes[x]));
  }
  for(int x =start+2;x<test;x++){
    points2.add(x, (int)(ln(x)+(x*(ln(x)+ln(ln(x))-0.935))));
   if( (ln(x)+(x*(ln(x)+ln(ln(x))-0.935))) <=int(primes[x])) System.out.print("Error on upper bounds at: "+x+"\r\nEstimate: "+(ln(x)+(x*(ln(x)+ln(ln(x))-0.935)))+"\r\nAnswer: "+primes[x]);
  }
  for(int x =start+2;x<test;x++){
    points.add(x, (int)(x*(ln(x)+ln(ln(x))-1)));
    if( (x*(ln(x)+ln(ln(x))-1)) > int(primes[x])) System.out.print("error on lower bounds at:"+x);

  }
  for(int x =start+2;x<test;x++){
  //plot1.addPoint(x, (int)((x*(ln(x)+ln(ln(x))))-(x*(ln(x)+ln(ln(x))-1))));
  }*/

  plot1.addLayer("blueVal", points); //Add red layer
  plot1.addLayer("redVal", points1); //Add red layer
  plot1.addLayer("greenVal", points2); //Add green layer
  plot1.getLayer("blueVal").setPointColor(color(0, 0, 255, 100));
  plot1.getLayer("redVal").setPointColor(color(255, 0, 0, 100)); //Set red layer red
  plot1.getLayer("greenVal").setPointColor(color(0, 255, 0, 100));//Set green layer green

  plot1.beginDraw();
  plot1.drawBackground();
  plot1.drawBox();
  plot1.drawXAxis();
  plot1.drawYAxis();
  plot1.drawTitle();
  plot1.drawGridLines(GPlot.BOTH);
  plot1.drawPoints();
  plot1.getLayer("blueVal").drawPoints();
  plot1.getLayer("redVal").drawPoints();
  plot1.getLayer("greenVal").drawPoints();
  plot1.endDraw();
  stop();
}
