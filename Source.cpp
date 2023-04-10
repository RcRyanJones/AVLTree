#include <string>
using namespace std;
#include <iostream>
#include <cctype>
#include <stdio.h>
#include <string.h>
#include <queue>
int counter = 0;

class Node {
public:
    int IDMem; //to show members of class
    string nameMem;
    //Node* newNode;
    Node* left;
    Node* right;
    Node(int x, string y) : IDMem(x), nameMem(y), left(nullptr), right(nullptr) {}
};


int unique(int ID, Node* nodey) {  
    if (counter == 0) {
        return 1;
    }
    if (nodey == nullptr) {
        return 1;
    }
    if (nodey->left != nullptr) {
        if (nodey->left->IDMem == ID) {
            return -1;
        }
        unique(ID, nodey->left);
    }
    if (nodey->right != nullptr) {
        if (nodey->right->IDMem == ID) {
            return -1;
        }
        unique(ID, nodey->right);
    }
    else {
        return 1;
    }
}

int leftHeight = 0;
int rightHeight = 0;
int height(Node* nodey) {
    int high = 0;
    if (nodey != nullptr) {
        leftHeight = height(nodey->left);
        leftHeight++;
        rightHeight = height(nodey->right);
        rightHeight++;
        int max_height = max(leftHeight, rightHeight);
        high = max_height;
    }
    leftHeight = 0;
    rightHeight = 0;
    return high;
}
int difference(Node* nodey) {
    if (nodey != nullptr) {
        int leftHeight = 0;
        int rightHeight = 0;
        if (nodey->left != nullptr) {
            leftHeight = height(nodey->left);
        }
        if (nodey->right != nullptr) {
            rightHeight = height(nodey->right);
        }
        int diff = leftHeight - rightHeight;
        return diff;
    }
    else {
        return 0;
    }
}


struct Node* minimumValue(struct Node* nodey)
{
    struct Node* curr = nodey;

    while (curr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}
//finds minimum value by traversing left side
Node* leftDoubleRotation(Node* nodey) {
    Node* grandchild = nodey->left->right;
    Node* newParent = nodey->left;
    newParent->right = nodey;
    nodey->left = grandchild;
    return newParent;
} //rotates left twice depending on order specs


Node* rightDoubleRotation(Node* nodey) {
    //if 
    Node* grandchild = nodey->right->left;
    Node* newParent = nodey->right;
    newParent->left = nodey; 
    nodey->right = grandchild;
    return newParent;
}


Node* rightLeftRotation(Node* nodey) {
    Node* temp;
    temp = nodey->right; //according to slides left right and right left are right and then left performed
    nodey->right = leftDoubleRotation(temp);
    return rightDoubleRotation(nodey);
}


Node* leftRightRotation(Node* nodey) {
    Node* temp;
    temp = nodey->left; //according to slides left right and right left are right and then left performed
    nodey->left = rightDoubleRotation(temp);
    return leftDoubleRotation(nodey);
}



Node* order(Node* root) {//takes in root from insert and remove and gives new root
    Node* temp = root;
    int orderStat = 0;
    if (orderStat > 1) {
        if (difference(root->left) > 0) {
            temp = leftDoubleRotation(root);
        }
        else {
            temp = leftRightRotation(root);
        }
    }
    else if (orderStat < -1) { //needs rightrot
        if (difference(root->right) > 0) {
            temp = rightLeftRotation(root);
        }
        else {
            temp = rightDoubleRotation(root);
        }
    }
    return temp;
}

struct Node* remove(int ID, Node* root) { //

    if (root == nullptr) {
        return root;
    }
    else if (ID < root->IDMem) {
        root->left = remove(ID, root->left);
    } //move left on tree
    else if (ID > root->IDMem) {

        root->right = remove(ID, root->right);
    } 
    else { 
        
        if (root->left == nullptr && root->right == nullptr) {
            struct Node* temp = root->right;
            
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        else if (root->left == nullptr) {
            struct Node* temp = root->right;
            delete root;
            cout << "successful" << endl;
            return temp;
        }
        else if (root->right == nullptr) {
            struct Node* temp = root->left;
            delete root;
            cout << "successful" << endl;
            return temp;

        }
        struct Node* temp = minimumValue(root->right);
        root->IDMem = temp->IDMem;
        root->nameMem = temp->nameMem;
        root->right = remove(temp->IDMem, root->right);
    }
    return root;
}



void search(int ID, Node* root) { 
    if (root->IDMem == ID) {
        for (int i = 0; i < root->nameMem.length(); i++) {
            cout << root->nameMem.at(i);
        }
        cout << endl;
        return;
    }

   

    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }
    if (root->left != nullptr) {
        if (root->IDMem == ID) {
            for (int i = 0; i < root->nameMem.length(); i++) {
                cout << root->nameMem.at(i);
            }
            cout << endl;
            return;
        }
        if (root->left->IDMem == ID) {
            for (int i = 0; i < root->left->nameMem.length(); i++) {
                cout << root->left->nameMem.at(i);
            }
            cout << endl;
            return;
        }
        search(ID, root->left);
        return;
    }

