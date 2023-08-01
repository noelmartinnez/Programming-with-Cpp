//DNI: 48771960T NOEL MARTÍNEZ POMARES
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>
using namespace std;

const string PROYECT_NAME = "Enter project name: ";                             //AQUÍ DECLARO CONSTANTES TODAS LAS FRASES QUE LES APARECEREN A LOS USUARIOS,
const string PROYECT_DESCRIPTION = "Enter project description: ";               //COMO SALEN VARIAS VECES ES PREFERIBLE DECLARARLAS Y USARLAS DESPUÉS
const string LIST_NAME = "Enter list name: ";
const string TASK_NAME = "Enter task name: ";
const string DEADLINE = "Enter deadline: ";
const string TIME = "Enter expected time: ";

struct Date{
  int day;
  int month;
  int year;
};

struct Task{
  string name;
  Date deadline;
  bool isDone;
  int time;
};

struct List{
  string name;
  vector<Task> tasks;
};

struct Project{
  int id;
  string name;
  string description;
  vector<List> lists;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME
};

void error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty string" << endl;
      break;
    case ERR_LIST_NAME:
      cout << "ERROR: wrong list name" << endl;
      break;
    case ERR_TASK_NAME:
      cout << "ERROR: wrong task name" << endl;
      break;
    case ERR_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_TIME:
      cout << "ERROR: wrong expected time" << endl;
  }
}

void showMainMenu(){
  cout << "1- Edit project" << endl
       << "2- Add list" << endl
       << "3- Delete list" << endl 
       << "4- Add task" << endl
       << "5- Delete task" << endl
       << "6- Toggle task" << endl
       << "7- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void editProject(Project &toDoList){        // FUNCIÓN QUE NOS PERMITE INTRODUCIR EL NOMBRE Y LA DESCRIPCIÓN DEL PROYECTO
     bool correctProyectName=false;
     
     do{                                                                        //HAGO UN BUCLE DO-WHILE PARA QUE EL USUARIO INTRODUZCA UN NOMBRE DE PROYECTO CORRECTO
        cout<<PROYECT_NAME;
        getline(cin,toDoList.name,'\n');
        
        if(toDoList.name == ""){
            error(ERR_EMPTY);
            
        }else{
            correctProyectName = true;
        }
     }while(correctProyectName == false);
    
    cout<<PROYECT_DESCRIPTION;                                                  //LA DESCRIPCIÓN SE PUEDE QUEDAR VACIA SIN PROBLEMAS
    getline(cin,toDoList.description,'\n');
}

void checkList(Project &toDoList,bool &listDone,string listName){               //FUNCIÓN PARA COMPROBAR QUE LA LISTA INTRODUCIDA NO SE HABÍA INTRODUCIDO PREVIAMENTE
    
    for(unsigned i=0;i<toDoList.lists.size();i++){
        if(toDoList.lists[i].name == listName){
            listDone = true;
        }
    }
}

void addList(Project &toDoList){                     //FUNCIÓN QUE NOS PERMITE AÑADIR LISTAS A NUETRO PROYECTO
    bool correctList=false,listDone=false;
    List newList;
    string listName;
    
    do{                                                                         //BUCLE DO-WHILE PARA QUE EL USUARIO INTRODUZCA UN NOMBRE DE PROYECTO CORRECTO
        cout<<LIST_NAME;
        getline(cin,listName,'\n');

        if(listName == ""){
            error(ERR_EMPTY);
            
        }else{
            correctList = true;
        }
    }while(correctList == false);
     
    if(toDoList.lists.size() == 0){                                             //SI EL VECTOR LISTS ESTÁ VACIO SE ASIGNA EL NOMBRE DE LA LISTA AL VECTOR "newList" CREADO, Y DESPUÉS CON ".push_back" SE INTRODUCE AL FINAL DEL VECTOR LISTS
        newList.name = listName;                                                
        toDoList.lists.push_back(newList);
         
    }else{
        checkList(toDoList,listDone,listName);                                  //SI EL VECTOR LISTS NO ESTÁ VACIO, SE LLAMA A LA FUNCIÓN "checkList" PARA QUE COMPRUEBE QUE LA LISTA NO EXISTA AÚN, SI ES ASÍ SE INTRODUCE EL NOMBRE DE LA LISTA
                                                                                //AL FINAL DEL VECTOR LISTS, PERO SI LA LISTA YA EXISTIERA, SALDRÍA EL ERROR "ERR_LIST_NAME"
        if(listDone == true){                  
            error(ERR_LIST_NAME);
        
        }else{
            newList.name = listName;
            toDoList.lists.push_back(newList);                                               
        }
    }
}

