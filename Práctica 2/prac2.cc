//DNI: 48771960T NOEL MARTÍNEZ POMARES
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <cctype>
#include <cstring>
#include <sstream>
using namespace std;

const string PROYECT_NAME = "Enter project name: ";                           
const string PROYECT_DESCRIPTION = "Enter project description: ";               
const string LIST_NAME = "Enter list name: ";
const string TASK_NAME = "Enter task name: ";
const string DEADLINE = "Enter deadline: ";
const string TIME = "Enter expected time: ";
const string ID_PROYECT = "Enter project id: ";
const string ALL_PROJECTS = "Save all projects [Y/N]?: ";
const string FILENAME = "Enter filename: ";
const string ELECCION = "Confirm [Y/N]?: ";
const int ANYO1 = 2000;
const int ANYO2 = 2100;
const int MESI = 1;
const int MESF = 12;
const int NUM = 180;
const int BIS4 = 4;
const int BIS100 = 100;
const int BIS400 = 400;
const int KMAXNAME = 20;
const int KMAXDESC = 40;

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

struct ToDo{
    int nextId;
    string name;
    vector<Project> projects;
};

struct BinTask{
    char name[KMAXNAME];
    Date deadline;
    bool isDone;
    int time;
};

struct BinList{
    char name[KMAXNAME];
    unsigned numTasks;
};

struct BinProject{
    char name[KMAXNAME];
    char description[KMAXDESC];
    unsigned numLists;
};

struct BinToDo{
    char name[KMAXNAME];
    unsigned numProjects;
};

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME,
  ERR_FILE,
  ERR_ARGS
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
      break;
    case ERR_ID:
      cout << "ERROR: wrong project id" << endl;
      break;
    case ERR_PROJECT_NAME:
      cout << "ERROR: wrong project name" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
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
       << "b- Back to main menu" << endl
       << "Option: ";
}

void showProyectMenu(){
  cout << "1- Project menu" << endl
       << "2- Add project" << endl
       << "3- Delete project" << endl 
       << "4- Import projects" << endl
       << "5- Export projects" << endl
       << "6- Load data" << endl
       << "7- Save data" << endl
       << "8- Summary" << endl
       << "q- Quit" << endl
       << "Option: ";    
}


//Funcion que nos permite introducir el nombre y la descripción del proyecto
void editProject(ToDo &toDoProyect, int numero_Id){        
     bool correct_Proyect_Name=false;
     
     //Se hace bucle para introducir el nombre
     do{                                                                        
        cout<<PROYECT_NAME;
        getline(cin,toDoProyect.projects[numero_Id].name,'\n');
        
        if(toDoProyect.projects[numero_Id].name == ""){
            error(ERR_EMPTY);
            
        }else{
            correct_Proyect_Name = true;
        }
     }while(correct_Proyect_Name == false);
    
    //La descripción puede quedarse vacía
    cout<<PROYECT_DESCRIPTION;                                                  
    getline(cin,toDoProyect.projects[numero_Id].description,'\n');
}

//Función que comprueba que la lista introducida no se había introducido anteriormente
bool checkList(ToDo &toDoProyect,string listName,int num_id){               
    bool check_list=false;    

    for(unsigned i=0;i<toDoProyect.projects[num_id].lists.size();i++){
        if(toDoProyect.projects[num_id].lists[i].name == listName){
            check_list = true;
        }
    }
    
    return(check_list);
    
}

//Función que verifica que la lista introducida no esté vacía
bool correct_Name(ToDo &toDoProyect,string List_Name){
    bool is_correct=false;

    if(List_Name == ""){
        error(ERR_EMPTY);
            
        }else{
            is_correct = true;
        }
    
    return (is_correct);
}

//Función para añadir listas al proyecto
void addList(ToDo &toDoProyect, int numero_Id_AddList){                     
    bool correctList=false,listDone=false;
    List newList;
    string listName;
    
    do{                                                                         

        cout<<LIST_NAME;
        getline(cin,listName,'\n');
        
        correctList=correct_Name(toDoProyect,listName);
        
    }while(correctList == false);
     
    //Si no hay listas previas, se asigna el nombre de la lista al vector "newList" creado, 
    //y después con ".push_back" se introduce al final del vector lists
    if(toDoProyect.projects[numero_Id_AddList].lists.size() == 0){                                             
        newList.name = listName;                                                
        toDoProyect.projects[numero_Id_AddList].lists.push_back(newList);
         
    }else{
        
        //Si no está vacio, se introduce el nombre de la lista al final del vector lists,
        //de lo contrario daría error
        listDone=checkList(toDoProyect,listName,numero_Id_AddList);                                  
                                                                                
        if(listDone == true){                  
            error(ERR_LIST_NAME);
        
        }else{
            newList.name = listName;
            toDoProyect.projects[numero_Id_AddList].lists.push_back(newList);                                               
        }
    }
}

//Función que comprueba que la lista introducida existe en el vector lists
bool checkDeleteList(ToDo &toDoProyect,string delete_Name, int id_Delete_list){     
    bool Delete_List=false;
    
    for(unsigned i=0;i<toDoProyect.projects[id_Delete_list].lists.size();i++){
        if(toDoProyect.projects[id_Delete_list].lists[i].name == delete_Name){
            Delete_List = true;
        }
    }
    
    return(Delete_List);
    
}

//Función que devuelve la posición donde se encuentra la lista introducida
int check_Pos_List(ToDo &toDoProyect,string delete_Name, int id_pos_list){     
    int posicion=0;
    
    for(unsigned i=0;i<toDoProyect.projects[id_pos_list].lists.size();i++){
        if(toDoProyect.projects[id_pos_list].lists[i].name == delete_Name){
            posicion = i;
        }
    }
    
    return(posicion);
    
}

//Funcíon para eliminar listas
void deleteList(ToDo &toDoProyect, int numero_Id_DeleteList){                         
    int pos=0;
    bool deleteLists=false,correctDeleteList=false;
    string deleteName;
    
    do{
        cout<<LIST_NAME;                                                        
        getline(cin,deleteName,'\n');

        deleteLists=correct_Name(toDoProyect,deleteName);
        
    }while(deleteLists == false);

    //Se comprueba que la lista introducida exista y su obtiene su posición,
    //en caso contrario emitirá un error
    correctDeleteList=checkDeleteList(toDoProyect,deleteName,numero_Id_DeleteList);                 
    pos=check_Pos_List(toDoProyect,deleteName,numero_Id_DeleteList);
    
    if(correctDeleteList == true){
        
        //Si la lista existe se elimina con ".erase(.begin()+posicion)" usando su posición guardada
        toDoProyect.projects[numero_Id_DeleteList].lists.erase(toDoProyect.projects[numero_Id_DeleteList].lists.begin()+pos);                  
                                                                                
    }else{
        error(ERR_LIST_NAME);                                                      
    }
}