    if (root->right != nullptr) {
        if (root->IDMem == ID) {
            for (int i = 0; i < root->nameMem.length(); i++) {
                cout << root->nameMem.at(i);
            }
            cout << endl;
            return;
        }
        if (root->right->IDMem == ID) {
            for (int i = 0; i < root->right->nameMem.length(); i++) {
                cout << root->right->nameMem.at(i);

            }
            cout << endl;
            return;
        }
        search(ID, root->right);
        return;
    }
    cout << "unsuccessful" << endl;
    return;
}


int searchNameDuplicatecount = 0;
Node* storage;

void search(string name, Node* root) { 
    if (searchNameDuplicatecount == 0) { 
        storage->IDMem == 95159519;
    }
    if (searchNameDuplicatecount > 0) {
        if (root->left != nullptr) {
            root = root->left;
            //cout << "here";
        }
        else if (root->right != nullptr) {
            root = root->right;
        }
    }

    if (root != nullptr) {
        if (root->nameMem.compare(name) == 0) { 



            if (storage == nullptr || root->IDMem != storage->IDMem) {

                cout << root->IDMem << endl;
                storage = root;
                searchNameDuplicatecount++;
                search(name, root);//
                return;
            }
            return;
        }
        if (root->right != nullptr) {
            if (root->nameMem.compare(name) == 0) {

                if (storage == nullptr || root->IDMem != storage->IDMem) {

                    cout << root->IDMem << endl;
                    storage = root;

                    searchNameDuplicatecount++;
                    search(name, root);//
                    return;
                }
                return;
            }
            if (root->right->nameMem.compare(name) == 0) {

                if (storage == nullptr || root->IDMem != storage->IDMem) {
                    cout << root->right->IDMem << endl;
                    storage = root;

                    searchNameDuplicatecount++;
                    search(name, root);//
                    return;
                }
                return;
            }
            search(name, root->right);
            return;
        }

        if (root->left != nullptr) {
            if (root->nameMem.compare(name) == 0) {

                if (storage == nullptr || root->IDMem != storage->IDMem) {
                    cout << root->IDMem << endl;
                    storage = root;

                    searchNameDuplicatecount++;
                    search(name, root);//
                    return;
                }
                return;
            }

            search(name, root->left);
            return;
        }
    }
    if (searchNameDuplicatecount == 0) {
        cout << "unsuccessful" << endl;
    }
    return;
}


Node* insert(string name, int ID, Node* root) {
 
    if (root != nullptr && root->IDMem == 0 && root->nameMem == " " && counter > 0) {
        remove(root->IDMem, root);
    }

    if (root == nullptr) {
        cout << "successful" << endl;
        return new Node(ID, name);
    }
    else if (root->IDMem < ID) {
        root->right = insert(name, ID, root->right);//, root->right);
   
    }
    else {
        root->left = insert(name, ID, root->left);//, 
    }

    return root;
}
int commaCount = 0;
void printPreorder(Node* nodey)
{
    if (nodey == nullptr) {
        return;
    }
    if (commaCount != 0 && commaCount != counter && to_string(nodey->IDMem).length() == 8) {

        cout << ", ";

    }
    if (commaCount == 0 || to_string(nodey->IDMem).length() == 8) {
        commaCount++;
    }
    if (nodey->left != nullptr) {
        cout << nodey->left->nameMem;

        printPreorder(nodey->left);
    }
    if (nodey->right != nullptr) {
        cout << nodey->right->nameMem;
        printPreorder(nodey->right);
        // cout << ",";
    }
}
int commaIn = 0;
void printInorder(Node* nodey) // fixed
{
    if (nodey == nullptr) {
        return;
    }
    if (nodey != nullptr && nodey->left != nullptr && to_string(nodey->IDMem).length() == 8) {
        printInorder(nodey->left);
    }
    if (nodey->nameMem != "" && to_string(nodey->IDMem).length() == 8) {
        for (int i = 0; i < nodey->nameMem.length(); i++) {
            cout << nodey->nameMem.at(i);
        }
        // cout << ",";
    }
    if (commaIn != 0 && commaIn != counter && to_string(nodey->IDMem).length() == 8) {

        cout << ", ";

    }
    if (commaIn == 0 || to_string(nodey->IDMem).length() == 8) {
        commaIn++;
    }

    if (nodey->right != nullptr) {
        printInorder(nodey->right);
    }
}
int commaPost = 0;
void printPostorder(Node* nodey) //fix
{
    if (nodey == nullptr)
        return;

    printPostorder(nodey->left);
    printPostorder(nodey->right);
    if (commaPost != 0 && commaPost != counter && to_string(nodey->IDMem).length() == 8) {

        cout << ", ";

    }
    if (commaPost == 0 || to_string(nodey->IDMem).length() == 8) {
        commaPost++;
    }
    if (nodey->nameMem != "") {
        for (int i = 0; i < nodey->nameMem.length(); i++) {
            cout << nodey->nameMem.at(i);
        }
        //cout << ",";
    }

}
int heightRight = 0;
int heightLeft = 0;
int heightLoc = 0;
int printLevelCount(Node* root) {
    int deep = 0;
    queue<Node*> nodeQ;
    nodeQ.push(root);
    nodeQ.push(nullptr);
    while (!nodeQ.empty()) {
        Node* temp = nodeQ.front();
        nodeQ.pop();
        if (temp == nullptr) {
            deep++;
        }
        if (temp != nullptr) {
            if (temp->left) {
                nodeQ.push(temp->left);
            }
            if (temp->right) {
                nodeQ.push(temp->right);
            }
        }
        else if (!nodeQ.empty()) {
            nodeQ.push(nullptr);
        }
    }

    return deep;
}

Node* findInorder(Node* nodey) // fixed
{
    if (nodey == nullptr)
        return nullptr;
    findInorder(nodey->left);
    findInorder(nodey->right);
    return nodey;

}


void removeInorder(int numNodes, Node* root) {
    for (int i = 0; i < numNodes; i++) {
        if (root == nullptr) {
            cout << "unsuccessful" << endl;
            return;
        }
        else {
            if (findInorder(root) != nullptr) {
                root = findInorder(root->right);
            }
        }
    }

    remove(root->IDMem, root);

}


int main()
{
    Node* root;
    int ID = 0;
    string namestr = "";
    root = new Node(ID, namestr);
    int repeat = 0;
    string commands;
    string name;
    cin >> repeat;
    for (int i = 0; i < repeat; i++) {
        cin >> commands;
        if (commands == "insert") {
            name = "";
            namestr = "";
            getline(cin, namestr);                   
     
            string IDstr;
            for (int j = 0; j < 8; j++) {
                IDstr.push_back(namestr.at(namestr.length() - 8 + j));
            }
            
            if (isalpha(IDstr.at(4))) {
                cout << "unsuccessful" << endl;
            } else{
            int ID = stoi(IDstr);
            int length = to_string(ID).length();
            int tester = 0;
            for (int i = 2; i < namestr.length() - 10; i++) {
                name.push_back(namestr.at(i));
                if (!isalpha(namestr.at(i)) && (namestr.at(i) != ' ')) { 
                    tester = -1;

                }
            }
            if (IDstr.length() != 8) {
                
                cout << "unsuccessful" << endl; 
            }
            else if (tester == -1) {
                //cout <<
                cout << "unsuccessful" << endl;
            }
            else {
                if (unique(ID, root) == 1) {
                    insert(name, ID, root);
                    root = order(root);
                    counter++;
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            }
        }
        if (commands == "printInorder") {
            commaIn = 0;
            printInorder(root);
            cout << endl;
        }
        if (commands == "printPostorder") {
            commaPost = 0;
            printPostorder(root);
            cout << endl;

        }
        if (commands == "printPreorder") {
            commaCount = 0;
            printPreorder(root);
            cout << endl;

        }
        if (commands == "printLevelCount") {

            cout << printLevelCount(root) - 2;
            cout << endl;

        }
        if (commands == "search") {
            string searchID;
            string insertedID;
            getline(cin, searchID);
            int litmus = 0;
            for (int i = 2; i < searchID.length() - 1; i++) {
                insertedID.push_back(searchID.at(i));
                if (!isalpha(searchID.at(i)) && (searchID.at(i) != ' ')) {
                    litmus = -1;
                }
            }
            if (litmus == -1) {

                search(stoi(searchID), root);
            }
            else {
                search(insertedID, root);
            }
        }
        if (commands == "remove") {
            cin >> ID;
            remove(ID, root);
            counter--;
        }
        if (commands == "removeInorder") {
            int numNodes;
            cin >> numNodes;
            removeInorder(numNodes, root);
            counter--;

        }
        if (root->nameMem == " " && root->IDMem == 0) {
            remove(root->IDMem, root);
            root = root->right;

        }
    }
}