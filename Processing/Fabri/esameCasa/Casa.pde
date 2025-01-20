class Casa {

  float x, y;
  float speedX;
  float rad;

  Casa() {
    x = width/2 + random(-200, 200);
    y = height/2 + random(-100, 100);
    speedX = random(3, 8);
    rad = 30;
    rectMode(CENTER);
  }

  void show() {
    fill(250,220,10);
    square(x, y, rad);
    fill(255,0,0);
    triangle(x-15, y-15, x, y-15*2, x+15, y-15);
    
  }
  void move(){
    x+=speedX;
    if(x>=width || x<=0){speedX*=-1;}
  }
}
