#include <iostream>
#include <queue>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

//Class Declarations

template <typename T>
class Node{
public:
    Node<T>* left=nullptr;
    Node<T>* right=nullptr;
    T value;
    vector<T> inOrder(vector<T>& vault);
    vector<T> preOrder(vector<T>& vault);
    vector<T> postOrder(vector<T>& vault);
    //    void remove(T value, int& numofnodes, Node<T>*& cum);
    void remove(Node<T>* Node,T value, int& numofnodes);
    bool includes(T value);
    void insert(T value);
};
template <typename T>
class BinarySearchTree {
private:
    Node<T>* head=nullptr;
    int numofnodes{0};
public:
    //    BinarySearchTree();
    bool includes(T value);
    void insert(T value);
    void remove(T value);
    vector<T> inOrder();
    vector<T> preOrder();
    vector<T> postOrder();
    int size();
    bool isEmpty() {return size() == 0;}
};

//Method Declaration
//template <typename T>
//BinarySearchTree<T>::BinarySearchTree(){
//     BinarySearchTree<T>->numofnodes=0;
//};
template <typename T>
bool BinarySearchTree<T>::includes(T valve){
    return head->includes(valve);
}

template <typename T>
vector<T> BinarySearchTree<T>::inOrder(){
    vector<T> DespicableMe;
    return head->inOrder(DespicableMe);
}

template <typename T>
vector<T> BinarySearchTree<T>::preOrder(){
    vector<T> DespicableMe;
    return head->preOrder(DespicableMe);
}
template <typename T>
vector<T> BinarySearchTree<T>::postOrder(){
    vector<T> cheddar;
    return head->postOrder(cheddar);
}
template <typename T>
void BinarySearchTree<T>::insert(T value){
    numofnodes+=1;
    if(head){
        head->insert(value);
    }
    else{
        Node<T>* newnode= new Node<T>;
        newnode->value=value;
        head=newnode;
    }
}


template <typename T>
void BinarySearchTree<T>::remove(T valve){
    head->remove(head,valve,numofnodes);
}
template <typename T>
int BinarySearchTree<T>::size(){
    return numofnodes;
}
template <typename T>
void Node<T>::insert(T valve){
    if(valve>value){
        if(right!=nullptr){
            right->insert(valve);
        }
        else{
            Node<T>* newnode=new Node<T>;
            newnode->value=valve;
            right=newnode;
        }
    }
    else if(valve<value){
        if(left!=nullptr){
            left->insert(valve);
        }
        else{
            Node<T>* newnode=new Node<T>;
            newnode->value=valve;
            left=newnode;
        }
    }
}

template <typename T>
vector<T> Node<T>::inOrder(vector<T>& vault){
    if(left){
        left->inOrder(vault);
    }
    vault.push_back(value);
    if(right){
        right->inOrder(vault);
    }
    return vault;
}

template <typename T>
vector<T> Node<T>::preOrder(vector<T>& cheese){
    cheese.push_back(value);
    if(left){
        left->preOrder(cheese);
    }
    if(right){
        right->preOrder(cheese);
    }
    return cheese;
}

template <typename T>
vector<T> Node<T>::postOrder(vector<T>& cheese){
    if(left){
        left->postOrder(cheese);
    }
    if(right){
        right->postOrder(cheese);
    }
    cheese.push_back(value);
    return cheese;
}

template <typename T>
bool Node<T>::includes(T cheese){
    if(cheese<value){
        if(left!=nullptr){
            left->includes(cheese);
        }
    }
    else if(cheese>value){
        if(right!=nullptr){
            right->includes(cheese);
        }
    }
    else if(cheese==value){
        return true;
    }
    else{
        return false;
    }
}