void checkDeleteList(Project &toDoList,bool &correctDeleteList,string deleteName,int &pos){     //FUNCIÓN PARA COMPROBAR QUE LA LISTA INTRODUCIDA EXISTE EN EL VECTOR LISTS
    
    for(unsigned i=0;i<toDoList.lists.size();i++){
        if(toDoList.lists[i].name == deleteName){
            correctDeleteList = true;
            pos = i;
        }
    }
}

void deleteList(Project &toDoList){                         //FUNCIÓN QUE NOS PERMITE ELIMINAR LISTAS DE NUESTRO PROYECTO
    int pos=0;
    bool deleteList=false,correctDeleteList=false;
    string deleteName;
    
    do{
        cout<<LIST_NAME;                                                        //BUCLE DO-WHILE PARA QUE EL USUARIO INTRODUZCA UN NOMBRE DE PROYECTO CORRECTO
        getline(cin,deleteName,'\n');

        if(deleteName == ""){
            error(ERR_EMPTY);
        
        }else{
            deleteList = true;
        }
    }while(deleteList == false);

    checkDeleteList(toDoList,correctDeleteList,deleteName,pos);                 //SI EL NOMBRE ES CORRECTO SE LLAMA A LA FUNCIÓN "checkDeleteList" PARA QUE COMPRUEBE QUE LA LISTA INTRODUCIDA EXISTE 
    
    if(correctDeleteList == true){
            toDoList.lists.erase(toDoList.lists.begin()+pos);                   //SI LA LISTA EXISTE SE ELIMINA DEL VECTOR LISTS, USANDO EL COMANDO ".erase()" QUE GRACIAS A QUE HEMOS GUARDADO LA POSICIÓN DE LA LISTA, PODEMOS BORRAR ESA
                                                                                //EN CONCRETO, USANDO EL COMANDO ".erase(.begin()+posision)"
    }else{
        error(ERR_LIST_NAME);                                                      
    }
}

void checkAddTask(Project &toDoList,bool &correctAddTask,string listName2,int &posList){    //FUNCIÓN PARA COMPROBAR QUE LA LISTA INTRODUCIDA EXISTE EN EL VECTOR LISTS
    
    for(unsigned i=0;i<toDoList.lists.size();i++){
        if(toDoList.lists[i].name == listName2){
            correctAddTask = true;
            posList=i;
        }
    }
}

bool checkCorrectDate(Date newTask){                                            //FUNCIÓN PARA COMPROBAR QUE LA FECHA INTRODUCIDA ES CORRECTA
    int mesDias[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};
    
    if((newTask.year%4 == 0 && newTask.year%100 != 0) || newTask.year%400 == 0){    //ESTE IF COMPRUEBA SI EL AÑO ES BISIESTO O NO, YA QUE LO ES SI ES DIVISIBLE ENTRE 4 Y 400, Y SI NO LO ES ENTRE 100
        mesDias[1]++;                                                               //SI ES BISIESTO SE AÑADE UN DÍA AL MES DE FEBRERO
    } 
        
    if(newTask.year < 2000 || newTask.year > 2100){                                 //COMPRUEBA QUE EL AÑO ESTÉ EN EL RANGO [2000,2100]
        return false;
    } 
    
    if(newTask.month < 1 || newTask.month > 12){                                    //COMPRUEBA QUE EL MÉS ESTÉ EN EL RANGO [1,12]
        return false;
    }
    
    newTask.month = newTask.month-1;
    if(newTask.day <= 0 || newTask.day > mesDias[newTask.month]){                   //ESTE IF COMPRUEBA SI EL DÍA ES MAYOR QUE 0 Y SI NO SUPERA EL MÁXIMO DE DÍAS DEL MES INTRODUCIDO
        return false;
    }

        return true;                                                                //SI LO ANTERIOR ES CORRECTO SE DEVOLVERÁ "true"
}