//Función para comprobar que la fecha es correcta
bool checkCorrectDate(Date newTask){                                            
    int mesDias[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};
    
    //Comprueba si el año es bisiesto, si es así se suma un día a febrero
    if((newTask.year%BIS4 == 0 && newTask.year%BIS100 != 0) || newTask.year%BIS400 == 0){    
        mesDias[MESI]++;                                                               
    } 
       
    //Se comprueba que el año esté entre [2000,2100]   
    if(newTask.year < ANYO1 || newTask.year > ANYO2){                              
        return false;
    } 
    
    //Se comprueba que el mes esté entre [1,12]
    if(newTask.month < MESI || newTask.month > MESF){                                    
        return false;
    }
    
    newTask.month = newTask.month-MESI;
    
    //Se comprueba que el día es mayor que cero y no supera el máximo de días de su mes
    if(newTask.day <= 0 || newTask.day > mesDias[newTask.month]){                   
        return false;
    }

        return true;                                                                
}

//Funcíon para añadir tareas a las listas
void addTask(ToDo &toDoProyect, int numero_Id_AddTask){                      
    int numCadena,posList;
    bool correctList_Task=false,correctAddTask=false,correctDate=false;
    string listName2,taskName;
    Task newTask;
    char primeraBarra,segundaBarra;

    do{
        cout<<LIST_NAME;                                                      
        getline(cin,listName2,'\n');
    
        correctList_Task=correct_Name(toDoProyect,listName2);
        
    }while(correctList_Task == false);
     
    //Se comprueba que la lista introducida exista y su obtiene su posición,
    //en caso contrario emitirá un error
    correctAddTask=checkDeleteList(toDoProyect,listName2,numero_Id_AddTask);                    
    posList=check_Pos_List(toDoProyect,listName2,numero_Id_AddTask);
    
    if(correctAddTask == true){
        cout<<TASK_NAME;
        getline(cin,taskName,'\n');                                             
        cout<<DEADLINE;
        
        //Se usa un vector auxiliar para que el usuario introduzca la fecha
        cin>>newTask.deadline.day >> primeraBarra >> newTask.deadline.month >> segundaBarra >> newTask.deadline.year;  

        //Se comprueba que la fecha sea correcta
        correctDate = checkCorrectDate(newTask.deadline);                       
        
        //Si es correcta se pide el tiempo, que debe estar entre [1,180],
        //de lo contrario se emetirá un error
        if(correctDate == true){                                                
            cout<<TIME;
            cin>>numCadena;
            cin.get();
            
            //Si es correcto se introduce el nombre y el tiempo al vector task y el campo .isDone se inicializa falso
            if(numCadena >= MESI && numCadena <= NUM){                             
                newTask.name = taskName;                                        
                newTask.time = numCadena;
                newTask.isDone = false;
                toDoProyect.projects[numero_Id_AddTask].lists[posList].tasks.push_back(newTask);            

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

//Funcíon que comprueba que la task introducida existe
void checkTaskName2(ToDo &toDoProyect,bool &correctTask_Name,string taskName2,int &posTask,int posList_Task,int &contador,int id_task_name){    
                                                                                                                                
    for(unsigned z=0;z<toDoProyect.projects[id_task_name].lists[posList_Task].tasks.size();z++){
            if(toDoProyect.projects[id_task_name].lists[posList_Task].tasks[z].name == taskName2){
                    correctTask_Name=true;
                    posTask=z;
                    contador++;
            
        }
    }
}

//Función para eliminar tareas de las listas
void deleteTask(ToDo &toDoProyect, int numero_Id_DeleteTask){                         
    bool correctDelete_Task=false,correctTask_Name=false,correctListTask=false;
    string listName3,taskName2; 
    int posTask,posList_Task,contador=0;
    
    do{
        cout<<LIST_NAME;                                                        
        getline(cin,listName3,'\n');
    
        correctDelete_Task=correct_Name(toDoProyect,listName3);
        
    }while(correctDelete_Task == false);

    //Se comprueba que la lista introducida exista y su obtiene su posición,
    //en caso contrario emitirá un error
    correctListTask=checkDeleteList(toDoProyect,listName3,numero_Id_DeleteTask);                    
    posList_Task=check_Pos_List(toDoProyect,listName3,numero_Id_DeleteTask);

    if(correctListTask == true){
        cout<<TASK_NAME;
        getline(cin,taskName2,'\n');
        
        //Se declara un contador para contar la cantidad de task con el
        //mismo nombre introducido hay en esa lista
        do{
            if(contador != 0){                                                  
                do{
                    contador--;
                }while(contador > 0);
            }
            
        //Se comprueba que la task, exista en la lista
        checkTaskName2(toDoProyect,correctTask_Name,taskName2,posTask,posList_Task,contador,numero_Id_DeleteTask);    
        
        if(correctTask_Name == true){
            
            //Si existe se eliminará esa task y se disminuirá el contador
            toDoProyect.projects[numero_Id_DeleteTask].lists[posList_Task].tasks.erase(toDoProyect.projects[numero_Id_DeleteTask].lists[posList_Task].tasks.begin()+posTask);      
            contador--;
        }else{
            error(ERR_TASK_NAME);
        }
        
        }while(contador > 0);                                                   
        
    }else{
        error(ERR_LIST_NAME);
    }
}

//Funcíon que comprueba que la task introducida existe
void checkTaskName3(ToDo &toDoProyect,bool &correctTaskName3,string taskname3,int h,vector<int> &contadorTask,int id_toggle_name){     
    
    for(unsigned d=0;d<toDoProyect.projects[id_toggle_name].lists[h].tasks.size();d++){
        if(toDoProyect.projects[id_toggle_name].lists[h].tasks[d].name == taskname3){
            correctTaskName3=true;
            contadorTask.push_back(d);
        }
    }
}

//Función para cambiar el estado de las tareas
void toggleTask(ToDo &toDoProyect, int numero_Id_Toggle){                                                     
    bool correctDeleteTask2=false,checkToggleList=false,correctTaskName3=false;
    string listname4,taskname3;     
    int h;
    vector<int> contadorTask;
    do{
        cout<<LIST_NAME;                                                        
        getline(cin,listname4,'\n');
    
        correctDeleteTask2=correct_Name(toDoProyect,listname4);
        
    }while(correctDeleteTask2 == false);

    //Se comprueba que la lista introducida exista y su obtiene su posición,
    //en caso contrario emitirá un error
    checkToggleList=checkDeleteList(toDoProyect,listname4,numero_Id_Toggle);                    
    h=check_Pos_List(toDoProyect,listname4,numero_Id_Toggle);

    if(checkToggleList == true){
        cout<<TASK_NAME;
        getline(cin,taskname3,'\n');
        
        //Se comprueba que la task exista en la lista introducida
        checkTaskName3(toDoProyect,correctTaskName3,taskname3,h,contadorTask,numero_Id_Toggle);     
        
        if(correctTaskName3 == true){            
            
            //Si existe se cambia el estado de la tarea
            for(unsigned j=0;j<contadorTask.size();j++){
                
                //Si la lista tiene mas de una task con ese nombre, se cambia el estado a todas con la ayuda de un vector auxiliar
                //y por cada task con ese nombre se hará un ".push_back" con su posición, y con el bulce for cambiarlas todas
                if(toDoProyect.projects[numero_Id_Toggle].lists[h].tasks[contadorTask[j]].isDone == true){                 
                    toDoProyect.projects[numero_Id_Toggle].lists[h].tasks[contadorTask[j]].isDone = false;                  
                    
                }else{                                                                        
                    toDoProyect.projects[numero_Id_Toggle].lists[h].tasks[contadorTask[j]].isDone = true;
                }
            }
        }else{
            error(ERR_TASK_NAME);
        }
    }else{
        error(ERR_LIST_NAME);
    }    
}

//Función para saber cual es la task mas antigua
void checkHighestPriority(const ToDo &toDoProyect,string &highestTask,int &highestDay,int &highestMonth,int &highestYear,int &contadorReport, int id_Priority){             

    for(unsigned x=0;x<toDoProyect.projects[id_Priority].lists.size();x++){                                                            
        for(unsigned y=0;y<toDoProyect.projects[id_Priority].lists[x].tasks.size();y++){                                               
    
            if(toDoProyect.projects[id_Priority].lists[x].tasks[y].isDone == false){                                                   
                if(highestYear == 0){                                                                        
                    highestYear=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year;
                    highestMonth=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month;
                    highestDay=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day;
                    highestTask=toDoProyect.projects[id_Priority].lists[x].tasks[y].name;
                
                }else{
                    if(toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year < highestYear){
                    highestYear=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year;
                    highestMonth=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month;
                    highestDay=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day;
                    highestTask=toDoProyect.projects[id_Priority].lists[x].tasks[y].name;
                    
                    }else{
                        if(toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year == highestYear){
                            if(toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month < highestMonth){
                                highestYear=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year;
                                highestMonth=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month;
                                highestDay=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day;
                                highestTask=toDoProyect.projects[id_Priority].lists[x].tasks[y].name;
                            
                            }else{
                                if(toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month == highestMonth){
                                    if(toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day < highestDay){
                                        highestYear=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year;
                                        highestMonth=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month;
                                        highestDay=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day;
                                        highestTask=toDoProyect.projects[id_Priority].lists[x].tasks[y].name;
                                     
                                    }else{
                                        
                                        //Si hay dos tasks igual de antiguas, se mostrará solo la que primero haya sido introducida
                                        if(toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day == highestDay){
                                            if(contadorReport < 0){
                                                highestYear=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.year;
                                                highestMonth=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.month;
                                                highestDay=toDoProyect.projects[id_Priority].lists[x].tasks[y].deadline.day;
                                                highestTask=toDoProyect.projects[id_Priority].lists[x].tasks[y].name;
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

//Función para mostrar todo lo introducido
void report(const ToDo &toDoProyect, int numero_Id_Report){                                                                              
    int totalLeft=0,totalDone=0,minLeft=0,minDone=0,highestDay=0,highestMonth=0,highestYear=0,contadorReport=0;
    string highestTask;
    
    cout<<"Name: "<<toDoProyect.projects[numero_Id_Report].name<<endl;                        
    
    if(toDoProyect.projects[numero_Id_Report].description != ""){
        cout<<"Description: "<<toDoProyect.projects[numero_Id_Report].description<<endl;          
    }
    
    //Recorre los vectores mostrando todo su contenido y marcando con una X si las tareas están completas
    for(unsigned i=0;i<toDoProyect.projects[numero_Id_Report].lists.size();i++){                 
        cout<<toDoProyect.projects[numero_Id_Report].lists[i].name<<endl;
        for(unsigned z=0;z<toDoProyect.projects[numero_Id_Report].lists[i].tasks.size();z++){
            if(toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].isDone == false){
                cout<<"[ ] ("<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].time<<") "<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].deadline.year<<"-"<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].deadline.month<<"-"<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].deadline.day<<" : "<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].name<<endl;
                totalLeft++;
                minLeft=minLeft + toDoProyect.projects[numero_Id_Report].lists[i].tasks[z].time;
            }
        }
    
        for(unsigned j=0;j<toDoProyect.projects[numero_Id_Report].lists[i].tasks.size();j++){
            if(toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].isDone == true){
                cout<<"[X] ("<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].time<<") "<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].deadline.year<<"-"<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].deadline.month<<"-"<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].deadline.day<<" : "<<toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].name<<endl;
                totalDone++;
                minDone=minDone + toDoProyect.projects[numero_Id_Report].lists[i].tasks[j].time;
            } 
        }
        
        cout<<endl;
    }
    
    cout<<endl;
    
    //Total de tareas que faltan por hacer y la cantidad de minutos restantes
    cout<<"Total left: "<<totalLeft<<" ("<<minLeft<<" minutes)"<<endl;          
    
    //Total de tareas hechas y cantidad de minutos empleados
    cout<<"Total done: "<<totalDone<<" ("<<minDone<<" minutes)"<<endl;          
    
    if(totalLeft != 0){
        if(contadorReport != 0){
                do{
                    contadorReport--;
                }while(contadorReport > 0);
            }
            
        //Muestra la task sin completar con la fecha mas antigua    
        checkHighestPriority(toDoProyect,highestTask,highestDay,highestMonth,highestYear,contadorReport,numero_Id_Report);                  
        cout<<"Highest priority: "<<highestTask<<" ("<<highestYear<<"-"<<highestMonth<<"-"<<highestDay<<")"<<endl;      
    }
}

//Función que comprueba si el id del proyecto introducido existe
bool checkExist_ProjectId(ToDo &toDoProyect,int identificador){
    bool id_exist=false;
    
    for(unsigned i=0;i<toDoProyect.projects.size();i++){
        if(toDoProyect.projects[i].id == identificador){
            id_exist = true;
        }
    }
    
    return id_exist;    
}

//Función que devuelve la posición del proyecto introducido 
int checkPos_ProjectId(ToDo &toDoProyect,int identificador_pos){
    int posicion_id=0;
    
    for(unsigned i=0;i<toDoProyect.projects.size();i++){
        if(toDoProyect.projects[i].id == identificador_pos){
            posicion_id=i;
        }
    }
    
    return posicion_id;    
}

//Función para editar los proyectos ya introducidos. Se pide al usuario el id y si existe, se muestra
//El menu de editar proyectos de la práctica 1
void projectMenu(ToDo &toDoProyect){
    int project_id,posicion_toDoProyect;
    bool correctProyect_Id=false;
    char option_proyect;
    
    
    cout <<ID_PROYECT;
    cin>>project_id;
    cin.get();
    
    correctProyect_Id=checkExist_ProjectId(toDoProyect,project_id);
    posicion_toDoProyect=checkPos_ProjectId(toDoProyect,project_id);
    
    if(correctProyect_Id == true){
        do{
            showMainMenu();
            cin >> option_proyect;
            cin.get();
    
            switch(option_proyect){
                case '1': editProject(toDoProyect,posicion_toDoProyect);
                        break;
                case '2': addList(toDoProyect,posicion_toDoProyect);
                        break;
                case '3': deleteList(toDoProyect,posicion_toDoProyect);
                        break;
                case '4': addTask(toDoProyect,posicion_toDoProyect);
                        break;
                case '5': deleteTask(toDoProyect,posicion_toDoProyect);
                        break;
                case '6': toggleTask(toDoProyect,posicion_toDoProyect);
                        break;
                case '7': report(toDoProyect,posicion_toDoProyect);
                        break;
                case 'b': break;
                default: error(ERR_OPTION);
            }
        }while(option_proyect!='b');
        
    }   else{
        error(ERR_ID);
    }

}

//Función que verifica que el proyecto no se haya introducido anteriormente
bool checkExist_Project(ToDo &toDoProyect,string name_Project){
    bool project_exist=false;
    
    for(unsigned i=0;i<toDoProyect.projects.size();i++){
        if(toDoProyect.projects[i].name == name_Project){
            project_exist = true;
        }
    }
    
    return(project_exist);    
}

//Función para añadir proyectos nuevos
void addProject(ToDo &toDoProyect){
    string project_name,projectDescription_Name;
    bool notCorrect_Name=false,existProject_Name=false;
    Project newProject;
    
    do{
        cout << PROYECT_NAME;
        getline(cin,project_name,'\n');
    
        if(project_name == ""){
            error(ERR_EMPTY);
            
        }   else{
                notCorrect_Name=true;
        }
    }while(notCorrect_Name==false);
    
    //Se comprueba que no exista ya un projecto con ese nombre
    existProject_Name=checkExist_Project(toDoProyect,project_name);
    
    if(existProject_Name==true){
        error(ERR_PROJECT_NAME);
        
    }   else{
            //Si no existe, se introduce un nuevo proyecto con los datos introducidos
            //Y se le asigna el id de toDoProyect, aumentando este después +1
            newProject.name=project_name;
            
            cout<<PROYECT_DESCRIPTION;
            getline(cin,projectDescription_Name,'\n');
            
            newProject.description=projectDescription_Name;
            newProject.id=toDoProyect.nextId;
            toDoProyect.nextId++;
            
            toDoProyect.projects.push_back(newProject);     
    }
}

//Función para eliminar proyectos
void deleteProject(ToDo &toDoProyect){
    int correctProject_Id,posicion_toDoId=0;
    bool existProject_Id=false;
    
    cout<<ID_PROYECT;
    cin>>correctProject_Id;
    cin.get();
    
    existProject_Id=checkExist_ProjectId(toDoProyect,correctProject_Id);
    posicion_toDoId=checkPos_ProjectId(toDoProyect,correctProject_Id);
    
    if(existProject_Id == false){
        error(ERR_ID);
        
    }   else{
            //Si existe el id introducido, se borrará el proyecto con ese id, pero
            //Su id no lo podrá tener ninguno más, se elimina también sin volver atrás
            toDoProyect.projects.erase(toDoProyect.projects.begin()+posicion_toDoId);
    }
}

// Extraemos la subcadena antes del |
string extraer_Nombre_Task(string cadena){
  string indice;

  // Recorremos hasta encontrar los primeros "|"  
  for(unsigned i=0;i<cadena.find("|");i++){
    indice+=cadena[i];
  }
  
  return (indice);
}

string extraer_contenido(string contenido_String){
  string extraccion;

  //Se copia a partir de "|"
  for(unsigned i=contenido_String.find("|")+1;i<contenido_String.length();i++){
    extraccion+=contenido_String[i];
  }

  return extraccion;
}

// Extraemos la fecha antes del /
string extraer_Fecha_Task(string cadena_fecha){
  string string_fecha;

  // Recorremos hasta encontrar los primeros "/"  
  for(unsigned i=0;i<cadena_fecha.find("/");i++){
    string_fecha+=cadena_fecha[i];
  }
  
  return (string_fecha);
}

string extraer_contenido_fecha(string contenido_fecha){
  string extraccion_numero;

  //Se copia a partir de "/"
  for(unsigned i=contenido_fecha.find("/")+1;i<contenido_fecha.length();i++){
    extraccion_numero+=contenido_fecha[i];
  }

  return extraccion_numero;
}

//Función que comprueba que el tiempo del fichero sea correcto
bool comprobar_tiempo(int tiempo_introducido){
    bool tiempo_introducido_correcto=false;
    
    if((tiempo_introducido >= MESI) && (tiempo_introducido <= NUM)){
        tiempo_introducido_correcto=true;
    }
    
    return (tiempo_introducido_correcto);
}

//Función que nos permite introducir en nuestro programa datos leidos de un fichero de texto
void importProjects(ToDo &toDoProyect,string nombreFichero){
    string import_Filename;
    ifstream project_import;
    Project project_New;
    List aux_list;
    Task aux_task;
    string linea,subcadena_name,subcadena_description,subcadena_list,subcadena_task,subcadena_task_fecha,subcadena_fecha,subcadena_task_bool,subcadena_bool,subcadena_time,cadena_mes,cadena_anyo,nume_dia,nume_mes,nume_anyo;
    int num_day,num_month,num_year,num_time,contador=0;
    bool project_not=false,fecha_correcta=false,tiempo_correcto=false;
    
    //Si se le pasa el fichero con un argumento se hará en esta parte con su nombre
    if(nombreFichero != ""){
        project_import.open(nombreFichero.c_str(),ios::in);
    
        if(project_import.is_open()){
            while(!project_import.eof()){
                getline(project_import,linea);
            

                if(linea.find("#")!=string::npos){
                    int pos = linea.find("#");
                    subcadena_name=linea.substr(pos+1);
                
                    project_not=checkExist_Project(toDoProyect,subcadena_name);
                
                    if(project_not == false){
                        project_New.name=subcadena_name;
                        project_New.id=toDoProyect.nextId;
                    
                    }   else{
                            error(ERR_PROJECT_NAME);
                    }
                }
            
                if(project_not==false){    
                    if(linea.find("@")!=string::npos){
                        if(contador == 1){
                            project_New.lists.push_back(aux_list);
                            aux_list.name.clear();
                            aux_list.tasks.clear();
                            contador=0;
                        }
                
                        int pos_list = linea.find("@");
                        subcadena_list=linea.substr(pos_list+1);
                        aux_list.name=subcadena_list;
                        contador++;
                    }
                
                    if(contador != 0){
                        if(linea.find("|")!=string::npos){
                            subcadena_task=extraer_Nombre_Task(linea);
                
                            subcadena_task_fecha=extraer_contenido(linea);
                            subcadena_fecha=extraer_Nombre_Task(subcadena_task_fecha);
                
                            nume_dia=extraer_Fecha_Task(subcadena_fecha);
                            istringstream(nume_dia) >> num_day;
                
                            cadena_mes=extraer_contenido_fecha(subcadena_fecha);
                            nume_mes=extraer_Fecha_Task(cadena_mes);
                            istringstream(nume_mes) >> num_month;
                
                            nume_anyo=extraer_contenido_fecha(cadena_mes);
                            istringstream(nume_anyo) >> num_year;
                
                            subcadena_task_bool=extraer_contenido(subcadena_task_fecha);
                            subcadena_bool=extraer_Nombre_Task(subcadena_task_bool);
                
                            subcadena_time=extraer_contenido(subcadena_task_bool);
                            istringstream(subcadena_time) >> num_time;
                        
                            aux_task.deadline.day=num_day;
                            aux_task.deadline.month=num_month;
                            aux_task.deadline.year=num_year;
                        
                            aux_task.time=num_time;
                            aux_task.name=subcadena_task;

                            if(subcadena_bool=="F"){
                                    aux_task.isDone=false;
                            }   else{
                                    aux_task.isDone=true;
                            }   
                        
                            fecha_correcta = checkCorrectDate(aux_task.deadline);
                        
                            if(fecha_correcta == true){
                                tiempo_correcto = comprobar_tiempo(num_time);
                            
                                if(tiempo_correcto == false){
                                    error(ERR_TIME);
                                }
                            
                            }   else{
                                    error(ERR_DATE);
                            }
                        
                            if((fecha_correcta == true) && (tiempo_correcto == true)){
                                aux_list.tasks.push_back(aux_task);
                            }  
                            
                        }
                    }

        
                    if(linea.find("*")!=string::npos){
                        int pos_description = linea.find("*");
                        subcadena_description=linea.substr(pos_description+1);
                        project_New.description=subcadena_description;
                    }
            
                    if(linea.find(">")!=string::npos){
                        toDoProyect.nextId=toDoProyect.nextId + 1;
                
                        project_New.lists.push_back(aux_list);
                        aux_list.name.clear();
                        aux_list.tasks.clear();
                
                        toDoProyect.projects.push_back(project_New);
                        project_New.name.clear();
                        project_New.description.clear();
                        project_New.lists.clear();
                        project_New.id=0;
                        contador=0;
                    }
                }
            }
        
            project_import.close();
        
        }   else{
                error(ERR_FILE);
            
        }
        
        //En caso de que no se haya introducido por argumento, se seguirá por aquí
    }   else{
            cout<<FILENAME;
            getline(cin,import_Filename,'\n');
    
            project_import.open(import_Filename.c_str(),ios::in);
            
            //Se abre el fichero
            if(project_import.is_open()){
                
                //Se leeran lineas consecutivas mientras que sigan habiendo en el fichero
                while(!project_import.eof()){
                    getline(project_import,linea);
            
                    //Si en la linea leida hay un #, se introducirán los datos de esa linea en un nuevo proyecto
                    if(linea.find("#")!=string::npos){
                        int pos = linea.find("#");
                        subcadena_name=linea.substr(pos+1);
                
                        project_not=checkExist_Project(toDoProyect,subcadena_name);
                
                        if(project_not == false){
                            project_New.name=subcadena_name;
                            project_New.id=toDoProyect.nextId;
                    
                        }   else{
                                error(ERR_PROJECT_NAME);
                        }
                    }
                    
                    //Si el nombre del proyecto leido ya existe, no se volvería a intentar introducir nada
                    //Hasta que lea el próximo proyecto
                    if(project_not==false){    
                        
                        //Si en la linea encuentra un @, se introducirán los datos en una lista del proyecto
                        if(linea.find("@")!=string::npos){
                            if(contador == 1){
                                project_New.lists.push_back(aux_list);
                                aux_list.name.clear();
                                aux_list.tasks.clear();
                                contador=0;
                            }
                
                            int pos_list = linea.find("@");
                            subcadena_list=linea.substr(pos_list+1);
                            aux_list.name=subcadena_list;
                            contador++;
                        }
                
                        if(contador != 0){
                            
                            //Si en la linea encuentra un |, se introducirán los datos en la lista anterior leida
                            if(linea.find("|")!=string::npos){
                                subcadena_task=extraer_Nombre_Task(linea);
                
                                subcadena_task_fecha=extraer_contenido(linea);
                                subcadena_fecha=extraer_Nombre_Task(subcadena_task_fecha);
                
                                nume_dia=extraer_Fecha_Task(subcadena_fecha);
                                istringstream(nume_dia) >> num_day;
                
                                cadena_mes=extraer_contenido_fecha(subcadena_fecha);
                                nume_mes=extraer_Fecha_Task(cadena_mes);
                                istringstream(nume_mes) >> num_month;
                
                                nume_anyo=extraer_contenido_fecha(cadena_mes);
                                istringstream(nume_anyo) >> num_year;
                
                                subcadena_task_bool=extraer_contenido(subcadena_task_fecha);
                                subcadena_bool=extraer_Nombre_Task(subcadena_task_bool);
                
                                subcadena_time=extraer_contenido(subcadena_task_bool);
                                istringstream(subcadena_time) >> num_time;
                        
                                aux_task.deadline.day=num_day;
                                aux_task.deadline.month=num_month;
                                aux_task.deadline.year=num_year;
                        
                                aux_task.time=num_time;
                                aux_task.name=subcadena_task;

                                if(subcadena_bool=="F"){
                                    aux_task.isDone=false;
                                }   else{
                                        aux_task.isDone=true;
                                }   
                        
                                fecha_correcta = checkCorrectDate(aux_task.deadline);
                        
                                if(fecha_correcta == true){
                                    tiempo_correcto = comprobar_tiempo(num_time);
                            
                                    if(tiempo_correcto == false){
                                        error(ERR_TIME);
                                    }
                            
                                }   else{
                                        error(ERR_DATE);
                                }
                        
                                if((fecha_correcta == true) && (tiempo_correcto == true)){
                                    aux_list.tasks.push_back(aux_task);
                                }  
                            
                            }
                        }

                        //Si en la linea encuentra un *, se introducirá la linea en la descripción del proyecto
                        if(linea.find("*")!=string::npos){
                            int pos_description = linea.find("*");
                            subcadena_description=linea.substr(pos_description+1);
                            project_New.description=subcadena_description;
                        }
                        
                        //Si en la linea encuentra un >, se borrarán los auxiliares y se seguirá leyendo nuevos proyectos
                        //Mientras queden en el fichero de texto
                        if(linea.find(">")!=string::npos){
                            toDoProyect.nextId=toDoProyect.nextId + 1;
                
                            project_New.lists.push_back(aux_list);
                            aux_list.name.clear();
                            aux_list.tasks.clear();
                
                            toDoProyect.projects.push_back(project_New);
                            project_New.name.clear();
                            project_New.description.clear();
                            project_New.lists.clear();
                            project_New.id=0;
                            contador=0;
                        }
                    }
                }
        
                project_import.close();
        
            }   else{
                    error(ERR_FILE);
            
            }
        }
}

//Función que permite introducir en un fichero de texto los datos de los proyectos que hayan
//Introducidos
void exportProjects(ToDo &toDoProyect){
    char election,final_election;
    int id_Export,posicionId_export;
    bool check_Export;
    string export_Filename;
    ofstream project_export;
    
    //Se le pregunta al usuario se quiere guardar todos los proyectos o solo uno en concreto
    do{
        cout<<ALL_PROJECTS;
        cin>>election;
        cin.get();
    
        final_election=tolower(election);
    }while((final_election != 'y') && (final_election != 'n'));
    
    //Si elige que todos, se entrará por aquí
    if(final_election == 'y'){
        cout<<FILENAME;
        getline(cin,export_Filename,'\n');
        
        project_export.open(export_Filename.c_str(),ios::out);
        
        if(project_export.is_open()){
            
            //Se introduce todo en orden y con el formato indicado
            for(unsigned i=0;i<toDoProyect.projects.size();i++){
                project_export << "<" << endl;
                project_export << "#" << toDoProyect.projects[i].name << endl;
                
                if(toDoProyect.projects[i].description != ""){
                    project_export << "*" << toDoProyect.projects[i].description << endl;
                }
                
                for(unsigned j=0;j<toDoProyect.projects[i].lists.size();j++){
                    project_export << "@" << toDoProyect.projects[i].lists[j].name << endl;
                    
                    for(unsigned x=0;x<toDoProyect.projects[i].lists[j].tasks.size();x++){
                        if(toDoProyect.projects[i].lists[j].tasks[x].isDone == false){
                            project_export << toDoProyect.projects[i].lists[j].tasks[x].name <<"|"<< toDoProyect.projects[i].lists[j].tasks[x].deadline.day<<"/"<<toDoProyect.projects[i].lists[j].tasks[x].deadline.month<<"/"<<toDoProyect.projects[i].lists[j].tasks[x].deadline.year<<"|F|"<<toDoProyect.projects[i].lists[j].tasks[x].time<<endl; 
                            
                        }   else{
                                project_export << toDoProyect.projects[i].lists[j].tasks[x].name <<"|"<< toDoProyect.projects[i].lists[j].tasks[x].deadline.day<<"/"<<toDoProyect.projects[i].lists[j].tasks[x].deadline.month<<"/"<<toDoProyect.projects[i].lists[j].tasks[x].deadline.year<<"|T|"<<toDoProyect.projects[i].lists[j].tasks[x].time<<endl;
                            
                        }
                    }
                }
                
            project_export << ">" << endl;
                
            }

            project_export.close();
                        
        }   else{
                error(ERR_FILE);
            
        }
        
        //Si se elige que solo un proyecto en concreto, se pedirá su id, y se comprobará que exista y su posición
    }   else{
            cout<<ID_PROYECT;
            cin>>id_Export;
            cin.get();
            
            check_Export=checkExist_ProjectId(toDoProyect,id_Export);
            posicionId_export=checkPos_ProjectId(toDoProyect,id_Export);
            
            if(check_Export == false){
                error(ERR_ID);
                
            }   else{
                    cout<<FILENAME;
                    getline(cin,export_Filename,'\n');
                    
                    project_export.open(export_Filename.c_str(),ios::out);
                    
                    if(project_export.is_open()){
                        project_export << "<" << endl;
                        project_export << "#" << toDoProyect.projects[posicionId_export].name << endl;
                
                        if(toDoProyect.projects[posicionId_export].description != ""){
                            project_export << "*" << toDoProyect.projects[posicionId_export].description << endl;
                        }
                
                        for(unsigned j=0;j<toDoProyect.projects[posicionId_export].lists.size();j++){
                            project_export << "@" << toDoProyect.projects[posicionId_export].lists[j].name << endl;
                    
                            for(unsigned x=0;x<toDoProyect.projects[posicionId_export].lists[j].tasks.size();x++){
                                if(toDoProyect.projects[posicionId_export].lists[j].tasks[x].isDone == false){
                                    project_export << toDoProyect.projects[posicionId_export].lists[j].tasks[x].name <<"|"<< toDoProyect.projects[posicionId_export].lists[j].tasks[x].deadline.day<<"/"<<toDoProyect.projects[posicionId_export].lists[j].tasks[x].deadline.month<<"/"<<toDoProyect.projects[posicionId_export].lists[j].tasks[x].deadline.year<<"|F|"<<toDoProyect.projects[posicionId_export].lists[j].tasks[x].time<<endl; 
                            
                                }   else{
                                        project_export << toDoProyect.projects[posicionId_export].lists[j].tasks[x].name <<"|"<< toDoProyect.projects[posicionId_export].lists[j].tasks[x].deadline.day<<"/"<<toDoProyect.projects[posicionId_export].lists[j].tasks[x].deadline.month<<"/"<<toDoProyect.projects[posicionId_export].lists[j].tasks[x].deadline.year<<"|T|"<<toDoProyect.projects[posicionId_export].lists[j].tasks[x].time<<endl;
                            
                                }
                            }
                        }
                
                        project_export << ">" << endl;
                        project_export.close();
                        
                    }   else{
                            error(ERR_FILE);
                        
                    }
            }
    }
}

//Funcíon que sirve para coger datos de un fichero binario e importarlos en nuestro programa
void loadData(ToDo &toDoProyect,string nombreBinario){
    ifstream project_load;
    string load_filename;
    char eleccion,eleccion_final;
    int numero_projectos=0,numero_listas=0,numero_tareas=0;
    BinToDo aux_bintodo_load;
    BinProject aux_binproject_load;
    BinList aux_binlist_load;
    BinTask aux_bintask_load;
    Project aux_project;
    List aux_list;
    Task aux_task;
    
    //Si se ha introducido mediante argumento, se seguirá por aquí con el nombre del fichero
    if(nombreBinario != ""){    
        project_load.open(nombreBinario.c_str(),ios::in | ios::binary);
    
        if(project_load.is_open()){
                toDoProyect.name.clear();
                toDoProyect.projects.clear();
                toDoProyect.nextId=1;
            
                project_load.read((char *)&aux_bintodo_load,sizeof(BinToDo));
                toDoProyect.name=aux_bintodo_load.name;
                numero_projectos=aux_bintodo_load.numProjects;
            
                for(int i=0;i<numero_projectos;i++){
                    project_load.read((char *)&aux_binproject_load,sizeof(BinProject));
                
                    aux_project.name=aux_binproject_load.name;
                    aux_project.description=aux_binproject_load.description;
                    aux_project.id=toDoProyect.nextId;
                    toDoProyect.nextId=toDoProyect.nextId + 1;
                    numero_listas=aux_binproject_load.numLists;
                        
                    toDoProyect.projects.push_back(aux_project);
                
                    for(int j=0;j<numero_listas;j++){
                        project_load.read((char *)&aux_binlist_load,sizeof(BinList));
                    
                        aux_list.name=aux_binlist_load.name;
                        numero_tareas=aux_binlist_load.numTasks;
                    
                        toDoProyect.projects[i].lists.push_back(aux_list);
                    
                        for(int x=0;x<numero_tareas;x++){
                            project_load.read((char *)&aux_bintask_load,sizeof(BinTask));
                        
                            aux_task.time=aux_bintask_load.time;
                            aux_task.isDone=aux_bintask_load.isDone;
                            aux_task.name=aux_bintask_load.name;
                        
                            aux_task.deadline.day=aux_bintask_load.deadline.day;
                            aux_task.deadline.month=aux_bintask_load.deadline.month;
                            aux_task.deadline.year=aux_bintask_load.deadline.year;
                        
                            toDoProyect.projects[i].lists[j].tasks.push_back(aux_task);
                        }
                    }
                }
            
                project_load.close();
            
        }   else{
                error(ERR_FILE);
            
        }
        
        //En caso contrario se seguirá por aquí
    }   else{
            cout<<FILENAME;
            getline(cin,load_filename,'\n');
    
            project_load.open(load_filename.c_str(),ios::in | ios::binary);
    
            //Se abre el fihcero y se pregunta si se quiere continuar, caso de que no se cerrará el fichero
            if(project_load.is_open()){
                do{
                    cout<<ELECCION;
                    cin>>eleccion;
                    cin.get();
    
                    eleccion_final=tolower(eleccion);
                }while((eleccion_final != 'y') && (eleccion_final != 'n'));
        
                //En caso de si, se borrarán todos los datos se nuestro programa y se importarán los del fichero
                if(eleccion_final == 'y'){
                    toDoProyect.name.clear();
                    toDoProyect.projects.clear();
                    toDoProyect.nextId=1;
            
                    project_load.read((char *)&aux_bintodo_load,sizeof(BinToDo));
                    toDoProyect.name=aux_bintodo_load.name;
                    numero_projectos=aux_bintodo_load.numProjects;
            
                    for(int i=0;i<numero_projectos;i++){
                        project_load.read((char *)&aux_binproject_load,sizeof(BinProject));
                
                        aux_project.name=aux_binproject_load.name;
                        aux_project.description=aux_binproject_load.description;
                        aux_project.id=toDoProyect.nextId;
                        toDoProyect.nextId=toDoProyect.nextId + 1;
                        numero_listas=aux_binproject_load.numLists;
                        
                        toDoProyect.projects.push_back(aux_project);
                
                        for(int j=0;j<numero_listas;j++){
                            project_load.read((char *)&aux_binlist_load,sizeof(BinList));
                    
                            aux_list.name=aux_binlist_load.name;
                            numero_tareas=aux_binlist_load.numTasks;
                    
                            toDoProyect.projects[i].lists.push_back(aux_list);
                    
                            for(int x=0;x<numero_tareas;x++){
                                project_load.read((char *)&aux_bintask_load,sizeof(BinTask));
                        
                                aux_task.time=aux_bintask_load.time;
                                aux_task.isDone=aux_bintask_load.isDone;
                                aux_task.name=aux_bintask_load.name;
                        
                                aux_task.deadline.day=aux_bintask_load.deadline.day;
                                aux_task.deadline.month=aux_bintask_load.deadline.month;
                                aux_task.deadline.year=aux_bintask_load.deadline.year;
                        
                                toDoProyect.projects[i].lists[j].tasks.push_back(aux_task);
                            }
                        }
                    }
            
                    project_load.close();
            
                }   else{
                        project_load.close();
                }
        
            }   else{
                    error(ERR_FILE);
            
            }
    }
}

//Función que permite exportar todos los datos de nuestros programas a un fichero binario
void saveData(ToDo &toDoProyect){
    ofstream project_save;
    string save_filename;
    
    cout<<FILENAME;
    getline(cin,save_filename,'\n');
        
    project_save.open(save_filename.c_str(),ios::out | ios::binary);
        
    if(project_save.is_open()){
        BinToDo aux_bintodo;
        BinProject aux_binproject;
        BinList aux_binlist;
        BinTask aux_bintask;
        
        //Con ayuda de auxiliares, vamos leyendo todos los proyectos y metiendolos con la función .write()
        strncpy(aux_bintodo.name,toDoProyect.name.c_str(),KMAXNAME-1);
        aux_bintodo.name[KMAXNAME-1]='\0';
        aux_bintodo.numProjects=toDoProyect.projects.size();
        
        project_save.write((const char *)&aux_bintodo,sizeof(BinToDo));
        
        for(unsigned i=0;i<toDoProyect.projects.size();i++){
            strncpy(aux_binproject.name,toDoProyect.projects[i].name.c_str(),KMAXNAME-1);
            aux_binproject.name[KMAXNAME-1]='\0';
            
            strncpy(aux_binproject.description,toDoProyect.projects[i].description.c_str(),KMAXDESC-1);
            aux_binproject.description[KMAXDESC-1]='\0';
            
            aux_binproject.numLists=toDoProyect.projects[i].lists.size();
            
            project_save.write((const char *)&aux_binproject,sizeof(BinProject));
            
            for(unsigned j=0;j<toDoProyect.projects[i].lists.size();j++){
                strncpy(aux_binlist.name,toDoProyect.projects[i].lists[j].name.c_str(),KMAXNAME-1);
                aux_binlist.name[KMAXNAME-1]='\0';
                
                aux_binlist.numTasks=toDoProyect.projects[i].lists[j].tasks.size();
            
                project_save.write((const char *)&aux_binlist,sizeof(BinList));
                
                if(aux_binlist.numTasks != 0){
                    for(unsigned x=0;x<toDoProyect.projects[i].lists[j].tasks.size();x++){
                        strncpy(aux_bintask.name,toDoProyect.projects[i].lists[j].tasks[x].name.c_str(),KMAXNAME-1);
                        aux_bintask.name[KMAXNAME-1]='\0';
                        
                        aux_bintask.time=toDoProyect.projects[i].lists[j].tasks[x].time;
                        aux_bintask.isDone=toDoProyect.projects[i].lists[j].tasks[x].isDone;
                        
                        aux_bintask.deadline.day=toDoProyect.projects[i].lists[j].tasks[x].deadline.day;
                        aux_bintask.deadline.month=toDoProyect.projects[i].lists[j].tasks[x].deadline.month;
                        aux_bintask.deadline.year=toDoProyect.projects[i].lists[j].tasks[x].deadline.year;
                            
                        project_save.write((const char *)&aux_bintask,sizeof(BinTask));
                    }    
                }
            }
        }
        
        project_save.close();
                        
    }   else{
            error(ERR_FILE);
            
    }
}

//Función que nos permite ver los prpyectos que hay y sus tareas, y la cantidad de ellas que hay hechas
void summary(const ToDo &toDoProyect){

    for(unsigned i=0;i<toDoProyect.projects.size();i++){   
        int contador=0;
        int contadorTotal=0;
        
        if(toDoProyect.projects[i].lists.size() != 0){
            for(unsigned j=0;j<toDoProyect.projects[i].lists.size();j++){
                for(unsigned x=0;x<toDoProyect.projects[i].lists[j].tasks.size();x++){
                    
                    if(toDoProyect.projects[i].lists[j].tasks[x].isDone == true){
                        contador++;
                        contadorTotal++;
                        
                    }   else{
                            contadorTotal++;
                    }
                    
                }
            }
        }
              
        cout<<"("<<toDoProyect.projects[i].id<<") "<<toDoProyect.projects[i].name<<" ["<<contador<<"/"<<contadorTotal<<"]"<<endl;

    }
            
}


//Función para comprobar que los argumentos no sean erroneos y poder sacar sus nombres
bool comprobar_Argumentos(int argc, char *argv[],string &fileBin,string &fileText){
    bool correctArgument = true;
    fileBin = "";
    fileText = "";
    for(int i = 1;i<argc;i++){
        if(strcmp(argv[i],"-i")==0){
            fileText = argv[i+1];
            i++;
            
        }   else{
                if(strcmp(argv[i],"-l")==0){
                    fileBin = argv[i+1];
                    i++;
                    
                }   else{
                        correctArgument=false;
                }
        }
    }
    
    return correctArgument;
}

int main(int argc, char *argv[]){
    char option;
    ToDo toDoProyect;
    toDoProyect.nextId=1;
    toDoProyect.name="My ToDo list";
    string fileBin,fileText;
    bool argumentos_correctos;
  
    argumentos_correctos=comprobar_Argumentos(argc,argv,fileBin,fileText);
  
    if(argumentos_correctos == false){
      error(ERR_ARGS);
      
    }   else{
            if(fileText != ""){
                 importProjects(toDoProyect,fileText);
            }
            
            if(fileBin != "" && argumentos_correctos == true){
                 loadData(toDoProyect,fileBin);
            }
            
            if(argumentos_correctos == true){
                    do{
                        showProyectMenu();
                        cin >> option;
                        cin.get();
    
                        switch(option){
                            case '1': projectMenu(toDoProyect);
                                        break;
                            case '2': addProject(toDoProyect);
                                        break;
                            case '3': deleteProject(toDoProyect);
                                        break;
                            case '4': importProjects(toDoProyect,fileText);
                                        break;
                            case '5': exportProjects(toDoProyect);
                                        break;
                            case '6': loadData(toDoProyect,fileBin);
                                        break;
                            case '7': saveData(toDoProyect);
                                        break;
                            case '8': summary(toDoProyect);
                                        break;
                            case 'q': break;
                            default: error(ERR_OPTION);
                        }
                    }while(option!='q');
            }
    }
    
    return 0;    
}
