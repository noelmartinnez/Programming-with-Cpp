//NOEL MARTÍNEZ POMARES    DNI: 48771960T
#ifndef _ToDo_
#define _ToDo_
#include "Project.h"
#include <iostream>
using namespace std;

class ToDo{
    
    friend ostream& operator<<(ostream &os,const ToDo &toDo);
    
    protected:
        static int nextId;
        string name;
        int getPosProject(string name) const;
        int getPosProject(int id) const;
        vector<Project*> projects;
        
    public:    
        ToDo(string name);
        string getName() const{ return name; };
        bool setName(string name);
        void addProject(Project *project);
        void deleteProject(int id=0);
        void setProjectDescription(string name,string description);
        void projectMenu(int id=0);
       
};
    
#endif