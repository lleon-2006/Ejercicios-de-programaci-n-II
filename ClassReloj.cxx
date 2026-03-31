#include <string>
#include <iostream>
using namespace std;

class Reloj{
    private:
    int horas,minutos, segundos;
      bool validarHora(int h, int m, int s) {
        return (h >= 0 && h <= 23) && 
               (m >= 0 && m <= 59) && 
               (s >= 0 && s <= 59);
      }
    
    public:
    //constructor 
    Reloj(int h, int m,int s){
        if(validarHora(h,m,s)){
            horas=h;
            minutos=m;
            segundos=s;
            cout<< "Se ha creado el reloj marcando las "<< horas<< ": " << minutos<< ": " << segundos<< endl;
            
             
         
     }else{
         cout<<" Tiempo fuera de rango. Inicializando Reloj en 00: 00: 00 "<<endl;
         horas=0;
         minutos=0;
         segundos=0;
        }
    }
    
    //getters
    
    int gethoras(){return horas;}
    int getminutos(){return minutos;}
    int getsegundos(){return segundos ;}
    
    int avanzarS(){
         segundos++;
         if(segundos ==60){
             segundos=0;
             minutos++;
             if(minutos ==60){
                 minutos=0;
                 horas++;
                 if(horas==24){
                     horas=0;
                     cout<< " Nuevo dia"<<endl;
                 }
             }
         }
         cout << "La hora cambio : " << horas<< ": " <<minutos<< ": " <<segundos<< endl;
         }
    void mostrarH(){
         cout<< "Son las : " <<horas<< ": "<< minutos<< ": "<< segundos << endl;
    }
};
    int main(){
         
         
         Reloj r1(23, 59,59);
         
         r1.mostrarH();
         r1.avanzarS();
         
       
       
       Reloj r2(24,-2,33);
         
         
         return 0;
    }
         
         
        
        
        
        
         