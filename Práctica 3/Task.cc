#include "Task.h"
#include "Util.h"
#include <iostream>
#include <sstream>
using namespace std;

const int TIMEINI =1;
const int TIMEFIN =180;
const int ANYO1 = 2000;
const int ANYO2 = 2100;
const int MESF = 12;
const int BIS4 = 4;
const int BIS100 = 100;
const int BIS400 = 400;

// Extraemos la fecha antes del /
string extraerFecha(string cadenaFecha){
  string stringFecha="";

  // Recorremos hasta encontrar los primeros "/"  
  for(unsigned i=0;i<cadenaFecha.find("/");i++){
    stringFecha+=cadenaFecha[i];
  }
  
  return stringFecha;
}

// Extraemos la cadena después del /
string extraerContenido(string contenidoFecha){
  string extraccion="";

  //Se copia a partir de "/"
  for(unsigned i=contenidoFecha.find("/")+1;i<contenidoFecha.length();i++){
    extraccion+=contenidoFecha[i];
  }

  return extraccion;
}

//Función para comprobar que la fecha es correcta
bool correctDate(int numeroDay,int numeroMonth,int numeroYear){                                            
    int mesDias[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};
    
    //Comprueba si el año es bisiesto, si es así se suma un día a febrero
    if((numeroYear%BIS4 == 0 && numeroYear%BIS100 != 0) || numeroYear%BIS400 == 0){    
        mesDias[TIMEINI]++;                                                               
    } 
       
    //Se comprueba que el año esté entre [2000,2100]   
    if(numeroYear < ANYO1 || numeroYear > ANYO2){                              
        return false;
    } 
    
    //Se comprueba que el mes esté entre [1,12]
    if(numeroMonth < TIMEINI || numeroMonth > MESF){                                    
        return false;
    }
    
    numeroMonth = numeroMonth-TIMEINI;
    
    //Se comprueba que el día es mayor que cero y no supera el máximo de días de su mes
    if(numeroDay <= 0 || numeroDay > mesDias[numeroMonth]){                   
        return false;
    }

        return true;                                                                
}

//Constructor que creará la task con el nombre pasado por parametro
Task::Task(string name){
    this->name=name;
    time=1;
    deadline.day=1;
    deadline.month=1;
    deadline.year=2000;
    isDone=false;
}

//Función para cambiar el nombre de la task
void Task::setName(string name){
    this->name=name;
}

//Función para cambiar el valor deadline, si se puede cambiar devuelve true; en caso contrario false
bool Task::setDeadline(string deadline){
    string numDia,numMes,numAnyo,cadenaMes;
    int numDay,numMonth,numYear;
    bool booleanoFecha=false;
    
    //Como se pasa un string,hay que convertir los trozos del string 
    //en números
    numDia=extraerFecha(deadline);
    istringstream(numDia) >> numDay;
                
    cadenaMes=extraerContenido(deadline);
    numMes=extraerFecha(cadenaMes);
    istringstream(numMes) >> numMonth;
                
    numAnyo=extraerContenido(cadenaMes);
    istringstream(numAnyo) >> numYear;
    
    //Se comprueba que sea correcta la fecha
    booleanoFecha=correctDate(numDay,numMonth,numYear);
    
    //Si es correcta se cambia en la task
    if(booleanoFecha == true){
        this->deadline.day=numDay;
        this->deadline.month=numMonth;
        this->deadline.year=numYear;
    }
    else{
        Util::error(ERR_DATE);
    }
    return booleanoFecha;
}

//Función para cambiar el valor time, si se puede cambiar devuelve true; en caso contrario false
bool Task::setTime(int time){
    bool setTimeTask=false;
    
    //Se comprueba que sea correcto el time pasado por parametro
    if((time >= TIMEINI)&&(time <= TIMEFIN)){
        this->time=time;
        setTimeTask=true;
        return setTimeTask;
    }
    else{
        Util::error(ERR_TIME);
        return setTimeTask;
    }
}

//Función para cambiar el valor del campo isDone
void Task::toggle(){
    isDone = !isDone;
}

//Llamada al objeto task, y vista de sus datos
ostream& operator<<(ostream &os,const Task &task){
    
    if(task.isDone == false){
        os<<"[ ] ("<<task.time<<") "<<task.deadline.year<<"-"<<task.deadline.month<<"-"<<task.deadline.day<<" : "<<task.name;
    }
    else{
        os<<"[X] ("<<task.time<<") "<<task.deadline.year<<"-"<<task.deadline.month<<"-"<<task.deadline.day<<" : "<<task.name;
    }
    
    return os;
}




