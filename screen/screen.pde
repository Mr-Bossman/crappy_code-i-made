import java.lang.Math;
PrintWriter output;
int rings = 12*2;
int deg = 360*1;
boolean fit = false;
String image = "pic.jpg";
import processing.serial.*;
void setup() {
  Serial myPort;
  myPort = new Serial(this, Serial.list()[1], 9600);
  System.out.println(Serial.list()[1]);
  noStroke();
  size(1000,1000);
  
  color[][] buffer = new int[deg][rings];
  int div = deg/360;
  PImage imp = loadImage(image);
  int scale;
  
  if(imp.width != imp.height){
    System.out.print("image needs to be sqare");
    exit();
  }
  
  if(fit){
    scale = (int)(imp.width / ((2*rings)/sqrt(2)));
  }else{
    scale = imp.width / (rings*2);
  }
  
  PImage img = createImage(rings*2,rings*2,RGB);
  for(int d = 0; d  < deg; d++){
    for(int r = 0; r < rings; r++){
      int y = -(int)Math.round(Math.cos(Math.toRadians((double)d/div))*r*scale);
      int x = (int)Math.round(Math.sin(Math.toRadians((double)d/div))*r*scale);
      buffer[d][r]= imp.get( x+imp.width/2, y+imp.height/2);
    }
  }
  
  output = createWriter("positions.txt"); 
  output.print("{");
  for(int d = 0; d  < deg; d++){
    for(int r = 0; r < rings; r++){
      
       output.print(logscalar(rings,(int)red(buffer[d][r])));
       output.print(",");

       
    }
  }
  
  for(int d = 0; d  < deg; d++){
    for(int r = 0; r < rings; r++){
      
       myPort.write((char)logscalar(rings,(char)red(buffer[d][r])));

       
    }
  }

    
  /*for(int x = 0; x  < size; x++){
    for(int y = 0; y < size; y++){
      int d = (int)Math.round(Math.toDegrees(Math.atan( -((y-offset)+.5) / ((x-offset)+.5) ))*10);
      int r =  (int)Math.round(sqrt( (float)( ((y-offset)+.5) * ((y-offset)+.5) ) + (float)( ((x-offset)+.5) * ((x-offset)+.5) )));
      if((x-offset) < 0) d += 3600;
      else d += 1800;
      d %= 3600;
      d = 2;
      double x2 = Math.cos(Math.toRadians((double)d/10))*r;
      double y2 = Math.sin(Math.toRadians((double)d/10))*r;
      set((int)x2+width/2, (int)y2+height/2, buffer[d][r]);
    }
  }*/
      
  for(int d = 0; d  < deg; d++){
    for(int r = 0; r < rings; r++){
      int y = -(int)Math.round(Math.cos(Math.toRadians((double)d/div))*r);
      int x = (int)Math.round(Math.sin(Math.toRadians((double)d/div))*r);
      set(x+width/2, y+height/2, color(green(buffer[d][r])));
      img.set(x+img.width/2, y+img.height/2, color(logscalar(rings,(int)red(buffer[d][r]))/256));
    }
  }
    img.resize(width/4,height/4);
   //image(img, width/2, height/2);
  image(img, 0, 0);
  //image(imp, 0, 0);
  /*for(double d = 0; d  < 360; d += .1){
    int r = 20;
      int x = (int)Math.round(Math.cos(Math.toRadians(d))*r);
      int y = (int)Math.round(Math.sin(Math.toRadians(d))*r);
      set(x+width/2, y+height/2, buffer[(int)(d*10)][r]);
  }*/
}
int logscalar(double base,int brightness){
  double part = ((1+brightness)*(1+brightness))-1;
  return (int)(part);
  
}
void draw() {
} 
