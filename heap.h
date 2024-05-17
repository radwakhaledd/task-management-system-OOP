
///Implement Min-heap tree to store tasks objects based on task duration. The heap tree will be used when user finishes a task.
/// it will be marked as completed and removed from the binary tree to be sorted in a heap tree.


#ifndef UNTITLED75_HEAP_H
#define UNTITLED75_HEAP_H
#include <iostream>
#include <string>
#include "BST.h"
using namespace std;

///Min-heap tree to store tasks objects based on task duration.
class MinHeap
{
public:
    Node * root;
    Node **arr;
    int n=0;
    int EducationalCount=0,HealthCount = 0,SelfdevelopmentCount = 0,FoodCount = 0,OtherCount = 0;

    ///function to construct minimum heap
    void min_heapify(Node** arr, int n, int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left]->data->durationMin > arr[smallest]->data->durationMin)
            smallest = left;

        if (right < n && arr[right]->data->durationMin > arr[smallest]->data->durationMin)
            smallest = right;

        if (smallest != i)
        {
            Node* temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            min_heapify(arr, n, smallest);
        }
    }

    ///function to build minimum heap
    void buildHeap(Node** arr, int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
            min_heapify(arr, n, i);
    }

    ///sort function
    void heapSort(Node** arr, int n)
    {
        buildHeap(arr, n);
        for (int i = n - 1; i >= 0; i--)
        {
            swap(arr[0], arr[i]);
            min_heapify(arr, i, 0);
        }
    }


    ///function that inserts a task in min heap

    bool MarkTaskCompleted(BST& bstTree, int dur, const string& desc, int& nu)
    {
        Task* newtask = new Task(desc, dur, "");
        Node* newt = new Node(newtask);
        Node* newTask = bstTree.searchInBst(bstTree.root, newt->data->description, dur);

        /// Check if the user input matches the description
        if (newTask == nullptr || !bstTree.checkDesc(newTask->data->description, desc))
        {
            cout << "The task you entered is not found in the tasks list" << endl;
            /// Free the memory allocated for the new task
            delete newt;
            return false;
        }
        else
        {
            newt->data->category = newTask->data->category;
            newt->data->description = newTask->data->description;
            newt->data->durationMin = newTask->data->durationMin;
            /// Increase the array size by 1
            Node** newArr = new Node*[nu + 1];

            for (int i = 0; i < nu; i++)
            {
                newArr[i] = new Node(arr[i]->data); // Copy the existing nodes to the new array
            }
            newArr[nu] = newt;
            nu++;
            n = nu;
            /// Free the memory allocated for the previous array
            for (int i = 0; i < nu - 1; i++)
            {
                delete arr[i];
            }
            delete[] arr;

            arr = newArr;                             /// Update the arr pointer to the new array
            bstTree.removeTaskFromBst(bstTree.root, newTask->data->description, dur);
            cout << "This task is removed" << endl;
            return true;
        }
    }


  /*  void displayTree(Node* root)
    {
        if (root == nullptr)
            return;

        /// Display the root node
        cout << "[" << root->data->description << " , " << root->data->durationMin << " , " << root->data->category << "]" << endl;

        /// Display left subtree
        displayTree(root->left);

        /// Display right subtree
        displayTree(root->right);
    }

*/
    ///display heap

    void displayHeap()
    {
        //cout<<"//min heap tree is printed"<<endl;
        heapSort(arr,n);
        if (n == 0)
        {
            cout << "The heap is empty." << endl;
            return;
        }

        for (int i = 0; i < n; i++)
        {
            cout << "[" << arr[i]->data->description << " , " << arr[i]->data->durationMin << " , " << arr[i]->data->category << "]" << endl;
        }
    }


    ///function that display category report
    void displayCategoryReport()
    {
        int EducationalCount=0,HealthCount = 0,SelfdevelopmentCount = 0,FoodCount = 0,OtherCount = 0;
        for(int i=0;i<n;i++)
        {
            if (arr[i]->data->category=="Educational")
                EducationalCount++;
            else if (arr[i]->data->category=="Health")
                HealthCount++;
            else if (arr[i]->data->category=="Self development")
                SelfdevelopmentCount++;
            else if (arr[i]->data->category=="Food")
                FoodCount++;
            else if (arr[i]->data->category=="Other")
                OtherCount++;
        }
        cout<<"//Category report"<<endl<<
            "Educational = "<<EducationalCount<<endl<<
            "Health = " <<HealthCount<<endl<<
            "Self development = "<<SelfdevelopmentCount<<endl<<
            "Food = "<<FoodCount<<endl<<
            "Other = "<<OtherCount<<endl;
    }

};




#endif //UNTITLED75_HEAP_H
