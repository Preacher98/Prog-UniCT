float circleX, circleY, speedY, speedX;
float R, G, B;
float radius = 30;
float squareX, squareY, dim;
float squareX1, squareY1;
boolean move=false;
void setup() {
  size(640, 320);
  background(120);
  speedX=random(2, 8);
  speedY=random(2, 8);
  circleX=width/2;
  circleY=40;
  R = random(0, 255);
  G = random(0, 255);
  B = random(0, 255);
  squareX1= width/2;
  squareY1= height/2;
  squareX= width/4;
  squareY= height/2;
  dim=45;
}

void draw() {
  background(120);
  if (mouseX >= squareX-dim && mouseX <= squareX+dim && mouseY >= squareY-dim && mouseY <= squareY+dim) {
    fill(R, G, B);
  }
  circle(circleX, circleY, radius*2);
  rectMode(CENTER);

  if (move == false) {
    circleY+=speedY;
    circleX+=speedX;
  }

  if (circleY >= height-radius || circleY <= radius) {
    speedY *= -1;
    R = random(0, 255);
    G = random(0, 255);
    B = random(0, 255);
  }
  if (circleX >= width-radius || circleX <= radius) {
    speedX *= -1;
    R = random(0, 255);
    G = random(0, 255);
    B = random(0, 255);
  }
  //square control 1
  fill(0,255,0);
  square(squareX, squareY, dim*2);

  fill(255,0,0);
  square(squareX1, squareY1, dim*2);
  if (mouseX >= squareX1-dim && mouseX <= squareX1+dim && mouseY >= squareY1-dim && mouseY <= squareY1+dim) {
    move=true;
  } else {
    move=false;
  }
}





void mousePressed() {
  
}
