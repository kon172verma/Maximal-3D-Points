#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

struct node{
    struct node* left;
    int index;
    int x;
    int y;
    int z;
    struct node*right;
};

class AVLTree{

    public:
        node* ROOT;
        vector<int> arr;
        int Y,Z;

        AVLTree(){
            ROOT=NULL;
        }
        void insert(int index, int x, int y, int z);
        node* Insert(node* root, int index, int x, int y, int z);

        void display();
        void Display(node* root, int i);

        void inorder();
        void Inorder(node* root);

        int height();
        int Height(node* root);

        node* balance(node* root);
        node* LLrotate(node* root);
        node* LRrotate(node* root);
        node* RLrotate(node* root);
        node* RRrotate(node* root);

        void delete_node(int val);
        node* Delete_node(node* root, int val);

        int closest_y_greater(int val);
        void y_inorder(node* root);

        int closest_z_greater(int val);
        void z_inorder(node* root);

        int find_z(int val);
        void Find_z(node* root, int val);

        int find_y(int val);
        void Find_y(node* root, int val);

        int find_max_y();
        int find_max_z();

        void delete_range(int lower, int higher);
};

//function to delete all the points from the tree that has a y value between the lower and higher.
void AVLTree :: delete_range(int lower, int higher){
    vector <int> temp;
    arr.clear();
    y_inorder(ROOT);
    for(int i=0;i<arr.size();i++){
        if(arr[i]>lower && arr[i]<higher){
            temp.push_back(arr[i]);
        }
    }
    for(int i=0;i<temp.size();i++)
        delete_node(temp[i]);
}

//function to find the maximum y value present in the tree.
int AVLTree :: find_max_y(){
    if(ROOT == NULL)
        return -1;
    node* temp = ROOT;
    while(temp->right)
        temp = temp->right;
    return temp->y;
}
//function to find the maximum z value present in the tree.
int AVLTree :: find_max_z(){
    if(ROOT == NULL)
        return -1;
    node* temp = ROOT;
    while(temp->left)
        temp = temp->left;
    return temp->z;
}

// function to find the z value of a point from its y value.
int AVLTree :: find_z(int val){
    Find_z(ROOT, val);
    return Z;
}
void AVLTree :: Find_z(node* root, int val){
    if(root->y == val){
        Z = root->z;
        return;
    }
    else if(root->y > val)
        Find_z(root->left, val);
    else if(root->y < val)
        Find_z(root->right, val);
}

// function to find the y value of a point from its z value.
int AVLTree :: find_y(int val){
    Find_y(ROOT, val);
    return Y;
}
void AVLTree :: Find_y(node*root, int val){
    if(root->z==val){
        Y = root->y;
        return;
    }
    else if(root->z < val)
        Find_y(root->left,val);
    else if(root->z > val)
        Find_y(root->right,val);
}

// inorder traversal on the basis of the y axis.
void AVLTree :: y_inorder(node*root){
    if(root){
        y_inorder(root->left);
        arr.push_back(root->y);
        y_inorder(root->right);
    }
}
// function to find the successor z value of a given value.
int AVLTree :: closest_y_greater(int val){
    arr.clear();
    y_inorder(ROOT);
    for(int i=0;i<arr.size();i++){
        if(arr[i]<val){}
        else
            return arr[i];
    }
    return -1;
}

// inorder traversal on the basis of the z axis.
void AVLTree :: z_inorder(node*root){
    if(root){
        z_inorder(root->left);
        arr.push_back(root->z);
        z_inorder(root->right);
    }
}
// function to find the successor z value of a given value.
int AVLTree :: closest_z_greater(int val){
    arr.clear();
    z_inorder(ROOT);
    for(int i=arr.size()-1;i>=0;i--){
        if(arr[i]<val){}
        else
            return arr[i];
    }
    return -1;
}

//function to delete a node.
void AVLTree :: delete_node(int val){
    ROOT = Delete_node(ROOT,val);
}
node* AVLTree :: Delete_node(node* root, int val){
    if(root){
        if(val<root->y)
            root->left = Delete_node(root->left, val);
        else
            root->right = Delete_node(root->right, val);

        if(root->y==val){
            if(root->left==NULL && root->right==NULL){
                free(root);
                return NULL;
            }
            else if(root->left==NULL){
                node* temp = root->right;
                free(root);
                return temp;
            }
            else if(root->right==NULL){
                node* temp = root->left;
                free(root);
                return temp;
            }
            else{
                node* temp = root->left;
                node* prev = NULL;
                while(temp->right){
                    prev = temp;
                    temp=temp->right;
                }
                int t_index = temp->index;
                temp->index = root->index;
                root->index = t_index;

                int t_x = temp->x;
                temp->x = root->x;
                root->x = t_x;

                int t_y = temp->y;
                temp->y = root->y;
                root->y = t_y;

                int t_z = temp->z;
                temp->z = root->z;
                root->z = t_z;

                if(prev==NULL){
                    root->left = temp->left;
                    free(temp);
                }
                else{
                    prev->right = temp->left;
                    free(temp);
                }
            }
        }
        root = balance(root);
    }
    return root;
}

