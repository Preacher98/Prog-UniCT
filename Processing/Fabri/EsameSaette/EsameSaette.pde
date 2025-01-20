ArrayList<Saetta> sat = new ArrayList<Saetta>();
int list=0;
void setup() {
  size(800, 800);
}

void draw() {
  background(0);

  for (int i=0; i<sat.size(); i++) {
    sat.get(i).run();
  }
}

void mouseClicked() {
  if (mouseButton==LEFT) {
    sat.add(new Saetta());
  }
  if (mouseButton==RIGHT) {
    sat.add(new SaettaLampeggiante());
  }
}

void keyPressed() {
  if (key == 'r' || key == 'R') {
    for (int i=sat.size()-1; i>=0; i--) {
      sat.remove(i);
    }
  }
}