void addTask(Project &toDoList){                      //FUNCIÓN QUE NOS PERMITE AÑADIR TAREAS A NUESTRAS LISTAS
    int numCadena,posList;
    bool correctList_Task=false,correctAddTask=false,correctDate=false;
    string listName2,taskName;
    Task newTask;
    char primeraBarra,segundaBarra;

    do{
        cout<<LIST_NAME;                                                        //BUCLE DO-WHILE PARA QUE EL USUARIO INTRODUZCA UN NOMBRE DE PROYECTO CORRECTO
        getline(cin,listName2,'\n');
    
        if(listName2 == ""){
            error(ERR_EMPTY);
        
        }else{
            correctList_Task = true;
        }
    }while(correctList_Task == false);
     
    checkAddTask(toDoList,correctAddTask,listName2,posList);                    //SI LA LISTA ES CORRECTA SE LLAMA A LA FUNCIÓN "checkAddTask" QUE COMPRUEBA QUE LA LISTA INTRODUCIDA EXISTA, ES CASO CONTRARIO EMITIRÁ UN ERROR
    
    if(correctAddTask == true){
        cout<<TASK_NAME;
        getline(cin,taskName,'\n');                                             //EN EL CASO DE QUE LA LISTA EXISTA SE UTILIZARÁ UN VECTOR AUXILIAR PARA QUE EL USUARIO INTRODUZCA EL DEADLINE DIRECTAMENTE 
        cout<<DEADLINE;
        cin>>newTask.deadline.day >> primeraBarra >> newTask.deadline.month >> segundaBarra >> newTask.deadline.year;  //DE ESTA FORMA NOS RESULTARÁ MÁS FACIL INTRODUCIR LA FECHA EN EL VECTOR DATE 

        correctDate = checkCorrectDate(newTask.deadline);                       //NECESITAMOS SABER SI LA FECHA INTRODUCIDA ES CORRECTA Y PARA ELLO NOS AYUDAMOS DE LA FUNCIÓN "checkCorrectDate" PASANDOLE EL VECTOR AUXILIAR CREADO
        
        if(correctDate == true){                                                //SI LA FECHA ES CORRECTA, SE PEDIRÁ AL USUARIO QUE INTRODUZCA EL TIEMPO EN EL RANGO [1,180], SI ESTÁ FUERA DEL RANGO SE EMITIRÁ UN ERROR
            cout<<TIME;
            cin>>numCadena;
            cin.get();
            
            if(numCadena >= 1 && numCadena <= 180){                             //SI ES CORRECTO, SE ASIGANRÁ EL NOMBRE Y EL TIEMPO INTRODUCIDO AL VECTOR AUXILIAR, Y DESPÚES SE INTRODUCIRÁ CON ".push_back" AL VECTOR "TASK", Y EL CAMPO "isDone"
                newTask.name = taskName;                                        //SE PONE COMO "false"
                newTask.time = numCadena;
                newTask.isDone = false;
                toDoList.lists[posList].tasks.push_back(newTask);            

            }else{
                error(ERR_TIME);
            }
        }else{
            error(ERR_DATE);
        }
    }else{
        error(ERR_LIST_NAME);
    }
}

