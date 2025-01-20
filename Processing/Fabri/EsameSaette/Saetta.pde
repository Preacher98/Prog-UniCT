class Saetta {

  float x, y;
  float speed, dim;

  Saetta() {
    x= width/2 + random(-300, 300);
    y= 0;
    speed = random(2, 10);
    dim = 80;
  }

  void display() {
    fill(245, 237, 0);
    triangle(x, y, x+10, y-dim, x+20, y);
    triangle(x+20, y, x+30, y+dim, x+40, y);
  }

  void move() {
    y+=speed;
    x+=random(-5,5);
    if (y>=height) {
      y=0;
    }
  }
  
  void run(){
    display();
    move();
  }

}
