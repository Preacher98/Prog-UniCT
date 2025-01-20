
void setup() {
  size(640, 360);
}

void draw() {
  background(255);
  /*float R = random(0, 255);
   float G = random(0, 255);
   float B = random(0, 255);*/
  float x1= 0;
  float y1= 5;
  float x2= width;
  float y2= 5;
  float x3= 5;
  float y3= 0;
  float x4= 5;
  float y4= height;
  noFill();
  strokeWeight(4);
  stroke(8);

  while (y1 <= height) {
    line(x1, y1, x2, y2);
    y1 += 20;
    y2 += 20;
  }
  while (x3 <= width) {
    line(x3, y3, x4, y4);
    x3 += 20;
    x4 += 20;
  }
}

void mousePressed() {
}
