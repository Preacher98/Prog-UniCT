Ball[] baloon;
void setup() {
  size(640, 360);
   baloon = new Ball[6];
  for (int i=0; i<6; i++) {
    baloon[i] = new Ball();
  }
}

void draw() {
  background(120);

  for (int i=0; i<6; i++) {
    baloon[i].moving();
    baloon[i].bal();
  }
}
