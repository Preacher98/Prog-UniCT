class Ball {
  float x, y;

  Ball() {
    x = width/2 + random(-200, 200);
    y = height;
  }

  void moving() {

      x += random(-2, 2);
      y -= random(1, 5);
 
  }

  void bal() {
    fill(255, 224, 12);
    circle(x, y, 60);
  }
}
