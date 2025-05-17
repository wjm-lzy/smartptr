#include <bits/stdc++.h>
using namespace  std;

class Solution {
public:
    vector<int> spiralArray(vector<vector<int>>& array) {
        if(array.size()==0||array[0].size()==0){
            return {};
        }
        vector<int> ans;
        int l=0,r=array[0].size()-1,u=0,lo = array.size()-1;
        while(l<=r&&u<=lo){
            int i=l,j=u;
            for(;i<r;i++){
                ans.push_back(array[j][i]);
            }
            for(;j<lo;j++){
                ans.push_back(array[j][i]);
            }
            for(;i>l;i--){
                ans.push_back(array[j][i]);
            }
            for(;j>i;j--){
                ans.push_back(array[j][i]);
            }
            l++;
            r--;
            u++;
            lo--;
        }
        return ans;

    }
};