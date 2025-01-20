class Casetta extends Casa {

  float x, y;
  float speedX;
  float rad;
  
  Casetta(){
    super();
    this.x = super.x;
    this.y = super.y;
    this.speedX = super.speedX;
    this.rad = super.rad;
  }
    void show() {
    fill(255);
    square(x, y, rad);
    fill(0,255,0);
    triangle(x-15, y-15, x, y-15*2, x+15, y-15);
    fill(0,0,255);
    square(x,y+10,10);
    
  }
  void move(){
    x-=speedX;
    if(x<=0){
    x=width+15;
  }
  }
}
