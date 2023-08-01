#include "Project.h"
#include "List.h"
#include "Util.h"
#include "string.h"
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

const string PROYECT_NAME = "Enter project name: ";   
const string LIST_NAME = "Enter list name: ";       
const string TASK_NAME = "Enter task name: ";   
const string DEADLINE = "Enter deadline: ";
const string TIME = "Enter expected time: ";
const string PROYECT_DESCRIPTION = "Enter project description: ";    

//Constructor que creará el project con el nombre pasado por parametro
//Si name es vacio se lazará una escepción, pero la descripción se puede quedar vacia
Project::Project(string name, string description){
    if(name == ""){
        throw ERR_EMPTY;
    }
    else{
        this->name=name;
        this->description=description;
        id=0;
    }
}

//Devuelve la posicion de la list con el nombre name, si no existe en el vector lists
//devolverá -1
int Project::getPosList(string name) const{
     for(unsigned i=0;i<lists.size();i++){
        if(lists[i].getName() == name){
            return i;
        }
    }
    
    return -1;
}

//Permite cambiar el valor id, solo si es mayor o igual a 0
bool Project::setId(int id){
    bool comprobarSetIdProject=false;
    
    if(id<0){
        Util::error(ERR_ID);
        return comprobarSetIdProject;
    }
    else{
        this->id=id;
        comprobarSetIdProject=true;
        return comprobarSetIdProject;
    }
}

//Función para cambiar el nombre del project, si name es vacio, devolverá false
bool Project::setName(string name){
    bool comprobarSetNameProject=false;
    
    if(name == ""){
        Util::error(ERR_EMPTY);
        return comprobarSetNameProject;
    }
    else{
        this->name=name;
        comprobarSetNameProject=true;
        return comprobarSetNameProject;
    }
}

//Función para cambiar la descripción del project
void Project::setDescription(string description){
    this->description=description;
}

//Función que permite cambiar el nombre y la descripción del project
void Project::edit(string name,string description){
     bool correctNameProject=false;
     string auxNameEdit;
     
     
     if(name == ""){
        do{                                                                        
            cout<<PROYECT_NAME;
            getline(cin,auxNameEdit,'\n');
        
            if(auxNameEdit == ""){
                Util::error(ERR_EMPTY);
            }
            else{
                correctNameProject = true;
            }
        }while(correctNameProject == false);
        
        this->name=auxNameEdit;
        
        if(description != ""){
            this->description=description;
        }
        else{
            cout<<PROYECT_DESCRIPTION;                                                  
            getline(cin,this->description,'\n');
        }
     }
     else{
         this->name=name;
         
         if(description != ""){
            this->description=description;
        }
        else{
            cout<<PROYECT_DESCRIPTION;                                                  
            getline(cin,this->description,'\n');
        }
    }
}

//Función para añadir una list al vector lists
void Project::addList(string name){
    string addListName; 
    bool addCorrectName=false;
    
    if(name == ""){
         do{                                                                        
            cout<<LIST_NAME;
            getline(cin,addListName,'\n');
        
            if(addListName == ""){
                Util::error(ERR_EMPTY);
            }
            else{
                addCorrectName = true;
            }
        }while(addCorrectName == false);
        
        if(getPosList(addListName) >= 0){
            Util::error(ERR_LIST_NAME);
        }
        else{
            //Se intenta crear una list con try catch, si falla algo no se creará
            try{
                List newList(addListName);
                lists.push_back(newList);
            }
            catch(Error e){
                Util::error(e);
            }
        }
    }
    else{
        if(getPosList(name) >= 0){
            Util::error(ERR_LIST_NAME);
        }
        else{
            try{
                List newList(name);
                lists.push_back(newList);
            }
            catch(Error e){
                Util::error(e);
            }
        }
    }
}

//Función para eliminar una list del vector lists
void Project::deleteList(string name){
    string nameList;
    bool correctNameList=false;
    
    if(name == ""){
        do{                                                                        
            cout<<LIST_NAME;
            getline(cin,nameList,'\n');
        
            if(nameList == ""){
                Util::error(ERR_EMPTY);
            }
            else{
                correctNameList = true;
            }
        }while(correctNameList == false);
        
        //Si existe la list con el nombre introducido se borrará
        if(getPosList(nameList) >= 0){
            lists.erase(lists.begin()+getPosList(nameList));
        }
        else{
            Util::error(ERR_LIST_NAME);
        }
    }
    else{
        if(getPosList(name) >= 0){
            lists.erase(lists.begin()+getPosList(name));
        }
        else{
            Util::error(ERR_LIST_NAME);
        }
    }
}