void checkDelete_Task(Project &toDoList,bool &correctDelete_Task,string listName3,int &posList_Task){   //FUNCIÓN PARA COMPROBAR QUE LA LISTA INTRODUCIDA EXISTE EN EL VECTOR LISTS
    
    for(unsigned p=0;p<toDoList.lists.size();p++){
        if(toDoList.lists[p].name == listName3){
            correctDelete_Task = true;
            posList_Task=p;
        }
    }
}

void checkTaskName2(Project &toDoList,bool &correctTask_Name,string taskName2,int &posTask,int posList_Task,int &contador){     //FUNCIÓN PARA COMPROBAR QUE LA 'TASK' INTRODUCIDA EXISTE EN EL VECTOR TASKS, EL CONTADOR AUMENTARÁ POR CADA
                                                                                                                                //'TASK' CON EL NOMBRE INTRODUCIDO EN EL VECTOR LISTS
    for(unsigned z=0;z<toDoList.lists[posList_Task].tasks.size();z++){
            if(toDoList.lists[posList_Task].tasks[z].name == taskName2){
                    correctTask_Name=true;
                    posTask=z;
                    contador++;
            
        }
    }
}

void deleteTask(Project &toDoList){                         //FUNCIÓN QUE NOS PERMITE ELIMINAR TAREAS DE NUESTRAS LISTAS
    bool correctDelete_Task=false,correctTask_Name=false;
    string listName3,taskName2; 
    int posTask,posList_Task,contador=0;
    
    do{
        cout<<LIST_NAME;                                                        //BUCLE DO-WHILE PARA QUE EL USUARIO INTRODUZCA UN NOMBRE DE PROYECTO CORRECTO
        getline(cin,listName3,'\n');
    
        if(listName3 == ""){
            error(ERR_EMPTY);
    
        }else{
            correctDelete_Task = true;
        }
    }while(correctDelete_Task == false);

    checkDelete_Task(toDoList,correctDelete_Task,listName3,posList_Task);       //SI LA LISTA ES CORRECTA, LLAMAMOS A LA FUNCIÓN "checkDelete_Task" PARA COMPROBAR QUE LA LISTA EXISTE EN EL VECTOR LISTS

    if(correctDelete_Task == true){
        cout<<TASK_NAME;
        getline(cin,taskName2,'\n');
        
        do{
            if(contador != 0){                                                  //SE CREA UN CONTADOR POR SI HAY MÁS DE UNA 'TASK' CON EL NOMBRE INTRODUCIDO
                do{
                    contador--;
                }while(contador > 0);
            }
            
        checkTaskName2(toDoList,correctTask_Name,taskName2,posTask,posList_Task,contador);      //SI LA LISTA EXISTE SE LLAMA A LA FUNCIÓN "checkTaskName2" PARA COMPROBAR QUE LA 'TASK' EXISTA EN EL VECTOR TASKS
        
        if(correctTask_Name == true){
            toDoList.lists[posList_Task].tasks.erase(toDoList.lists[posList_Task].tasks.begin()+posTask);       //SI EXISTE SE ELIMINARÁ LA POSICIÓN DEL VECTOR TASKS DONDE ESTÉ ESA 'TASK' Y SE DISMINUIRÁ EL CONTADOR
            contador--;
        }else{
            error(ERR_TASK_NAME);
        }
        
        }while(contador > 0);                                                   //EL BUCLE DO-WHILE SE HARÁ HASTA QUE SE HALLAN ELIMINADO TODAS LAS TASKS CON EL NOMBRE INTRODUCIDO
        
    }else{
        error(ERR_LIST_NAME);
    }
}

void checkDeleteTask2(Project &toDoList,bool &checkToggleList,string listname4,int &h){     //FUNCIÓN PARA COMPROBAR QUE LA LISTA INTRODUCIDA EXISTE EN EL VECTOR LISTS
    
    for(unsigned j=0;j<toDoList.lists.size();j++){
        if(toDoList.lists[j].name == listname4){
            checkToggleList = true;
            h=j;
        }
    }
}

