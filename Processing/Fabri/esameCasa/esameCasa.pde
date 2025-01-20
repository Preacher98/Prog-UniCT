Casa[] Home;
Casetta[] littleHome;
void setup() {
  size(640, 360);
  Home = new Casa[10];
  for (int i=0; i<10; i++) {
    Home[i] = new Casa();
  }
  littleHome = new Casetta[5];
  for (int i=0; i<5; i++) {
    littleHome[i] = new Casetta();
  }
}

void draw() {
  background(0);

  for (int i=0; i<10; i++) {
    Home[i].move();
    Home[i].show();
  }
  
  for (int i=0; i<5; i++) {
    littleHome[i].move();
    littleHome[i].show();
  }
}