//Función para introducir una task en el vector tasks de la list con el nombre introducido por parametro
//o por el usuario
void Project::addTaskToList(string name){
    string nameAddTask,nameAddTaskDeadline;
    int timeTaskAdd,posicionAddTask;
    bool correctListAddTask=false;
    
    if(name == ""){
        do{                                                                        
            cout<<LIST_NAME;
            getline(cin,name,'\n');
        
            if(name == ""){
                Util::error(ERR_EMPTY);
            }
            else{
                correctListAddTask = true;
            }
        }while(correctListAddTask == false);
    }
        
        posicionAddTask=getPosList(name);
        
        if(posicionAddTask == -1){
            Util::error(ERR_LIST_NAME);
        }
        else{
            
            //Si existe la lista, se pedirán todos los datos para 
            //crear la task correspondiente
            cout<<TASK_NAME;
            getline(cin,nameAddTask,'\n');
            
            Task newTask(nameAddTask);
            
            cout<<DEADLINE;
            getline(cin,nameAddTaskDeadline,'\n');
            
            if(newTask.setDeadline(nameAddTaskDeadline) == true){

                cout<<TIME;
                cin>>timeTaskAdd;
                cin.get();
            
                if(newTask.setTime(timeTaskAdd) == true){
                    
                    //Si todo es correcto se introduce la task
                    lists[posicionAddTask].addTask(newTask);
                }
            }
        }
}

//Función que borra todas las tasks de la list de nombre name
void Project::deleteTaskFromList(string name){
    string nameTaskToDelete,nameListDeleteTask;
    bool correctListDeleteTask=false;
    
    if(name == ""){
        do{                                                                        
            cout<<LIST_NAME;
            getline(cin,nameListDeleteTask,'\n');
        
            if(nameListDeleteTask == ""){
                Util::error(ERR_EMPTY);
            }
            else{
                correctListDeleteTask = true;
            }
        }while(correctListDeleteTask == false);
        
        if(getPosList(nameListDeleteTask) >= 0){
            cout<<TASK_NAME;
            getline(cin,nameTaskToDelete,'\n');
            
            //Si existe la task con el nombre introducido en la list, se llamará a la función deleteTask()
            //que eliminará todas con ese nombre
            if(lists[getPosList(nameListDeleteTask)].getPosTask(nameTaskToDelete) >= 0){
                lists[getPosList(nameListDeleteTask)].deleteTask(nameTaskToDelete);
            }
            else{
                Util::error(ERR_TASK_NAME);
            }
        }
        else{
            Util::error(ERR_LIST_NAME);
        }
    }
    else{
        if(getPosList(name) >= 0){
            cout<<TASK_NAME;
            getline(cin,nameTaskToDelete,'\n');
            
            if(lists[getPosList(name)].getPosTask(nameTaskToDelete) >= 0){
                lists[getPosList(name)].deleteTask(nameTaskToDelete);
            }
            else{
                Util::error(ERR_TASK_NAME);
            }
            
        }else{
            Util::error(ERR_LIST_NAME);
        }
    }
}

//Función que cambia todos los campos isDone de  todas las tasks de la list de nombre name
void Project::toggleTaskFromList(string name){
    string nameListToggleTask,nameTaskToToggle,nameTaskToToggleAux;
    bool correctListToggleTask=false;
    
    
    if(name == ""){
        do{                                                                        
            cout<<LIST_NAME;
            getline(cin,nameListToggleTask,'\n');
        
            if(nameListToggleTask == ""){
                Util::error(ERR_EMPTY);
            }
            else{
                correctListToggleTask = true;
            }
        }while(correctListToggleTask == false);
        
        if(getPosList(nameListToggleTask) >= 0){
            cout<<TASK_NAME;
            getline(cin,nameTaskToToggle,'\n');
            
            //Si existe la task con el nombre introducido en la list, se llamará a la función toggleTask()
            //que cambiará todas con ese nombre
            if(lists[getPosList(nameListToggleTask)].getPosTask(nameTaskToToggle) >= 0){
                lists[getPosList(nameListToggleTask)].toggleTask(nameTaskToToggle);
            }
            else{
                Util::error(ERR_TASK_NAME);
            }
        }
        else{
            Util::error(ERR_LIST_NAME);
        }
    }
    else{
        if(getPosList(name) >= 0){
            cout<<TASK_NAME;
            getline(cin,nameTaskToToggleAux,'\n');
            
            if(lists[getPosList(name)].getPosTask(nameTaskToToggleAux) >= 0){
                lists[getPosList(name)].toggleTask(nameTaskToToggleAux);
            }
            else{
                Util::error(ERR_TASK_NAME);
            }
            
        }else{
            Util::error(ERR_LIST_NAME);
        }
    }    
}

//Función que nos permite ver el menú de los projectos, y movernos por el
//y utilizar las diferentes funciones
void Project::menu(){
    char opcionMenu;
    
     do{
        cout << "1- Edit project" << endl
             << "2- Add list" << endl
             << "3- Delete list" << endl 
             << "4- Add task" << endl
             << "5- Delete task" << endl
             << "6- Toggle task" << endl
             << "7- Report" << endl
             << "b- Back to main menu" << endl
             << "Option: ";
         
        cin >> opcionMenu;
        cin.get();
    
        //Switch como en la practica 2, que sirve para moverse por las opciones de edición del project llamado
        switch(opcionMenu){
            case '1': edit();
                    break;
            case '2': addList();
                    break;
            case '3': deleteList();
                    break;
            case '4': addTaskToList();
                    break;
            case '5': deleteTaskFromList();
                    break;
            case '6': toggleTaskFromList();
                    break;
            case '7': cout<<*this<<endl;
                    break;
            case 'b': break;
            default: Util::error(ERR_OPTION);
        }
    }while(opcionMenu!='b');
}