void checkTaskName3(Project &toDoList,bool &correctTaskName3,string taskname3,int h,vector<int> &contadorTask){     //FUNCIÓN PARA COMPROBAR QUE LA 'TASK' INTRODUCIDA EXISTE EN EL VECTOR TASKS Y A SU VEZ VA INTRODUCIENDO POSICIONES
                                                                                                                    //EN EL VECTOR AUXILIAR
    for(unsigned d=0;d<toDoList.lists[h].tasks.size();d++){
        if(toDoList.lists[h].tasks[d].name == taskname3){
            correctTaskName3=true;
            contadorTask.push_back(d);
        }
    }
}

void toggleTask(Project &toDoList){                                                     //FUNCIÓN QUE NOS PERMITE CAMBIAR EL ESTADO DE NUESTRAS TAREAS
    bool correctDeleteTask2=false,checkToggleList=false,correctTaskName3=false;
    string listname4,taskname3;     
    int h;
    vector<int> contadorTask;
    do{
        cout<<LIST_NAME;                                                        //BUCLE DO-WHILE PARA QUE EL USUARIO INTRODUZCA UN NOMBRE DE PROYECTO CORRECTO
        getline(cin,listname4,'\n');
    
        if(listname4 == ""){
            error(ERR_EMPTY);
        
        }else{
            correctDeleteTask2 = true;
        }
    }while(correctDeleteTask2 == false);

    checkDeleteTask2(toDoList,checkToggleList,listname4,h);                     //SI LA LISTA ES CORRECTA, LLAMAMOS A LA FUNCIÓN "checkDeleteTask2" PARA COMPROBAR SI LA LISTA INTRODUCIDA EXISTE EN EL VECTOR LISTS

    if(checkToggleList == true){
        cout<<TASK_NAME;
        getline(cin,taskname3,'\n');
        
        checkTaskName3(toDoList,correctTaskName3,taskname3,h,contadorTask);     //SI LA LISTA EXISTE, LLAMAMOS A LA FUNCIÓN "checkTaskName3" PARA COMPROBAR QUE LA 'TASK' INTRODUCIDA EXISTE EN EL VECTOR LISTS CORRESPONDIENTE
        
        if(correctTaskName3 == true){                                           //SI LA 'TASK' EXISTE SE CAMBIARÁ DE ESTADO EN ".isDone"
            for(unsigned j=0;j<contadorTask.size();j++){
                if(toDoList.lists[h].tasks[contadorTask[j]].isDone == true){                  //SI LA LISTA TIENE MÁS DE UNA 'TASK' CON EL NOMBRE INTRODUCIDO, SE CAMBIARÁ EL ESTADO A TODAS LAS TASKS CON ESE NOMBRE
                    toDoList.lists[h].tasks[contadorTask[j]].isDone = false;                  //ESTO SE HARÁ CON LA AYUDA DEL VECTOR AUXILIAR "vector<int> contadorTask", YA QUE POR CADA 'TASK' QUE HAYA CON ESE NOMBRE
                                                                                              //SE HARÁ UN ".push_back" CON LA POSICIÓN DE LA 'TASK', Y ASÍ PODEMOS HACER UN BUCLE FOR QUE SE REPITA MIENTRAS QUE LA "j" SEA MENOR
                }else{                                                                        //QUE EL TAMAÑO DEL VECTOR AUXULIAR, CONSIGUIENDO CMABIAR TODOS LOS ESTADOS
                    toDoList.lists[h].tasks[contadorTask[j]].isDone = true;
                }
            }
        }else{
            error(ERR_TASK_NAME);
        }
    }else{
        error(ERR_LIST_NAME);
    }    
}

