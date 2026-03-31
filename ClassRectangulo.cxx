#include <string>
#include <iostream>
using namespace std;

class Rectangulo{
    private:
    double base, altura;
    bool validar(double b, double h){
        return (b>0)&&(h>0);
    }
    
    public:
    
    //constructor
    Rectangulo(double b, double h){
        if (validar(b,h))  {
            base=b;
        altura=h;
        cout<<"se ha creado el rectángulo de base "<<base<<" y altura "<<altura<<endl;
    }else{
        cout<<" No se ha podido crear el rectángulo, su base o altura están fuera de rango. Se establecerán sus dimensiones por defecto : base=1 ; altura=1"<<endl;
        base=1;
        altura=1;
        }
    }
   // getters
   double getBase(){return base;}
   double getAltura(){return altura;}
   
  // setters
  void setBase(double nuevaB){
      if(nuevaB>0){
          base=nuevaB;
      }else{
          cout<<"Error: Base fuera de rango. No se puede modificar. "<<endl;
      }
  }
  void setAltura(double nuevaA){
      if( nuevaA>0){
          altura=nuevaA;
      }else{
          cout<<"Error: Altura fuera de rango. No se puede modificar. "<< endl;
      }
  }
  double calcularA(){
      return (base*altura);
  }
  double calcularP(){
      return (2*(base+altura));
  }
};
  
  int main (){
      
      Rectangulo r1(3.5,2.0);
      
      cout<<" El rectangulo tiene base= "<<   r1.getBase()<< " y altura = "<<                         r1.getAltura()<<endl;
      
       cout<<"Área del rectangulo : "<<r1.calcularA()<<" unidades cuadradas  "<<endl;
       cout<<"Perimetro del rectangulo : "<<r1.calcularP()<< " unidades "<<endl;
       r1.setBase(-1.0);
       r1.setAltura(0.0);
       Rectangulo r2(-1.0,0.0);
       
       
      
      return 0;
  }