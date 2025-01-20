void setup(){
  size(640,360);

}

void draw(){
  background(120);
    float[] fruitInv={50, 220, 40, 90, 110};
  int i=0;
  float y = 40;
  noFill();
  for(float x=0; i<5; x+= fruitInv[i++]){

    square(x,y,fruitInv[i]);
  }
  
}