//Función que devuelve un string con el contenido del project
string Project::summary() const{
    stringstream ssId,ssDone,ssTotal;
    string summaryString="",numIdString,numTotalString,numDoneString;
    int numeroTotalDone=0,numeroTotalTasks=0;
    
    //Pasamos los int a string
    ssId<<getId();
    numIdString=ssId.str();
    
    //Calcula el numero total de tasks del project
    for(unsigned i=0;i<lists.size();i++){
        numeroTotalTasks=numeroTotalTasks+lists[i].getNumTasks();
    }
    
    //Calcula el numero total de tasks completadas del project
    for(unsigned j=0;j<lists.size();j++){
        numeroTotalDone=numeroTotalDone+lists[j].getNumDone();
    }

    ssTotal<<numeroTotalTasks;
    numTotalString=ssTotal.str();
    
    ssDone<<numeroTotalDone;
    numDoneString=ssDone.str();    
    
    //Añadimos todo a un único string
    summaryString+="("+numIdString+")"+" "+getName()+" "+"["+numDoneString+"/"+numTotalString+"]";
    
    return summaryString;
}

//Llamada al objeto project, y vista de sus datos
ostream& operator<<(ostream &os,const Project &project){
    int totalLeft=0,totalDone=0,totalMinutesLeft=0,totalMinutesDone=0;
    string highestTask;
    Date fechaAux;
    
    //Creo una fecha auxiliar
    fechaAux.day=31;
    fechaAux.month=12;
    fechaAux.year=2100;
    
    os<<"Name: "<<project.name<<endl;
    
    if(project.description != ""){
        os<<"Description: "<<project.description<<endl;
    }

    //Se muestran la informacion de todo el vector lists
    for(List l:project.lists){
        os<<l;
    }
    
    //Calcula el numero de tasks completadas y su total de minutos
    for(unsigned i=0;i<project.lists.size();i++){
        totalDone=project.lists[i].getNumDone() + totalDone;
        totalMinutesDone=project.lists[i].getTimeDone() + totalMinutesDone;
        
    }
    
    //Calcula el numero de tasks  sin completar y su total de minutos
    for(unsigned j=0;j<project.lists.size();j++){
        totalLeft=(project.lists[j].getNumTasks() - project.lists[j].getNumDone()) + totalLeft;
        totalMinutesLeft=(project.lists[j].getTimeTasks() - project.lists[j].getTimeDone()) + totalMinutesLeft;
    }
    
    //Compruebo la task más antigua y sus valores de fecha
    for(unsigned x=0;x<project.lists.size();x++){   
        vector<Task> tareas=project.lists[x].getTasks();
        
        for(unsigned y=0;y<project.lists[x].getNumTasks();y++){                                               
    
            if(tareas[y].getIsDone() == false){                                                   
                if(tareas[y].getDeadline().year < fechaAux.year){
                    fechaAux.year=tareas[y].getDeadline().year;
                    fechaAux.month=tareas[y].getDeadline().month;
                    fechaAux.day=tareas[y].getDeadline().day;
                    highestTask=tareas[y].getName();
                }
                else{
                    if(tareas[y].getDeadline().year == fechaAux.year){
                        if(tareas[y].getDeadline().month < fechaAux.month){
                            fechaAux.year=tareas[y].getDeadline().year;
                            fechaAux.month=tareas[y].getDeadline().month;
                            fechaAux.day=tareas[y].getDeadline().day;
                            highestTask=tareas[y].getName();
                        }
                        else{
                            if(tareas[y].getDeadline().month == fechaAux.month){
                                if(tareas[y].getDeadline().day < fechaAux.day){
                                    fechaAux.year=tareas[y].getDeadline().year;
                                    fechaAux.month=tareas[y].getDeadline().month;
                                    fechaAux.day=tareas[y].getDeadline().day;
                                    highestTask=tareas[y].getName();
                                }
                                else{
                                    
                                    //Si llega una tarea con la misma fecha, solo se tendrá en cuenta la primera, por eso no se actualiza sino que se introduce la misma fecha
                                    if((tareas[y].getDeadline().day == fechaAux.day) && (tareas[y].getDeadline().month == fechaAux.month) && (tareas[y].getDeadline().year == fechaAux.year)){
                                        
                                            fechaAux.year=fechaAux.year;
                                            fechaAux.month=fechaAux.month;
                                            fechaAux.day=fechaAux.day;
                                            highestTask=highestTask;
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }  
    
    os<<"Total left: "<<totalLeft<<" ("<<totalMinutesLeft<<" minutes)"<<endl;
    os<<"Total done: "<<totalDone<<" ("<<totalMinutesDone<<" minutes)"<<endl;
    
    //Si no hay tareas sin completar no se muestra
    if(totalLeft != 0){
        os<<"Highest priority: "<<highestTask<<" ("<<fechaAux.year<<"-"<<fechaAux.month<<"-"<<fechaAux.day<<")"<<endl;
        
    }
    
    return os;
}








