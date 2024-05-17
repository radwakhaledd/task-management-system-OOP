
///This program builds a class for representing “task object” and another class for representing binary search tree.
///The BST will store the tasks according to their duration, and will include several functions

#ifndef UNTITLED75_BST_H
#define UNTITLED75_BST_H
#include <iostream>
#include <string>

using namespace std;
///class that represents the task object (description, duration , category)
class Task
{
public:
    string description;          ///task description
    int durationMin;             ///task duration
    string category;             ///task category

    ///parametrized constructor for task class task that takes description , duration and category
    Task(string descript, int duration, string cg)
    {
        description = descript;
        durationMin = duration;
        category = cg;
    }
};


///class that represents node of BST
class Node
{
public:
    Task* data;             ///data of the node which is a task object
    Node *left;             ///pointer that points to the left of the node
    Node *right;            ///pointer that points to the right of the node

    ///default constructor
    Node()
    {
        data = new Task("", 0, "");
        left = right = NULL;
    }

    ///parametrized constructor that takes task value
    Node(Task* value)
    {
        data = value;
        left = right = NULL;
    }

};
///Binary search tree class that constructs the BST
class BST{
public:
    int cnt=0;         ///count
    Node* root;        ///the root of the BST

    ///default constractor
    BST()
    {
        root=NULL;
    }

    ///function that Inserts a task (input: description, duration, and category) where equal values of duration are added as left child.
    Node* insertTask(Node* r, Task* item)
    {
        if(r == NULL)
        {
            Node* newnode = new Node(item);
            r=newnode;
        }

        else if(item->durationMin <= r->data->durationMin)
        {
            r->left = insertTask(r->left, item);
        }
            ///otherwise if the duration of item is greater than the duration of data of root
        else
        {
            r->right= insertTask(r->right,item);
        }
        return r;

    }

    ///overloading the insert function but with task object parameter only
    void insertTask(Task* item)
    {
        root=insertTask(root,item);
    }

    ///function tha Displays all (in-order)
    void displayAll(Node* item)
    {
        if(item != NULL)
        {
            displayAll(item->left);
            cout<<"["<<item->data->description<<", "<<item->data->durationMin<<", "<<item->data->category<<"]"<<endl;
            displayAll(item->right);
        }
    }

    ///function that counts the number of tasks
    int searchCount(Node* r,int dur)
    {
        if (r != NULL)
        {
            if (r->data->durationMin == dur)
            {
                cnt++;
            }
            searchCount(r->left, dur);
            searchCount(r->right, dur);
        }
        return cnt;
    }

    ///function that Searches for a task(by duration)
    void search(Node* r, int dur)
    {
        cnt=0;
        if (r != NULL) {

            if (r->data->durationMin == dur)
            {
                cout<<"["<<r->data->description<<" , "<<r->data->durationMin<<" , "<<r->data->category<<"]"<<endl;
            }
            search(r->left, dur);
            search(r->right, dur);
        }
    }


    ///function that finds the minimum node on the left
    Node* findMin(Node* r)
    {
        if(r == NULL)
            return NULL;
        else if(r->left ==NULL)
            return r;
        else
            return findMin(r->left);

    }


    ///function that Removes a task (remove all tasks with the exact input duration)
    Node* removeTask(Node* r,int duration, int& cnt)
    {

        Node* temp = r;
        if(r ==NULL)
        {
            return NULL;
        }

        if(duration <= r->data->durationMin)
        {
            r->left = removeTask(r->left,duration,cnt);
        }

        else if(duration > r->data->durationMin)
        {
            r->right = removeTask(r->right,duration,cnt);
        }

        if(r->data->durationMin == duration)
        {

            if (r->left == NULL && r->right == NULL)
            {
                delete r;
                r = NULL;
                cnt++;
            }
            else if (r->left != NULL && r->right == NULL)
            {

                temp = r;
                r=r->left;
                delete temp;
                cnt++;

            }
            else if (r->left == NULL && r->right != NULL)
            {

                temp = r;
                r=r->right;
                delete temp;
                cnt++;

            }
            else
            {
                Node *maximum = findMin(r->right);
                r->data = maximum->data;
                r->right = removeTask(r->right, maximum->data->durationMin,cnt);

            }

        }
        return r;
    }

