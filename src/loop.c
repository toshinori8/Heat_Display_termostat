// Example program
#include <iostream>
#include <string>

struct Node
{
    int data; Node *prev,*next;
    Node(int x, Node* prev=NULL, Node* next=NULL)
    {
        this->data=x; this->prev=prev; this->next=next;
    }
    void print_list()
    {
        Node* temp=this;    //temp is created in function call stack
        while(temp!=NULL)
        {
            std::cout<<temp->data<<" ";
            temp=temp->next;
        }
    }
    Node* insert_left(int x)
    {
        Node* temp=new Node(x,this->prev,this);
        this->prev=temp;
        return temp;                            //list gets new head
    }
    Node* insert_right(int x)
    {
        Node* temp=new Node(x,this,this->next);
        this->next=temp;
        return this;                            //this would still be head
    }

};

int main()
{
    Node* head=new Node(-1);    //-1
    head=head->insert_left(0);  //0 -1
    head=head->insert_right(1); //0 1 -1
    head=head->insert_left(2);  //2 0 1 -1
    head->print_list();
}