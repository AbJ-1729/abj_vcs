#ifndef CUSTOM_CLASSES
#define CUSTOM_CLASSES
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class TreeNode{
    int version_id;
    string content;
    string message; // Empty if not a snapshot
    time_t created_timestamp;
    time_t snapshot_timestamp; // Null if not a snapshot
    TreeNode* parent;
    vector <TreeNode*> children;
public:
    TreeNode();
    TreeNode(TreeNode* parent, int id);
    string getContent();
    void addContent(string additions);
    void setContent(string content);
    bool isSnapshot();
    void addChild(TreeNode* child);
    ~TreeNode();
    void snapshot(string msg);
    TreeNode* getParent();
    string get_info();
};

class int_map{
    vector<TreeNode*> v;
public:
    int_map();
    ~int_map();
    int count(int x);
    TreeNode*& operator[](int t1);
};

struct File{
    string name;
    TreeNode* root; // Your implementation of the tree
    TreeNode* active_version;
    int_map version_map; // Your implementation of the HashMap
    int total_versions;
    time_t modification_time;
    File();
    ~File();
};

template<typename comp_logic>
class maxHeap{
    comp_logic comp;
    vector<File*> rawData;
    int n, tmp, x, y;
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void heapify(int i);
public:
    maxHeap();
    maxHeap(vector<File*> v);
    ~maxHeap();
    void buildHeap(vector<File*> v);
    void insert(File* f);
    File* deleteRoot();
    bool empty();
};

template<typename comp_logic> int maxHeap<comp_logic>::parent(int i){
    if(i==0) return i;
    return (i-1)/2;
}
template<typename comp_logic> int maxHeap<comp_logic>::leftChild(int i){
    if(2*i+1>=this->rawData.size()) return i;
    return (2*i+1);
}
template<typename comp_logic> int maxHeap<comp_logic>::rightChild(int i){
    if(2*i+2>=this->rawData.size()) return i;
    return (2*i+2);
}

template<typename comp_logic> void maxHeap<comp_logic>::heapify(int i){
    tmp=i; x=i;
    while(true){
        if(this->comp(this->rawData[leftChild(tmp)], this->rawData[x])){
            x = leftChild(tmp);
        }
        if(this->comp(this->rawData[rightChild(tmp)], this->rawData[x])){
            x = rightChild(tmp);
        }
        if(x==tmp) break;
        swap(this->rawData[tmp], this->rawData[x]);
        tmp=x;
    }
}

template<typename comp_logic> maxHeap<comp_logic>::maxHeap(){
    //Already a vector is initialized
}

template<typename comp_logic> maxHeap<comp_logic>::maxHeap(vector<File*> v){
    buildHeap(v);
}

template<typename comp_logic> maxHeap<comp_logic>::~maxHeap(){
    //Everything assigned on stack memory, thus gets cleared itself.
}

template<typename comp_logic> void maxHeap<comp_logic>::buildHeap(vector<File*> v){
    this->rawData = v;
    for(int i=v.size()-1; i>=0; i--) heapify(i);
}

template<typename comp_logic> void maxHeap<comp_logic>::insert(File* f){
    rawData.push_back(f);
    // this->rawData[n++] = f;
    tmp=rawData.size()-1;
    // n++;
    while(this->comp(this->rawData[tmp],this->rawData[parent(tmp)])){
        swap(this->rawData[tmp], this->rawData[parent(tmp)]);
        tmp=parent(tmp);
    }
}

template<typename comp_logic> File* maxHeap<comp_logic>::deleteRoot(){
    if (this->empty()) return nullptr;
    // n--;
    File* ans=rawData[0];
    swap(this->rawData[0], this->rawData[this->rawData.size()-1]);
    // File* ans=rawData[n-1];
    rawData.pop_back();
    if(this->empty()) return ans;
    tmp=0; x=0;
    while(true){
        if(this->comp(this->rawData[leftChild(tmp)], this->rawData[x])){
            x = leftChild(tmp);
        }
        if(this->comp(this->rawData[rightChild(tmp)], this->rawData[x])){
            x = rightChild(tmp);
        }
        swap(this->rawData[tmp], this->rawData[x]);
        if(x==tmp) break;
        tmp=x;
    }
    return ans;
}

template<typename comp_logic> bool maxHeap<comp_logic>::empty(){
    return rawData.empty();
}

struct compare_time{
    bool operator()(const File* a, const File* b);
};

// Comparator for last modified
struct compare_versions{
    bool operator()(const File* a, const File* b);
};


//TODO:Implement HashMap using vector of vectors
// template<typename T1, typename T2>
class str_map{
    vector<vector<pair<string, File*>>> v;
public:
    str_map();
    ~str_map();
    int count(string x);
    File*& operator[](string t1);
};

// class int_map{
//     vector<TreeNode*> v;
// public:
//     int_map();
//     ~int_map();
//     int count(int x);
//     TreeNode*& operator[](int t1);
// };

#endif