//function to implement the LL rotation.
node* AVLTree :: LLrotate(node* root){
    node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}
//function to implement the RR rotation.
node* AVLTree :: RRrotate(node* root){
    node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}
//function to implement the LR rotation.
node* AVLTree :: LRrotate(node* root){
    node* temp = root->left;
    root->left = RRrotate(temp);
    return LLrotate(root);
}
//function to implement the RL rotation.
node* AVLTree :: RLrotate(node* root){
    node* temp = root->right;
    root->right = LLrotate(temp);
    return RRrotate(root);
}

//function to balance the AVLTree.
node* AVLTree :: balance(node* root){

    int left = Height(root->left);
    int right = Height(root->right);
    int bf = left-right;
    //if the tree is balanced.
    if(bf==0 || bf==1 || bf==-1)
        return root;
    //if the tree is not balanced because of the left side.
    else if(bf>1){
        if(Height(root->left->left)-Height(root->left->right)>0)
            root = LLrotate(root);
        else
            root = LRrotate(root);
    }
    //if the tree is not balanced because of the right side.
    else if(bf<-1){
        if(Height(root->right->left)-Height(root->right->right)>0)
            root = RLrotate(root);
        else
            root = RRrotate(root);
    }
    return root;
}

//Implementation of the height function, height of the root is 1.
int AVLTree :: height(){
    return Height(ROOT);
}
int AVLTree :: Height(node* root){
    if(!root)
        return 0;
    int left = Height(root->left);
    int right = Height(root->right);
    if(left>=right)
        return left+1;
    else if(right>left)
        return right+1;
}

//Implementation of the inorder traversal function.
void AVLTree :: inorder(){
    Inorder(ROOT);
}
void AVLTree :: Inorder(node* root){
    if(root){
        Inorder(root->left);
        cout<<root->index<<" "<<root->x<<" "<<root->y<<" "<<root->z<<"\t";
        Inorder(root->right);
    }
}

//Implementation of a function that displays the AVL tree.
void AVLTree :: display(){
    Display(ROOT,0);
}
void AVLTree :: Display(node* root, int i){
    if(root){
        Display(root->right,i+1);
        for(int k=0;k<i;k++)
            cout<<"\t";
        cout<<root->index<<" "<<root->x<<" "<<root->y<<" "<<root->z<<endl;
        Display(root->left,i+1);
    }
}

//Implementation of the insert function.
void AVLTree :: insert(int index, int x, int y, int z){
    ROOT = Insert(ROOT, index, x, y, z);
}
node* AVLTree :: Insert(node *root, int index, int x, int y, int z){

    //case 1: if the tree is empty.
    if(root==NULL){
        node* temp;
        temp = new node;
        temp->left = NULL;
        temp->index = index;
        temp->x = x;
        temp->y = y;
        temp->z = z;
        temp->right = NULL;
        return temp;
    }
    //finding the location where we need to insert the new element.
    else if(y < root->y){
        root->left = Insert(root->left, index, x, y, z);
        root = balance(root);
    }
    else if(root->y < y){
        root->right = Insert(root->right, index, x, y, z);
        root = balance(root);
    }
    return root;
}

/*
int main(){

    int option, index, x, y, z;
    int value;
    AVLTree tree;
    while(1){
        cout<<"choose an option : \n1.insert \n2.display \n3.inorder\n4.height\n5.delete"<<endl;
        cout<<"6. closest_y_greater\n7. closest_z_greater\n8. find_z\n9. find_y\n10.find_max_y\n11.find_max_z"<<endl;
        cin>>option;
        switch(option){
            case 1:
                cin>>index>>x>>y>>z;
                tree.insert(index,x,y,z);
                break;
            case 2:
                cout<<endl;
                tree.display();
                cout<<endl;
                break;
            case 3:
                tree.inorder();
                cout<<endl;
                break;
            case 4:
                cout<<"height : "<<tree.height()<<endl;
                break;
            case 5:
                cin>>y;
                tree.delete_node(y);
                break;
            case 6:
                cin>>value;
                cout<<tree.closest_y_greater(value)<<endl;
                break;
            case 7:
                cin>>value;
                cout<<tree.closest_z_greater(value)<<endl;
                break;
            case 8:
                cin>>value;
                cout<<tree.find_z(value);
                break;
            case 9:
                cin>>value;
                cout<<tree.find_y(value);
                break;
            case 10:
                cout<<tree.find_max_y();
                break;
            case 11:
                cout<<tree.find_max_z();
                break;
            default:
                return 1;
        }
    }

    return 0;
}
*/
