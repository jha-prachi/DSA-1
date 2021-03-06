#include<iostream>
#include<vector>
#include<list>
#include<queue>
using namespace std;
class edge{
    public:
    int v;
    int wt;
    edge(int v , int wt){
        this->v=v;
        this->wt=wt;
    }
    edge(){
        // default constructor
    }
};
// graph declaration outside of main
vector<vector<edge *>> graph;
// add edge function
void addedge(int u , int v , int wt){
    if(u<0 || v<0 || u>graph.size() || v>graph.size())
    return;

    graph[u].push_back(new edge(v , wt));
    graph[v].push_back(new edge(u , wt));
}
void display(vector<vector<edge *>> graph){
    for(int i =0;i<graph.size();i++){
        cout<<i<<"-> ";
        for(int j=0;j<graph[i].size();j++){
            int nbr = graph[i][j]->v;
            // -> its because we  have used heap and created edge on heap
            // . when created on stack
            cout<<graph[i][j]->v<<" @ "<<graph[i][j]->wt<<" , ";

        }
        cout<<endl;

    }
}
//==================================================================================================
class bfspair{
    public:
    int v;
    int wt;
    string psf;
    bfspair(int v , int wt , string psf){
        this->v=v;
        this->wt=wt;
        this->psf=psf;
    }
    bfspair(){

    }
};

int bfs(int src , vector<bool> isvisited){
    list<bfspair *> que;
    bfspair* src1 = new bfspair(src,0, src+" ");
    que.push_back(src1);
     int level=1;
        int size = que.size();
        bool iscompleted =false;
        int count =0;
    while(!que.empty()){
       
       
            bfspair* rpair = que.front();que.pop_front();
            if(isvisited[rpair->v]){
                count++;
                continue;
            }
            isvisited[rpair->v]=true;
            for(edge* e : graph[rpair->v]){

                if(!isvisited[e->v]){
                bfspair* nbr = new bfspair(rpair->v , rpair->wt,rpair->psf+to_string(rpair->v));
                que.push_back(nbr);
                }
            }
            
    }
    return count;
}
    void gcchelper(vector<bool>& isvisited){
    int cycle=0;
    int component =0;
    for(int i=0;i<7;i++){
        if(!isvisited[i]){
            cout<<i<<" ";
        cycle = bfs(i,isvisited);
        component++;
        // cout<<"cycle encointered on"<<i;
        }
        
    }
    cout<<"no of comp "<<component;
}

//=======bipartite graph=============================================================================
class partitepair{
    public:
    int node;
    int color;
        partitepair(int node , int color){
        this->node=node;
        this->color=color;
    }
    partitepair(){

    }
};
void bipartitegraph(int src,vector<int>& isvisited){
    // make a queue
    list<partitepair*> que;
    // add root
    // priority que will be type of partitite pair
    partitepair* root = new partitepair(src,0);
    que.push_back(root);
    while (!que.empty())
    {
        // partitepair* rpair = new partitepair(que.front()->node, que.front()->color);
        partitepair* rpair = que.front();
        que.pop_front();

        if(isvisited[rpair->node]!=-1   ){
            if(isvisited[rpair->node]==rpair->color){
                cout<<rpair->node<<" -> bipartite"<<endl;
            }
            else{
                cout<<rpair->node<<"-> not bipartite"<<endl;
            }
                 continue;
        }
        isvisited[rpair->node]=rpair->color;
        for(edge* e:graph[rpair->node]){
            if(isvisited[e->v]==-1){
                partitepair* nbr = new partitepair(e->v,(rpair->color+1)%2);
                que.push_back(nbr);
            }
        }

    }
    
}   
//=== dikstra ==============================================================================
vector<vector<edge *>> dgraph;
void addedge2(int u , int v , int wt){
    dgraph[u].push_back(new edge(v,wt));
}
class dpair{
    public:
    int vtx;
    int pvtx;
    int wt ;
    int wsf;
    string psf ="";
    dpair(int vtx , int pvtx , int wt , int wsf , string psf){
        this->vtx =vtx;
        this->pvtx =pvtx;
        this->wt=wt;
        this->wsf=wsf;
        this->psf =psf;
        
    }
    dpair(){

        }
        bool operator<(const dpair& o) const{
            return this->wsf>o.wsf;
        }
};
void dikshtra(int src , vector<bool> isvisited){
        priority_queue<dpair *> que;
        dpair* src1= new dpair(src,-1,0,0,"0");
        que.push(src1);
        int dest=6;
        while(!que.empty()){
            dpair* rpair = que.top();que.pop();
            if(isvisited[rpair->vtx]) continue;
            if(rpair->vtx==dest){
                cout<<rpair->psf<<" -> "<<rpair->wsf;
            }
            isvisited[rpair->vtx]=true;
            if(rpair->pvtx!=-1){
                addedge2(rpair->vtx , rpair->pvtx, rpair->wt);
            }
            for(edge* e : graph[rpair->vtx]){
                dpair* nbr = new dpair(e->v, rpair->vtx , e->wt , rpair->wsf+e->wt , rpair->psf+to_string(e->v));
                que.push(nbr);
            }
        }
}
//==== kruskal===============================================================================
vector<vector<edge *>> kgraph;

