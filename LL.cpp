#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData();//Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here


// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list

template <class T>
LL<T>::LL(){
  m_head = nullptr;//set private members to defaults
  m_size = 0;
}

// Name: ~LL() - Destructor
// Desc: Used to destruct a LL

template <class T>
LL<T>::~LL(){
  Node<T> *curr = m_head;
  while(curr != nullptr){ 
    m_head = curr; 
    curr = curr ->GetNext(); //moves curr to next node
    delete m_head; //delete m_head;
  }
  m_head = nullptr;//set private members to defaults
  m_size = 0;
}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values

template <class T>
LL<T>::LL(const LL& other){
  m_size = other.m_size;//set size equal to assigned LL
  if(other.m_head){//m_head not null meaning other is populated
    Node<T> *temp, *curr;
    temp = other.m_head;
    m_head = new Node<T> (temp->GetData().first);//set m_head to new node with same value as assigned LL first node but with frequency of 1
    m_head ->SetData(temp->GetData());//sets m_head node to same int frequency
    curr = m_head;
    temp = temp ->GetNext();
    while(temp != nullptr){//itterates through LL and assigns nodes to assigned LL 
      curr ->SetNext(new Node<T> (temp->GetData().first));
      curr = curr -> GetNext();
      curr ->SetData(temp->GetData());
      temp = temp ->GetNext();
    }
  }
}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values

template <class T>
LL<T>& LL<T>::operator= (const LL& other){
  if(this != &other){//checks for self assign
    m_size = other.m_size;
    if(other.m_head){
      Node<T> *temp, *curr;
      temp = other.m_head;
      m_head = new Node<T> (temp->GetData().first);
      m_head ->SetData(temp->GetData());
      curr = m_head;
      temp = temp ->GetNext();
      while(temp != nullptr){
	curr ->SetNext(new Node<T> (temp->GetData().first));
	curr = curr -> GetNext();
	curr ->SetData(temp->GetData());
	temp = temp ->GetNext();
      }
    }
  }
  return *this;
}

// Name: Find
// Desc: Iterates through LL and returns node if data found

template <class T>
Node<T>* LL<T>:: Find(const T& data){

  Node<T> *it = m_head;
  for(int i = 0; i < m_size; i++){//iterates LL
    if(it->GetData().first == data){//checks if data is in linked list
      return it;//returns node ptr of data location
    }
    it = it ->GetNext();
  }
  return nullptr;//returns null if not in LL
}

// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first

template <class T>
void LL<T>::Insert(const T& data){
 
  if(!m_head){//if LL empty adds a new node
    
    m_head = new Node<T>(data);
    m_size++;
    return;
  }
  Node<T> *it = Find(data);//checks if data is already in LL
  if(it == nullptr){//if data not in LL
    if(data < m_head->GetData().first){// checks if data is less than first node
      Node<T> *temp = new Node(data);
      it = m_head;
      temp ->SetNext(it);//makes node with data the first node if its less than current first node
      m_head = temp;
      m_size++;
      return;
    }
    it = m_head;
    while((it ->GetNext() != nullptr) and (data > it ->GetNext()-> GetData().first)){//iterates till last position or till in the correct position in LL
      it = it->GetNext();
    }
    Node<T> *temp = new Node(data);
    temp -> SetNext(it->GetNext());//enters the position it belongs in LL
    it -> SetNext(temp);
    m_size++;
    return;
  }
  else{//if data already in LL increanses frequency int
    pair<T,int> newData;
    newData = it -> GetData();
    newData.second = newData.second + 1;
    it ->SetData(newData);
    return;
  }
}

// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)

template <class T>
void LL<T>::RemoveAt(const T& data){
  
  Node<T> *prev, *curr;
  curr = Find(data);//finds node ptr of data in LL
  if(curr){// if data in LL
    prev = m_head;
    if (curr == prev){
      m_head = m_head ->GetNext();//if data is the first node, delete it
    }
    else{
      while(prev->GetNext() != curr){//iterate til it reaches data in LL then deletes it
	prev = prev->GetNext();
      }
      prev->SetNext(curr->GetNext());
    }
    delete curr;
    m_size--;
  }
}

// Name: Display
// Desc: Display all nodes in linked list

template <class T>
void LL<T>::Display(){
  cout<< *this << endl; //uses << operator
}

// Name: GetSize
// Desc: Returns the size of the LL

template <class T>
int LL<T>::GetSize(){
  return m_size;
}

// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node

template <class U>
ostream& operator<<(ostream& output, const LL<U>& ll){
  Node<U> *temp = ll.m_head;
  while(temp != nullptr){
    output << temp->GetData().first << ":" << temp->GetData().second << endl;//iterates LL and enters data from LL into output
    temp = temp ->GetNext();
  }
  return output;
}

// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location

template <class T>
pair<T,int>& LL<T>::operator[] (int x){
  Node<T> *it = m_head;
  for(int i = 0; i < x; i++){//iterates LL until it reaches position them outputs data at position
    it = it -> GetNext();
  }
  return it->GetData();
}

