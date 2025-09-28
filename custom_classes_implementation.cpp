#include "custom_classes.hpp"

File::File(){
    this->modification_time=time(NULL);
}

File::~File(){
    delete root;
}

TreeNode::TreeNode(){
    this->created_timestamp = time(NULL);
    this->snapshot_timestamp = time(NULL);
    message="Initial Version";
    this->version_id = 0;
    content="";
    this->parent=nullptr;
}

TreeNode::TreeNode(TreeNode* parent, int id){
    this->created_timestamp = time(NULL);
    this->snapshot_timestamp = 0;
    message="";
    this->version_id = id;
    content="";
    this->parent=parent;
}

TreeNode::~TreeNode(){
    for(TreeNode *tn : children){
        delete tn;
    }
}

string TreeNode::getContent(){
    return this->content;
}

void TreeNode::addContent(string additions){
    this->content += additions;
}

void TreeNode::setContent(string content){
    this->content = content;
}

bool TreeNode::isSnapshot(){
    return this->snapshot_timestamp!=0;
}

void TreeNode::addChild(TreeNode *child){
    this->children.push_back(child);
}

void TreeNode::snapshot(string msg){
    this->message = msg;
    this->snapshot_timestamp = time(NULL);
}

TreeNode *TreeNode::getParent(){
    return this->parent;
}

string TreeNode::get_info(){
    string anss;
    anss = "ID : " + to_string(this->version_id) + " | Timestamp: ";
    if(!this->snapshot_timestamp==0){
        anss.append(ctime(&this->snapshot_timestamp)); //Human readable timestamp
        anss.pop_back();
        anss += " | Message : " + this->message;
    } else {
        anss += "<not a snapshot>";
    }
    return anss;
}


bool compare_time::operator()(const File* a, const File* b){
    return a->modification_time > b->modification_time;   // bigger size = higher priority
}

bool compare_versions::operator()(const File* a, const File* b){
    return a->total_versions > b->total_versions; // recent = higher priority
}

int stringhasher(string s){
    int p1=37;
    int p2=10007;
    long long int ans=0;
    int x;
    for(char i : s){
        x=i;
        ans *= p1;
        ans += x;
        ans %= p2;
    }
    return ans;
}

str_map::str_map(){
    v.resize(10007);
}

str_map::~str_map(){
    //Nothing to do
}

int str_map::count(string x){
    int mhash=stringhasher(x);
    for(pair<string, File*> &p : v[mhash]){
        if(p.first==x) return 1;
    }
    return 0;
}

File*& str_map::operator[](string t1){
    int mhash=stringhasher(t1);
    for(pair<string, File*> &p : v[mhash]){
        if(p.first==t1) return p.second;
    }
    v[mhash].push_back({t1, nullptr});
    return v[mhash].back().second;
}

int_map::int_map(){
    v.resize(1000000);
    for(int ti=0; ti<1000000; ti++) v[ti]=nullptr;
}

int_map::~int_map(){
    //Nothing to do
}

int int_map::count(int x){
    int mhash=x;
    if(v[mhash]!=nullptr) return 1;
    return 0;
}

TreeNode*& int_map::operator[](int t1){
    int mhash=t1;
    return v[mhash];
}