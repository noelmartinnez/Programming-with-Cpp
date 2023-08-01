#include "ToDo.h"
#include "Project.h"
#include "Util.h"
#include <iostream>
using namespace std;

const string ID_PROYECT = "Enter project id: ";

//Devuelve la posición del project con el id pasado por parametro si existe, sino devuelve -1
int ToDo::getPosProject(int id) const{
     for(unsigned i=0;i<projects.size();i++){
        if(projects[i]->getId() == id){
            return i;
        }
    }
    
    return -1;    
}

//Devuelve la posición del project de nombre name si existe, sino devuelve -1
int ToDo::getPosProject(string name) const{
     for(unsigned i=0;i<projects.size();i++){
        if(projects[i]->getName() == name){
            return i;
        }
    }
    
    return -1;   
}

//Constructor que se encarga de crear un objeto todo, se lanza una excepción si name es vacio 
ToDo::ToDo(string name){
    if(name == ""){
        throw ERR_EMPTY;
    }
    else{
        this->name=name;
    }
}

//Se declara aquí al ser static
int ToDo::nextId=1;

//Cambia el nombre del objeto si no se le pasa un name vacio
bool ToDo::setName(string name){
    bool comprobar=false;
    
    if(name == ""){
        Util::error(ERR_EMPTY);
        return comprobar;
    }
    else{
        this->name=name;
        comprobar=true;
        return comprobar;
    }
}

//Añade un project al vector de punteros a projects
void ToDo::addProject(Project *project){
    if(getPosProject(project->getName()) >= 0){
        throw ERR_PROJECT_NAME;
    }
    else{
        project->setId(nextId);
        
        //Se aumenta el nextId
        nextId++;
        this->projects.push_back(project);
    }

}

//Se elimina el project con el id pasado como parametro del vector projects
void ToDo::deleteProject(int id){
    int deleteIdProject;
    
    if(id == 0){
        cout<<ID_PROYECT;
        cin>>deleteIdProject;
        cin.get();
        
        //Si existe el project con el id, se eliminará del vector
        if(getPosProject(deleteIdProject) >= 0){
            projects.erase(projects.begin()+getPosProject(deleteIdProject));
        }
        else{
            Util::error(ERR_ID);
        }
    }
    else{
        if(getPosProject(id) >= 0){
            projects.erase(projects.begin()+getPosProject(id));
        }
        else{
            Util::error(ERR_ID);
        }
    }
}

//Funcion que llama a la función de Project para cambiar el nombre y la descripción del project
void ToDo::setProjectDescription(string name,string description){
    if(getPosProject(name) >= 0){
        projects[getPosProject(name)]->setDescription(description);
    }
    else{
        Util::error(ERR_PROJECT_NAME);
    }
}

//Función que llama a la función menu() del project con el id pasado como parametro
void ToDo::projectMenu(int id){
    int menuIdProject;
    
    if(id == 0){
        cout<<ID_PROYECT;
        cin>>menuIdProject;
        cin.get();
        
        //Si existe el project con el id, se llamará a la función
        if(getPosProject(menuIdProject) >= 0){
            projects[getPosProject(menuIdProject)]->menu();            
        }
        else{
            Util::error(ERR_ID);
        }
    }
    else{
        if(getPosProject(id) >= 0){
            projects[getPosProject(id)]->menu();
        }
        else{
            Util::error(ERR_ID);
        }
    }
}

//Función que muestra todos los datos de todos los projectos, llamando a la función summary de todos los projectos
ostream& operator<<(ostream &os,const ToDo &toDo){
    for(unsigned i=0;i<toDo.projects.size();i++){
        os<<toDo.projects[i]->summary();
    }
    
    return os;
}


