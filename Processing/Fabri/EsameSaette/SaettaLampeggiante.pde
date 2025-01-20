class SaettaLampeggiante extends Saetta {
  float x, y;
  float speed;
  float dim;
  boolean flag;

  SaettaLampeggiante() {
    super();
    this.x = super.x;
    this.y = super.y;
    this.speed = super.speed;
    this.dim = super.dim;
    this.flag = true;
  }
  void show() {
    noStroke();
    fill(255);
    triangle(x, y, x+10, y-dim, x+20, y);
    triangle(x+20, y, x+30, y+dim, x+40, y);
  }

  void run() {
    if (frameCount%6 == 0)
    {
      if (flag) {
        flag=false;
      } else {
        flag=true;
      }
    }
    if (flag) {
      show();
    }

    y+=speed;
    x+=random(-5, 5);
    if (y>=height) {
      y=0;
    }
  }
}
