#include<iostream>
#include<vector>
using namespace std;
//MY soln
int binarysearch(vector<int>& v,int data , int si,int ei){
    while(si<=ei){
        int mid=(si+ei)/2;
        
        if(data == v[mid]){
            if(mid-1>0 && v[mid-1]==v[mid]){
                ei = mid-1; // for lowerbound
                // for upper bound -> si = mid+1
            }
            else{
                return mid;
            }
        }
        else if(v[mid] > data){
            ei = mid-1;
            if(ei<0){
                return v[0];
            }
        }
        else{
            int temp=v.size();
            si= mid+1;
            if(si>=temp){
                return v[temp];
            }
        }
       
    }
     if(data-v[ei]>=v[si]-data){
            return si;
        }
        else{
            return ei;
        }
    return -1;
}

void input(vector<int>& v ,int n){
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
}
int main(){
    int n,data ;
    cin>>n;
    vector<int> v(n,0);
    input(v,n);
    cin>>data;
    cout<<binarysearch(v,data,0,n);

    return 0;
}