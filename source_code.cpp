

#include <iostream>
#include "BST.h"
#include "heap.h"
#include <fstream>
#include <string>

using namespace std;

int main() {
    BST bstTree;                 ///BST object
    MinHeap tree;                ///minimum heap object
    Task *task;                  ///task object
    int duration;                ///duration of the task
    int n;
    string description;          ///description of the task
    string category;             ///category of the task
    Node *arr[100];              /// an array to store the tasks
    Task *array[100];            ///an array to store task object
    int nu = 0;                  /// the size of the heap
    int numOfTasks;              ///variable that stores the number of tasks
    int option=0;                ///variable to store option number


    ///Taking the data from a file
    string fileName;
    cout<<"please Enter the file name with '.txt' at the end"<<endl;
    getline(cin,fileName);
    ///enter the file name (ex:file name.txt)
    ifstream ifile(fileName);
    ifile >> numOfTasks;
    ifile.ignore();
    for(int i =0 ;i < numOfTasks ; i++)
    {
        getline(ifile,description);
        ifile >> duration;
        ifile.ignore();
        getline(ifile,category);
        task = new Task(description,duration,category);
        bstTree.insertTask(task);

    }


    ///Menu that displays for the user to choose options from
    while(option != 9)
    {
        cout<<endl;
        cout<<"--------------------------------------------------------------"<<endl;
        cout<<"MENU"<<endl<<endl<<
            "1. Insert a task (using BST Class)"<<endl<<
            "2. Display all (using BST Class)"<<endl<<
            "3. Search for a task (using BST Class)"<<endl<<
            "4. Remove a task (using BST Class)"<<endl<<
            "5. Display more than (using BST Class)"<<endl<<
            "6. Display less than (using BST Class)"<<endl<<
            "7. Mark a task as completed by task duration and description (using heap Class)"<<endl<<
            "8. Display all completed tasks and the number of tasks completed per category (using heap Class)"<<endl<<
            "9. exit "<<endl;
        cout<<"--------------------------------------------------------------"<<endl;

        cout<<"Enter number of option: ";
        cin>>option;

        ///1. Insert a task (using BST Class)
        if(option == 1)
        {
            cout<<"Enter tasks description: ";
            cin.ignore();
            getline(cin,description);
            cout<<"Enter duration: ";
            cin>>duration;
            cout<<"Enter Category: ";
            cin.ignore();
            getline(cin,category);
            task = new Task(description,duration,category);
            bstTree.insertTask(task);
            numOfTasks++;
            cout<<"the task is added "<<endl;
        }


            ///2. Display all (using BST Class)
        else if (option==2)
        {
            cout<<"//"<<numOfTasks<<" tasks are printed"<<endl;
            bstTree.displayAll(bstTree.root);
        }

            ///3. Search for a task (using BST Class)
        else if(option==3)
        {
            int cnt;
            cout<<"Enter the duration: ";
            cin>>duration;
            cnt=bstTree.searchCount(bstTree.root,duration);
            if (cnt == 0)
            {
                cout << "No tasks found with this duration." << endl;
            }
            else
            {
                cout << "//" << cnt << " tasks are found" << endl;
            }
            bstTree.search(bstTree.root,duration);

        }

            ///4. Remove a task (using BST Class)
        else if(option==4)
        {
            cout<<"Enter the duration: ";
            cin>>duration;
            int cnt = 0;
            bstTree.removeTask(bstTree.root,duration, cnt);
            cout << "//"<<cnt << " tasks are removed" << endl;
            while(cnt!=0)
            {
                numOfTasks--;
                cnt--;
            }
        }

            ///5. Display more than (using BST Class)
        else if(option==5)
        {
            int cnt;
            cout<<"Enter the duration more than: ";
            cin>>duration;
            cnt=bstTree.displayMoreThanCount(bstTree.root,duration);
            if (cnt == 0)
            {
                cout << "No tasks found with this duration." << endl;
            }
            else
            {
                cout << "//" << cnt << " tasks are found" << endl;
            }
            bstTree.displayMoreThan(bstTree.root,duration);
        }

            ///6. Display less than (using BST Class)
        else if(option==6)
        {
            int cnt;
            cout<<"Enter the duration less than: ";
            cin>>duration;
            cnt=bstTree.displayLessThanCount(bstTree.root,duration);
            if (cnt == 0)
            {
                cout << "No tasks found with this duration." << endl;
            }
            else
            {
                cout << "//" << cnt << " tasks are found" << endl;
            }
            bstTree.displayLessThan(bstTree.root,duration);
        }

            ///7. Mark a task as completed by task duration and description (using heap Class)
        else if (option == 7)
        {
            Node *arr[100];
            cout<<"Task duration: ";
            cin>>duration;
            cout<<"Task description: ";
            cin.ignore();
            getline(cin,description);
            bool check=tree.MarkTaskCompleted(bstTree,duration,description,nu);
            if (check==true)
            {
                numOfTasks--;
            }
        }

            ///8. Display all completed tasks and the number of tasks completed per category (using heap Class)
        else if(option == 8)
        {
            cout<<"//min heap tree is printed"<<endl;
            tree.displayHeap();
            tree.displayCategoryReport();
        }
        else if(option == 9)
        {
            cout<<"EXIT"<<endl;
        }
        else
        {
            cout<<"INVALID option , please insert another option"<<endl;
        }
    }
    return 0;
}
