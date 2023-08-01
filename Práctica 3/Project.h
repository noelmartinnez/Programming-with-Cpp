//NOEL MARTÍNEZ POMARES    DNI: 48771960T
#ifndef _Project_
#define _Project_
#include <iostream>
#include <vector>
#include "List.h"
using namespace std;

class Project{
    
    friend ostream& operator<<(ostream &os,const Project &project);
    
    protected:
        int id;
        string name;
        string description;
        vector<List> lists;
        int getPosList(string name) const;
        
    public:    
        Project(string name, string description="");
        
        int getId() const{ return id; };
        string getName() const{ return name; };
        string getDescription() const{ return description; };
        bool setId(int id);
        bool setName(string name);
        void setDescription(string description);
        void edit(string name="",string description="");
        void addList(string name="");
        void deleteList(string name="");
        void addTaskToList(string name="");
        void deleteTaskFromList(string name="");
        void toggleTaskFromList(string name="");
        void menu();
        string summary() const;
};
    
#endif