void addedge1(int u , int v , int wt){
    if(u<0 || v<0 || u>=kgraph.size() || v>=kgraph.size()) return;
    kgraph[u].push_back(new edge(v,wt));
}
class kpair{
    public:
    int vtx1;
    int vtx2;
    int wt;
    kpair(int vtx1 , int vtx2 , int wt){
        this->vtx1 = vtx1;
        this->vtx2 = vtx2;
        this->wt =wt;
    }
    kpair(){

    }
    bool operator<(const kpair& o)const{
        return this->wt>o.wt;
    }
    
};
// size vector
vector<int> sizearr(graph.size()+1,1);
vector<int> parentarr(graph.size()+1,1);
// helps in finding the parent and changing the parent
int findptx(int pt1){
        if(parentarr[pt1]!=pt1){
            parentarr[pt1] = findptx(parentarr[pt1]);
        }
        else{
            return pt1;
        }
        return parentarr[pt1];
}
void unionset(int parent1, int parent2, int wt){
    // int parent2 = findptx(vtx2);
    // int parent1 = findptx(vtx1);
    if(sizearr[parent1]<sizearr[parent2]){
        
        // set parent2 in vtx1
        // i just have to change for the parent node . child will automatically get converted afterwards
        parentarr[parent1]=parent2;
        addedge1(parent2,parent1, wt);
        sizearr[parent2]+=sizearr[parent1];

    }
    else{
            parentarr[parent2]=parent1;
            sizearr[parent1]+=sizearr[parent2];
            addedge1(parent2,parent1, wt);
    }
}
void kruskal(int src){
    // cout<<graph.size();
    priority_queue<kpair *>que;
    // kpair* root = new kpair(0,-1,src+"");
    for(int i=0;i<7;i++){
        for(int j =0;j<graph[i].size();j++){
            que.push(new kpair(i,graph[i][j]->v,graph[i][j]->wt));
        }
    }
    while(!que.empty()){
        kpair* rpair = que.top();
        que.pop();
        int parent1 = findptx(rpair->vtx1);
        int parent2 = findptx(rpair->vtx2);
        if(parent2!=parent1){
            unionset(parent1,parent2,rpair->wt);
        }
    }
    display(kgraph);
}
int main(){
     
    //need to intitalize the vector
    for(int i=0;i<7;i++){
        vector<edge *> ar;
        graph.push_back(ar);
        // vector<edge *> ar1;
        // dgraph.push_back(ar1);
        vector<edge *> ar2;
        kgraph.push_back(ar2);
    }
    addedge(0, 1, 10);
    addedge(1, 2, 10);
    addedge(2, 3, 40);
    addedge(0, 3, 10);
    addedge(3, 4, 2);
    addedge(4, 5, 2);
    addedge(5, 6, 8);
    addedge(4, 6, 3);

    // display();
    // vector<int> isvisited(7,-1);
    // bipartitegraph(0,isvisited);
    vector<bool> isvisited(7,false);
    // dikshtra(0,isvisited);
    // gcchelper(isvisited);
    for(int i=0;i<7;i++){
    parentarr[i]=i;
}
    kruskal(0);
    return 0;
}