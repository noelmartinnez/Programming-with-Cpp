//NOEL MARTÍNEZ POMARES    DNI: 48771960T
#ifndef _List_
#define _List_
#include <iostream>
#include <vector>
#include "Task.h"
using namespace std;

class List{
    
    friend ostream& operator<<(ostream &os,const List &list);
    
    protected:
        string name;
        vector<Task> tasks;
        
    public:    
        List(string name);
        string getName() const{ return name; };
        vector<Task>getTasks() const{ return tasks; };
        unsigned getNumTasks() const;
        unsigned getNumDone() const;
        int getTimeTasks() const;
        int getTimeDone() const;
        int getPosTask(string name) const;
        bool setName(string name);
        void addTask(Task task);
        bool deleteTask(string name);
        bool toggleTask(string name);
};
    
#endif