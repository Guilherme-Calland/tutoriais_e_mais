

class Point{
  float x;
  float y;
  int label;

  Point() {
    x = random(width); //width é a largura da tela
    y = random(height); //height é a altura da tela 
    
    if(x > y){
      label = 1;
    } else {
      label = -1;  
    }
  } 
  //no caso, todos que estiverem acima da linha y = x serão classe: 1
  //lembrando que o ponto (0,0) começa no canto esquerdo superior da tela
  
  void show(){
    stroke(0);
    if( label == 1 ){
      fill(255);
    } else {
      fill(0);
    }
    ellipse(x, y, 16, 16);
  }
}
