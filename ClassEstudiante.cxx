#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Estudiante{
    private:
    string nombre;
    string carnet;
    vector <double> notas;
    
    
    
    public:
     // constructor
     Estudiante(string nom, string id){
         nombre=nom;
         carnet=id;
         cout<<" Estudiante registrado "<< nombre<< "-> ID: "<< carnet<< endl;
     }
     
     string getNombre(){return nombre;}
     string getId(){return carnet;}
         
         void agregarCalificaciones(double calificacion){
             if(calificacion>=0&&calificacion<=100){
                 notas.push_back(calificacion);
                 cout<<"Calificacion agregada : "<< calificacion<<endl;
             }else{
                 cout<< "Calificacion invalida. Su nota debe estar entre 0 y 100"<<endl;
                 }
         }
         double calcularPromedio(){
             if(notas.empty()){
                 cout<<"(No hay calificaciones registradas)"<<endl;
                 return 0.0;
             }
                 
                 
             double suma=0;
             for(int i=0; i<notas.size();i++){
                 suma=notas.at(i)+suma;
             }
             return suma/notas.size();
         }
};

int main (){
                 
               Estudiante estudiante1("Luis","06022680480");
               
               estudiante1.agregarCalificaciones(100);
                 estudiante1.agregarCalificaciones(98);
                   estudiante1.agregarCalificaciones(90);
                     estudiante1.agregarCalificaciones(150);
                     
                   cout<< "Promedio del estudiante "<<estudiante1.getNombre()<<": "<< estudiante1.calcularPromedio()<<endl;
                   Estudiante estudiante2("Jose","84051960221");
                  cout<<  "Promedio del estudiante "<<estudiante2.getNombre()<<": "<<estudiante2.calcularPromedio();
                   
               
                 return 0; 
                 }
                 
         
                 
             
                 
             
         
     
     
    