void checkHighestPriority(const Project &toDoList,string &highestTask,int &highestDay,int &highestMonth,int &highestYear,int &contadorReport){              //ESTA FUNCÍON NOS PERMITE SABER CUAL ES LA 'TASK' MÁS ANTIGUA

    for(unsigned x=0;x<toDoList.lists.size();x++){                                                            //PARA ELLO VAMOS A IR ASIGNANDO A LAS VARIABLES INT, CADA VEZ QUE RECORRA UNA POSICION DE LOS VECTORES, SI SUS VALORES SON MAS ANTIGUOS
        for(unsigned y=0;y<toDoList.lists[x].tasks.size();y++){                                               //QUE LOS YA GUARDADOS, LOS REEMPLAZARÁN, ASI HASTA QUE RECORRA TODAS LAS TASKS DE TODAS LAS LISTS
    
            if(toDoList.lists[x].tasks[y].isDone == false){                                                   //SI OCURRE QUE HAY DOS TASKS IGUALES Y LAS DOS SON LAS MÁS ANGIUAS, SE MOSTRARÁ LA QUE PRIMERO HAYA SIDO INTRODUCIDA
                if(highestYear == 0){                                                                         //PARA ELLO USAMOS "contadorReport", YA QUE CUANDO COJA LA PRIMERA SE INCREMENTE Y NO PUEDA METER MÁS VALORES
                    highestYear=toDoList.lists[x].tasks[y].deadline.year;
                    highestMonth=toDoList.lists[x].tasks[y].deadline.month;
                    highestDay=toDoList.lists[x].tasks[y].deadline.day;
                    highestTask=toDoList.lists[x].tasks[y].name;
                
                }else{
                    if(toDoList.lists[x].tasks[y].deadline.year < highestYear){
                    highestYear=toDoList.lists[x].tasks[y].deadline.year;
                    highestMonth=toDoList.lists[x].tasks[y].deadline.month;
                    highestDay=toDoList.lists[x].tasks[y].deadline.day;
                    highestTask=toDoList.lists[x].tasks[y].name;
                    
                    }else{
                        if(toDoList.lists[x].tasks[y].deadline.year == highestYear){
                            if(toDoList.lists[x].tasks[y].deadline.month < highestMonth){
                                highestYear=toDoList.lists[x].tasks[y].deadline.year;
                                highestMonth=toDoList.lists[x].tasks[y].deadline.month;
                                highestDay=toDoList.lists[x].tasks[y].deadline.day;
                                highestTask=toDoList.lists[x].tasks[y].name;
                            
                            }else{
                                if(toDoList.lists[x].tasks[y].deadline.month == highestMonth){
                                    if(toDoList.lists[x].tasks[y].deadline.day < highestDay){
                                        highestYear=toDoList.lists[x].tasks[y].deadline.year;
                                        highestMonth=toDoList.lists[x].tasks[y].deadline.month;
                                        highestDay=toDoList.lists[x].tasks[y].deadline.day;
                                        highestTask=toDoList.lists[x].tasks[y].name;
                                     
                                    }else{
                                        if(toDoList.lists[x].tasks[y].deadline.day == highestDay){
                                            if(contadorReport < 0){
                                                highestYear=toDoList.lists[x].tasks[y].deadline.year;
                                                highestMonth=toDoList.lists[x].tasks[y].deadline.month;
                                                highestDay=toDoList.lists[x].tasks[y].deadline.day;
                                                highestTask=toDoList.lists[x].tasks[y].name;
                                                contadorReport++; 
                                            }
                                        }
                                    }
                                }                                                                       
                            }
                        }
                    }
                }
            }
        }
    }
}