    ///function that displays the count of the tasks >= certain duration
    int displayMoreThanCount(Node* r,int dur)
    {
        if (r != NULL)
        {
            if (r->data->durationMin >= dur)
            {
                cnt++;
            }
            displayMoreThanCount(r->left, dur);
            displayMoreThanCount(r->right, dur);
        }
        return cnt;
    }

    ///Display more than (display all tasks having > or = input duration)
    void displayMoreThan(Node* r,int duration)
    {
        cnt=0;
        if (r != NULL)
        {
            displayMoreThan(r->left, duration);
            if (r->data->durationMin >= duration)
            {
                cout<<"["<<r->data->description<<" , "<<r->data->durationMin<<" , "<<r->data->category<<"]"<<endl;
            }
            displayMoreThan(r->right, duration);
        }
    }


    ///function that displays the count of the tasks < certain duration
    int displayLessThanCount(Node* r,int dur)
    {
        if (r != NULL)
        {
            displayLessThanCount(r->left, dur);
            if (r->data->durationMin < dur)
            {
                cnt++;
            }
            displayLessThanCount(r->right, dur);
        }
        return cnt;
    }

    ///Display less than (display all tasks having < input duration)
    void displayLessThan(Node* r,int duration)
    {
        cnt=0;
        if (r != NULL)
        {
            displayLessThan(r->left, duration);
            if (r->data->durationMin < duration)
            {
                cout<<"["<<r->data->description<<" , "<<r->data->durationMin<<" , "<<r->data->category<<"]"<<endl;
            }
            displayLessThan(r->right, duration);
        }
    }

    ///function that removes task from the binary search tree
    Node* removeTaskFromBst(Node* r,const string& description,int duration) {

        Node *temp = r;
        if (r == NULL) {
            return NULL;
        }

        if (duration <= r->data->durationMin || checkDesc(r->data->description, description))
        {
            r->left = removeTaskFromBst(r->left, description, duration);
        }
        else if (duration > r->data->durationMin || checkDesc(r->data->description, description))
        {
            r->right = removeTaskFromBst(r->right, description, duration);
        }

        if (r->data->durationMin == duration && checkDesc(r->data->description, description))
        {

            if (r->left == NULL && r->right == NULL)
            {
                delete r;
                r = NULL;
            }
            else if (r->left != NULL && r->right == NULL)
            {
                temp = r;
                r = r->left;
                delete temp;
            }
            else if (r->left == NULL && r->right != NULL)
            {
                temp = r;
                r = r->right;
                delete temp;
            }
            else
            {
                Node *maximum = findMin(r->right);
                r->data = maximum->data;
                r->right = removeTaskFromBst(r->right, maximum->data->description, maximum->data->durationMin);
            }
        }
        return r;
    }


    ///function that allows the user to search for task (upper case, lower case) or by typing part of the description
    bool checkDesc(string desc, string insertedDesc)
    {
        /// Convert both strings to lowercase
        for (int i = 0; i < desc.length(); i++)
        {
            desc[i] = tolower(desc[i]);
        }
        for (int i = 0; i < insertedDesc.length(); i++)
        {
            insertedDesc[i] = tolower(insertedDesc[i]);
        }

        /// Check if inserted description is a substring of the description found in file
        int i = 0, j = 0;
        while (i < desc.length() && j < insertedDesc.length())
        {
            if (desc[i] == insertedDesc[j])
            {
                j++;
            }
            i++;
        }
        return (j == insertedDesc.length());
    }

    ///function that search for a certain task takes task description and duration as parameters
    Node* searchInBst(Node* r, string &description, int dur) {
        r = root;
        while (r != NULL) {
            if (r->data->durationMin == dur && checkDesc(r->data->description, description))
            {
                cout << "[" << r->data->description << " , " << r->data->durationMin << " , " << r->data->category << "]" << endl;
                return r;
            }
            else if (dur < r->data->durationMin)
            {
                r = r->left;
            }
            else if (dur > r->data->durationMin)
            {
                r = r->right;
            }
            else if (description < r->data->description)
            {
                r = r->left;
            }
            else {
                r = r->right;
            }
        }
        return NULL;
    }


};


#endif //UNTITLED75_BST_H
