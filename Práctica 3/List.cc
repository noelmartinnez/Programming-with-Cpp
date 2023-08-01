#include "List.h"
#include "Util.h"
#include "Task.h"
#include <iostream>
using namespace std; 

//Constructor que creará la list con el nombre pasado por parametro
List::List(string name){
    if(name == ""){
        throw ERR_EMPTY;
    }
    else{
        this->name=name;
    }
}

//Devuelve la cantidad de tareas de la list
unsigned List::getNumTasks() const{
    return tasks.size();
}

//Devuelve la cantidad de tareas completadas de la list
unsigned List::getNumDone() const{
    int contadorDone=0;
    
    for(unsigned i=0;i<tasks.size();i++){
        if(tasks[i].getIsDone() == true){
            contadorDone++;
        }
    }
    return contadorDone;
}

//Devuelve la cantidad de tiempo de las tareas de la list
int List::getTimeTasks() const{
    int totalTime=0;
    
    for(unsigned i=0;i<tasks.size();i++){
        totalTime=totalTime+tasks[i].getTime();
    }  
    return totalTime;
}

//Devuelve la cantidad de tiempo de las tareas completadas de la list
int List::getTimeDone() const{
    int totalTimeDone=0;
    
    for(unsigned i=0;i<tasks.size();i++){
        if(tasks[i].getIsDone() == true){
            totalTimeDone=totalTimeDone+tasks[i].getTime();
        }
    }  
    return totalTimeDone;
}

//Devuelve la posicion de la task con el nombre name, si no existe en el vector tasks
//devolverá -1
int List::getPosTask(string name) const{
     for(unsigned z=0;z<tasks.size();z++){
        if(tasks[z].getName() == name){
            return z;
        }
    }
    
    return -1;
}

//Función para cambiar el nombre de la list, si name es vacio, devolverá false
bool List::setName(string name){
    bool setNameList=false;
    
    if(name == ""){
        Util::error(ERR_EMPTY);
        return setNameList;
    }
    else{
        this->name=name;
        setNameList=true;
        return setNameList;
    }
}

//Añade una tarea al vector tasks
void List::addTask(Task task){
    tasks.push_back(task);
}

//Borra todas las tasks con nombre name
bool List::deleteTask(string name){
    int existPosicion=0;
    bool returnDeleteTask=false;
        
    if(getPosTask(name) >= 0){
        
        //Mientras que hayan posiciones, irá borrando del vector
        while(existPosicion != -1){
            existPosicion=getPosTask(name);
            
            if(existPosicion >= 0){
                tasks.erase(tasks.begin()+existPosicion);
            }
        }
        
        returnDeleteTask=true;
        return returnDeleteTask;
    }
    else{
        Util::error(ERR_TASK_NAME);
        return returnDeleteTask;
    }
}

//Cambia el estado del campo isDone de todas las tasks con nombre name
bool List::toggleTask(string name){
    bool returnToggleTask=false;
    
    for(unsigned i=0;i<tasks.size();i++){
        if(tasks[i].getName() == name){
            tasks[i].toggle();
            returnToggleTask=true;
        }
    }
        
    if(returnToggleTask == false){
            Util::error(ERR_TASK_NAME);
    }
    
    return returnToggleTask;
}

//Llamada al objeto list, y vista de sus datos
ostream& operator<<(ostream &os,const List &list){
    os <<list.name<<endl;
    
    //Primero se muestran las tasks sin completar
    for(Task t:list.tasks){
        if(!t.getIsDone()){
            os<<t<<endl;
        }
    }
    

    for(Task t:list.tasks){
        if(t.getIsDone()){
            os<<t<<endl;
        }
    }        
    return os;
}







