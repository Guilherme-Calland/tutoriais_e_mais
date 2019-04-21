Perceptron percept;

Point[] points = new Point[100];

int trainingIndex = 0;
void setup(){
  size(500, 500);
  percept = new Perceptron();
  
  for(int i = 0; i < points.length; i++){
      points[i] = new Point();
  }
  /*
  float[] inputs = {-1, 0.5};
  int guess = percept.guess(inputs);
  println(guess);
  */
}

void draw() {
  background(255);//cor de fundo
  stroke(0);// cor da linha
  line(0, 0, width , height); //linha que começa do ponto(0,0) ate o ponto(width,height) (limite da tela)
  
  for(Point p : points){
     p.show(); 
  }
 
  
  for ( Point p : points) {
    float[] inputs = {p.x, p.y}; 
    int target = p.label;
    //percept.train(inputs, target);
    
    int guess = percept.guess(inputs);
    if(guess == target) {
        fill(0, 255, 0);
    } else {
        fill(255, 0, 0);
    }
    noStroke();
    ellipse(p.x, p.y, 8, 8);  
  }
  
  Point training =  points[trainingIndex];
  float[] inputs = {training.x, training.y};
  int target = training.label;
  percept.train(inputs, target);
  trainingIndex++;
  if (trainingIndex == points.length){
   trainingIndex = 0; 
  }
}

void mousePressed() {
  
  for ( Point p : points) {
    float[] inputs = {p.x, p.y}; 
    int target = p.label;
    percept.train(inputs, target);
  }
}
