//1. for every input, multiply that input by its weight.
//2. Sum all of the weighted inputs
//3. Compute the putput based on the funcion (the sign of the sum)

class Perceptron{
  float[] weights = new float[2];
  float learning_rate = 0.1;
  
  //constructor
  void Peceptron() {
    
    
    for (int i = 0; i < weights.length ; i++){
      weights[i] = random(-1, 1);
    } 
    
    
    /*
    weights[0] = 5;
    weights[1] = 5;
    */
    
  } 
  
  //teste
  int guess(float[] inputs) {
    float sum = 0;
    for (int i = 0; i < weights.length; i++){
      sum += inputs[i]*weights[i];
    }
    
    int output = sign(sum);
    return output;
  }
  
  //recalcula os pesos
  void train(float [] inputs, int target){
      //target é a classe real do elemento
      int guess = guess(inputs);
      int error = target - guess;
      
      for( int i = 0; i < weights.length; i++){
         weights[i] += (error*inputs[i]) * learning_rate; 
      }
  }
  
}


//activation function
int sign(float sum){
  if(sum >= 0){
    return 1;
  } else {
    return -1;
  }
}