void report(const Project &toDoList){                                                                               //FUNCIÓN QUE NOS MUESTRAS 'TODO' LO INTRODUCIDO HASTA AHORA
    int totalLeft=0,totalDone=0,minLeft=0,minDone=0,highestDay=0,highestMonth=0,highestYear=0,contadorReport=0;
    string highestTask;
    
    cout<<"Name: "<<toDoList.name<<endl;                        //MUESTRA EL NOMBRE DEL PROYECTO
    
    if(toDoList.description != ""){
        cout<<"Description: "<<toDoList.description<<endl;          //MUESTRA LA DESCRIPCIÓN DEL PROYECTO SI LA TUVIESE
    }
    
    for(unsigned i=0;i<toDoList.lists.size();i++){                  //RECORRE TODOS LOS VECTORES CREADOS MOSTRANDO TODAS LAS LISTAS CON SUS RESPECTIVAS TAREAS, CON SU TIEMPO Y SU FECHA, Y MARCANDO CON UNA X SI ESTÁN COMPLETADAS
        cout<<toDoList.lists[i].name<<endl;
        for(unsigned z=0;z<toDoList.lists[i].tasks.size();z++){
            if(toDoList.lists[i].tasks[z].isDone == false){
                cout<<"[ ] ("<<toDoList.lists[i].tasks[z].time<<") "<<toDoList.lists[i].tasks[z].deadline.year<<"-"<<toDoList.lists[i].tasks[z].deadline.month<<"-"<<toDoList.lists[i].tasks[z].deadline.day<<" : "<<toDoList.lists[i].tasks[z].name<<endl;
                totalLeft++;
                minLeft=minLeft + toDoList.lists[i].tasks[z].time;
            }
        }
    
        for(unsigned j=0;j<toDoList.lists[i].tasks.size();j++){
            if(toDoList.lists[i].tasks[j].isDone == true){
                cout<<"[X] ("<<toDoList.lists[i].tasks[j].time<<") "<<toDoList.lists[i].tasks[j].deadline.year<<"-"<<toDoList.lists[i].tasks[j].deadline.month<<"-"<<toDoList.lists[i].tasks[j].deadline.day<<" : "<<toDoList.lists[i].tasks[j].name<<endl;
                totalDone++;
                minDone=minDone + toDoList.lists[i].tasks[j].time;
            } 
        }
        
        cout<<endl;
    }
    
    cout<<endl;
    cout<<"Total left: "<<totalLeft<<" ("<<minLeft<<" minutes)"<<endl;          //MUESTRA EL TOTAL DE TAREAS QUE FALTAN POR HACER Y LA CANTIDAD TOTAL DE MINUTOS RESTANTES
    cout<<"Total done: "<<totalDone<<" ("<<minDone<<" minutes)"<<endl;          //MUESTRA EL TOTAL DE TAREAS HECHAS Y LA CANTIDAD TOTAL DE MINUTOS EMPLEADOS
    
    if(totalLeft != 0){
        if(contadorReport != 0){
                do{
                    contadorReport--;
                }while(contadorReport > 0);
            }
            
        checkHighestPriority(toDoList,highestTask,highestDay,highestMonth,highestYear,contadorReport);                  //SE LLAMA A LA FUNCIÓN "checkHighestPriority" QUE NOS PERMITE CONOCER CUAL ES LA 'TASK' SIN COMPLETAR 
        cout<<"Highest priority: "<<highestTask<<" ("<<highestYear<<"-"<<highestMonth<<"-"<<highestDay<<")"<<endl;      //CON LA FECHA MÁS ANTIGUA
    }
}

int main(){
  Project toDoList;
  toDoList.id=1;
  char option;
  
  do{
    showMainMenu();
    cin >> option;
    cin.get();
    
    switch(option){
      case '1': editProject(toDoList);
                break;
      case '2': addList(toDoList);
                break;
      case '3': deleteList(toDoList);
                break;
      case '4': addTask(toDoList);
                break;
      case '5': deleteTask(toDoList);
                break;
      case '6': toggleTask(toDoList);
                break;
      case '7': report(toDoList);
                break;
      case 'q': break;
      default: error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;    
}