template <typename T>
void Node<T>::remove(Node<T>* previous,T cheese, int& numofnodes){
    if(cheese>value){
        if(right!=nullptr){
            this->right->remove(this,cheese,numofnodes);
        }
        return;
    }
    if(cheese<value){
        if(left!=nullptr){
            this->left->remove(this,cheese,numofnodes);
        }
        return;
    }

    if(left==nullptr && right==nullptr){
        if(previous->right!=nullptr){
        if(previous->right->value==cheese){
            previous->right=nullptr;
            delete this;
        }
        else{
            if(previous->left!=nullptr){
            previous->left=nullptr;
            delete this;
            }
        }
        }
        return;
    }

    if((left==nullptr && right!=nullptr) || (left!=nullptr && right==nullptr)){
        if(left!=nullptr){
            if(previous->right->value==cheese){
                previous->right=left;
                delete this;
            }
            else{
                previous->left=left;
                delete this;
            }
        }
        if(right!=nullptr){
            if(previous->right->value==cheese){
                previous->right=this->right;
                delete this;
            }
            else{
                previous->left=this->right;
                delete this;
            }
        }
        return;
    }
    Node<T>* Replacement=right;
    while(Replacement->left!=nullptr){
        Replacement=Replacement->left;
    }
    this->value=Replacement->value;
    right->remove(right,Replacement->value,numofnodes);
    numofnodes-=1;
}
//Testing
TEST(BinarySearchTrees,InOrder){
    BinarySearchTree<int> sum;
    sum.insert(10);
    sum.insert(17);
    sum.insert(25);
    sum.insert(15);
    ASSERT_EQ(sum.inOrder(),vector<int> ({10,15,17,25}));
}
TEST(BinarySearchTrees,Preorder){
    BinarySearchTree<int> sum;
    sum.insert(25);
    sum.insert(15);
    sum.insert(50);
    sum.insert(70);
    sum.insert(35);
    sum.insert(31);
    sum.insert(44);
    sum.insert(66);
    sum.insert(90);
    sum.insert(10);
    sum.insert(22);
    sum.insert(18);
    sum.insert(24);
    sum.insert(4);
    sum.insert(12);
    ASSERT_EQ(sum.preOrder(),vector<int> ({25,15,10,4,12,22,18,24,50,35,31,44,70,66,90}));
}
TEST(BinarySearchTrees,PostOrder){
    BinarySearchTree<int> sum;
    sum.insert(25);
    sum.insert(15);
    sum.insert(50);
    sum.insert(70);
    sum.insert(35);
    sum.insert(31);
    sum.insert(44);
    sum.insert(66);
    sum.insert(90);
    sum.insert(10);
    sum.insert(22);
    sum.insert(18);
    sum.insert(24);
    sum.insert(4);
    sum.insert(12);
    ASSERT_EQ(sum.postOrder(),vector<int> ({4,12,10,18,24,22,15,31,44,35,66,90,70,50,25}));
}
TEST(BinarySearchTrees,Sizing){
    BinarySearchTree<int> sum;
    sum.insert(10);
    sum.insert(17);
    sum.insert(25);
    sum.insert(15);
    ASSERT_EQ(sum.size(),4);
}
TEST(BinarySearchTrees,Includes){
    BinarySearchTree<int> sum;
    sum.insert(25);
    sum.insert(15);
    sum.insert(50);
    sum.insert(70);
    sum.insert(35);
    sum.insert(31);
    sum.insert(44);
    sum.insert(66);
    sum.insert(90);
    sum.insert(10);
    sum.insert(22);
    sum.insert(18);
    sum.insert(24);
    sum.insert(4);
    sum.insert(12);
    ASSERT_EQ(sum.includes(5),false);
}
TEST(BinarySearchTrees,removal){
    BinarySearchTree<int> sum;
    sum.insert(25);
    sum.insert(15);
    sum.insert(50);
    sum.insert(70);
    sum.insert(35);
    sum.insert(31);
    sum.insert(44);
    sum.insert(66);
    sum.insert(90);
    sum.insert(10);
    sum.insert(22);
    sum.insert(18);
    sum.insert(24);
    sum.insert(4);
    sum.insert(12);
    sum.remove(10);
    ASSERT_EQ(sum.includes(10),false);
}
//int main

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
