
//Alexandria Palm
//CS-300
//Project 2
#include <string>
#include <iostream>
#include <set>
#include <fstream>
#include <vector>
#include <sstream>
#include <exception>
using namespace std;

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    set<string> prerequisites;
    void display(){
        cerr << courseId << ", " << title;
        //if (!prerequisites.empty()){
        //    for (string const& str : prerequisites){
        //        cerr << ", " << str;
        //    }
        //}
        cerr << endl;
    }
};


// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course acourse) :
            Node() {
        course = acourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);
    void deleteNode(Node* node);
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //call deleteNode to make recursive calls on the left and right sides of each node
    deleteNode(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // make a call to recursively print the tree in ascending order
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // make a call to recursively print the tree in descending order
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    //make a call to recursively print the tree in pre order
    preOrder(root);
}



/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    if (!root){
        root = new Node(course);
    }
    else{
        addNode(root,course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
    removeNode(root,courseId);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* current = root;
    // keep looping downwards until bottom reached or matching courseId found
    while (current){
        // if match found, return current course
        if (current->course.courseId == courseId){
            return current->course;
        }
        // if course is smaller than current node then traverse left
        if (current->course.courseId > courseId){
            current = current->left;
        }
        // else larger so traverse right
        else{
            current=current->right;
        }
    }
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseId > course.courseId){
        // if no left node
        if (!node->left){
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else{
            addNode(node->left,course);
        }
    }
    // else
    else{
        // if no right node
        if (!node->right){
            // this node becomes right
            node->right = new Node(course);
        }
        else{
            addNode(node->right,course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {
      if (node){
        inOrder(node->left);//moves to left as far as can go
        node->course.display();//once we exit the the inOder calls the course gets printed
        inOrder(node->right);//then we call for the right nodes
      }
}
void BinarySearchTree::postOrder(Node* node) {
      if (node){
        postOrder(node->left);//then we call for the left nodes
        postOrder(node->right);//moves to right as far as can go
        node->course.display();//once we exit the the inOder calls the course gets printed
        
      }
}

void BinarySearchTree::preOrder(Node* node) {
    if (node){
        node->course.display();//display before order
        postOrder(node->left);//moves to left
        postOrder(node->right);//moves to right
      }
}

/**
 * Remove a course from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {
    // if node = nullptr return node
    if (!node){
        return node;
    }
    // (otherwise recurse down the left subtree)
    removeNode(node->left,courseId);
    // check for match and if so, remove left node using recursive call 
    if (node->course.courseId == courseId){
        return node;
    }
    // (otherwise recurse down the right subtree)
    removeNode(node->right,courseId);
    // check for match and if so, remove right node using recursive call
    if (node->course.courseId == courseId){
        return node;
    }
    // (otherwise no children so node is a leaf node)
    // if left node = nullptr && right node = nullptr delete node 
    if (!node->left && !node->right){
        delete node;
    }
    // (otherwise check one child to the left)
    removeNode(node->left,courseId);
    // if left node != nullptr && right node = nullptr delete node 
    if (node->left && !node->right){
        delete node;
    }
    // (otherwise check one child to the right)
    removeNode(node->right,courseId);
    // if left node = nullptr && right node != nullptr delete node
    if (!node->left && node->right){
        delete node;
    }
    // (otherwise more than one child so find the minimum)
    Node* temp = node->right;
    // create temp node to right
    // while left node is not nullptr keep moving temp left
    while (!node->left){
        temp=temp->left;
    }
    // make node course (right) equal to temp course (left)
    node->right->course = temp->course;
    // remove right node using recursive call
    removeNode(node->right,courseId);
    return node;
}

void BinarySearchTree::deleteNode(Node* node) {
    if (node){
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}




//https://stackoverflow.com/a/1120224
std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string>   result;
    std::string                line;
    std::getline(str,line);
    std::stringstream          lineStream(line);
    std::string                cell;

    while(std::getline(lineStream,cell, ','))
    {
        if (!cell.empty()){
            result.push_back(cell);
        }
    }
    return result;
}

//Load CSV Function
void loadCourses(string csvPath, BinarySearchTree &tree) {
    cerr << "Loading CSV file " << csvPath << endl;

    try {
        ifstream ifs (csvPath);
        while (!ifs.eof()){
            auto line = getNextLineAndSplitIntoTokens(ifs);
            if (line.size() < 2){
                throw runtime_error("line missing one or more elements");
            }
            Course course;
            course.courseId = line[0];
            course.title = line[1];
            for (int i = 2; i < line.size(); i++){
                if (!line[i].empty()){
                    course.prerequisites.insert(line[i]);
                }
            }
            tree.Insert(course);
        }
    } catch (exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    BinarySearchTree tree;
    int choice = 0;
    while (choice != 9) {
        cerr << "Menu:" << endl;
        cerr << "  1. Load Data Structure." << endl;
        cerr << "  2. Print Course List." << endl;
        cerr << "  3. Print Course." << endl;
        cerr << "  9. Exit" << endl;
        cerr << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:{
            cerr << "Enter name of file:" << endl;
            string name;
            cin >> name;
		    loadCourses(name,tree);
            break;
        }
        case 2:{
            // print list
            tree.InOrder();
            break;
        }
        case 3:{
            //call the print course function
            cerr << "please enter course ID:" << endl;
            string searchId;
            cin >> searchId;
            Course course = tree.Search(searchId);
            course.display();
            if (!course.prerequisites.empty()){
                for (string const& str : course.prerequisites){
                    cerr << str << endl;
                }
            }
            break;
        }
        //invalid input
        default:
            cerr << choice << " is not a valid option" << endl;
        }
    }

    cerr << "Good bye." << endl;

    return 0;
}
