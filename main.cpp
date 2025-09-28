#include "custom_classes.hpp"

int main(){
    string query, x, y;
    int n;
    str_map files;
    File *f;
    TreeNode *tnt;
    maxHeap<compare_time> mht;
    maxHeap<compare_versions> mhv;
    vector<File*> vf;
    while(true){
        cin>>query;
        if(query=="CREATE"){
            cin>>x;
            if(files.count(x)){
                cout<<"A file with that name already exists, use UPDATE to update its contents instead.\n";
                continue;
            }
            files[x] = new File();
            vf.push_back(files[x]);
            files[x]->name = x;
            files[x]->root = new TreeNode();
            files[x]->active_version = files[x]->root;
            files[x]->total_versions = 1;
            files[x]->version_map[0] = files[x]->root;
        } else if(query=="READ"){
            cin>>x;
            if(files.count(x)==0){
                cout<<"No such file exists, use CREATE to create a new file.\n";
                continue;
            }
            f = files[x];
            cout<<f->active_version->getContent()<<endl;
        } else if(query=="INSERT"){
            cin>>x;
            cin.ignore();
            getline(cin, y);
            // cin.ignore();
            if(files.count(x)==0){
                cout<<"No such file exists, use CREATE to create a new file.\n";
                continue;
            }
            f = files[x];
            f->modification_time = time(NULL);
            if(f->active_version->isSnapshot()){
                y = f->active_version->getContent() + y;
                f->version_map[f->total_versions] = new TreeNode(f->active_version, f->total_versions);
                f->active_version->addChild(f->version_map[f->total_versions]);
                f->active_version = f->version_map[f->total_versions];
                f->total_versions = f->total_versions + 1;
            }
            f->active_version->addContent(y);
        } else if(query=="UPDATE"){
            cin>>x;
            cin.ignore();
            getline(cin, y);
            // cin>>y;
            if(files.count(x)==0){
                cout<<"No such file exists, use CREATE to create a new file.\n";
                continue;
            }
            f = files[x];
            f->modification_time = time(NULL);
            if(f->active_version->isSnapshot()){
                f->version_map[f->total_versions] = new TreeNode(f->active_version, f->total_versions);
                f->active_version->addChild(f->version_map[f->total_versions]);
                f->active_version = f->version_map[f->total_versions];
                f->total_versions = f->total_versions + 1;
            }
            f->active_version->setContent(y);
        } else if(query=="SNAPSHOT"){
            cin>>x;
            cin.ignore();
            getline(cin, y);
            if(files.count(x)==0){
                cout<<"No such file exists, use CREATE to create a new file.\n";
                continue;
            }
            f = files[x];
            if(f->active_version->isSnapshot()){
                cout<<"Already a snapshot!!"<<endl;
                continue;
            }
            f->active_version->snapshot(y);
            
        } else if(query=="ROLLBACK"){
            getline(cin, y);
            stringstream sss(y);
            sss>>x;
            if(sss>>n){
                if(n<0){
                    cout<<"Invalid version id!"<<endl;
                    continue;
                }
                // Good!
            } else n=-1;
            if(files.count(x)==0){
                cout<<"No such file exists, use CREATE to create a new file.\n";
                continue;
            }
            f = files[x];
            if(n!=-1){
                if(!f->version_map.count(n)){
                    cout<<"No such version id exists for this filename\n";
                    continue;
                }
                f->active_version = f->version_map[n];
            } else{
                if(!f->active_version->getParent()){
                    cout<<"Already at original version!\n";
                    continue;
                }
                f->active_version = f->active_version->getParent();
            }
            
        } else if(query=="HISTORY"){
            cin>>x;
            if(files.count(x)==0){
                cout<<"No such file exists, use CREATE to create a new file.\n";
                continue;
            }
            f = files[x];
            tnt = f->active_version;
            y = tnt->get_info() + "\n";
            while(tnt->getParent()){
                tnt = tnt->getParent();
                y = tnt->get_info() + "\n" + y;
            }
            cout<<y;
        } else if(query=="RECENT_FILES"){
            mht.buildHeap(vf);
            cin>>n;
            for(int ij=0; ij<n; ij++){
                if(mht.empty()){
                    cout<<"No more files!!"<<endl;
                    break;
                }
                f=mht.deleteRoot();
                y=f->name;
                y += " ";
                y.append(ctime(&f->modification_time));
                cout<<y;
            }
        } else if(query=="BIGGEST_TREES"){
            mhv.buildHeap(vf);
            cin>>n;
            for(int ij=0; ij<n; ij++){
                if(mhv.empty()){
                    cout<<"No more files!!"<<endl;
                    break;
                }
                f=mhv.deleteRoot();
                cout<<f->name<<" "<<f->total_versions<<endl;
            }
        } else if(query=="EXIT"){
            //cleanup
            for(File* tmpfl : vf){
                delete tmpfl;
            }
            break;
        } else {
            cout<<"Invalid command!"<<endl;
        }
    }
    return 0;
}