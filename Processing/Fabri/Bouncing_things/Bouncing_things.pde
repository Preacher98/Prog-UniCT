void setup() {
  size(640, 360);
  background(0);
}
  float gravity = 0.5;
  float squareX=1;
  float speed=5;
  float squareY=1;
void draw() {

  //background(mouseX, mouseY, 50);
  background(0);
  stroke(255);
  strokeWeight(5);
  fill(mouseX, mouseY, 0);
  //Disegna il cerchio nella posizione X
  circle(mouseX, mouseY, 50);
  speed -= gravity;
  squareX+=speed;
  squareY+=speed;
  if((squareX >= width || squareX <= 0) || (squareY >= height || squareY <= 0)){speed *= -gravity;}
  println(squareX,squareY);
  square(squareX, squareY, 100);
}

void mousePressed() {
  speed = random(1,8);
}
