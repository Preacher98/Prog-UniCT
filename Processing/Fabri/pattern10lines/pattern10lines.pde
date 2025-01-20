void setup() {
  size(640, 360);
}

void draw() {
  int spacing =20;
  background(255);
  float x=0;
  float y=0;
  strokeWeight(4);
  for (x=0; x<width; x+=20) {
    for (y=0; y<height; y+=20) {
      float r = random(0, 1);
      if (r < 0.5) {
        line(x, y, x+spacing, y+spacing);
      } else {
        line(x, y+spacing, x+spacing, y);
      }
    }
  }
  noLoop();
}
