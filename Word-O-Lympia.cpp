#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class TrieNode{

    public:

    TrieNode*links[26];
    bool isEnd=false;
};

class Trie{

    public:
    TrieNode*root;

    Trie(){
        root=new TrieNode();
    }
    
    void insert(string word){

        TrieNode*curr=root;
        for(int i=0;i<word.length();i++){
            int ind=word[i]-'a';

            if(!curr->links[ind]){
                curr->links[ind]=new TrieNode();
            }

            curr=curr->links[ind];
        }
        curr->isEnd=true;

    }
};

void dfs(vector<vector<char>>&grid,vector<vector<int>>&visited,int row,int col,TrieNode*curr,string&word){
    
    word+=grid[row][col];

    if(curr->isEnd){
        cout<<word<<endl;
    }
    
    visited[row][col]=1;
    
    // up

    if(row>0&&!visited[row-1][col]){
        int ind=grid[row-1][col]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row-1,col,curr->links[ind],word);
            visited[row-1][col]=0;
            word.pop_back();
        }
    }

    // left
    
    if(col>0&&!visited[row][col-1]){
        int ind=grid[row][col-1]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row,col-1,curr->links[ind],word);
            visited[row][col-1]=0;
            word.pop_back();
        }
    }

    // down
    
    if(row<3&&!visited[row+1][col]){
        int ind=grid[row+1][col]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row+1,col,curr->links[ind],word);
            visited[row+1][col]=0;
            word.pop_back();
        }
    }

    // right
    
    if(col<3&&!visited[row][col+1]){
        int ind=grid[row][col+1]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row,col+1,curr->links[ind],word);
            visited[row][col+1]=0;
            word.pop_back();
        }
    }

    // top left
    
    if(row>0&&col>0&&!visited[row-1][col-1]){
        int ind=grid[row-1][col-1]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row-1,col-1,curr->links[ind],word);
            visited[row-1][col-1]=0;
            word.pop_back();
        }
    }

    // top right
    
    if(row>0&&col<3&&!visited[row-1][col+1]){
        int ind=grid[row-1][col+1]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row-1,col+1,curr->links[ind],word);
            visited[row-1][col+1]=0;
            word.pop_back();
        }
    }

    // bottom left
    
    if(row<3&&col>0&&!visited[row+1][col-1]){
        int ind=grid[row+1][col-1]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row+1,col-1,curr->links[ind],word);
            visited[row+1][col-1]=0;
            word.pop_back();
        }
    }

    // bottom right
    
    if(row<3&&col<3&&!visited[row+1][col+1]){
        int ind=grid[row+1][col+1]-'a';
        if(curr->links[ind]){
            dfs(grid,visited,row+1,col+1,curr->links[ind],word);
            visited[row+1][col+1]=0;
            word.pop_back();
        }
    }
}

vector<vector<char>> generateGrid(){

    vector<vector<char>>grid = {

    {'t','f','s','g'},
    {'a','s','w','a'},
    {'n','l','s','t'},
    {'i','w','i','o'},

    };

    return grid;
}

int main(){
    cout<<endl;

    Trie trie;

    ifstream inputFile("dictionary.txt");

    if (!inputFile.is_open()) {
        cout << "Error opening the file!"<<endl;
        return 1;
    }

    string word;
    while (getline(inputFile, word)) {
        trie.insert(word);
    }

    inputFile.close();

    vector<vector<char>>grid = generateGrid();

    vector<vector<int>>visited(4,vector<int>(4,0));

    cout<<"Printing Words Found...."<<endl<<endl;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            string WORD="";
            TrieNode*curr=trie.root;
            int ind=grid[i][j]-'a';
            if(curr->links[ind]){
                dfs(grid,visited,i,j,curr->links[ind],WORD);
            }
        }
    }
}