void setup(){
  size(640,360);
}

void sunshine(float x, float y, float radius){
  fill(255,217,0);
  strokeWeight(2);
  circle(x,y,radius);
}
void lollipop(){
  strokeWeight(5);
  line(width/2,height, width/2, height-100);
}

void draw(){
  background(120);
  sunshine(50, 50, 90);
  lollipop();
  sunshine(width/2, height-110, 50);

}
