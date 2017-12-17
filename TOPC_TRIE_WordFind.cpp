#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct trieNode
{
    struct trieNode *child[26];
    bool isLeaf;
    int index;
    bool done;
    trieNode() {
        done = false;
        isLeaf = false;
        index = -1;
        for(int i=0;i<26;++i)
            child[i] = NULL;
    }
};

class WordFind
{
    struct trieNode *root;
    void insertTrie(vector<string> &wordList);
    void searchWord(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans);
    void searchWordRight(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans);
    void searchWordDown(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans);
    void searchWordDiag(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans);
public:
    WordFind()
    {
        root = new trieNode();
    }
    vector<string> findWords(vector<string> grid, vector<string> wordList);
};

vector<string> WordFind::findWords(vector<string> grid, vector<string> wordList)
{
    vector<string> ans(wordList.size());
    string str;
    insertTrie(wordList);
    int M = grid.size();
    int N = grid[0].size();
    for(int i=0;i<M;++i)
    {
        for(int j = 0; j<N; ++j)
        {
            if(root->child[grid[i][j]-'a'])
            {
                str = to_string(i) + " " + to_string(j);
                searchWord(root->child[grid[i][j]-'a'], grid, i, j, str, ans);
            }
        }
    }
    return ans;
}

void WordFind::insertTrie(vector<string> &wordList)
{
    int n = wordList.size();

    int i, j;
    for(i=0;i<n;++i)
    {
        int m = wordList[i].size();
        trieNode *curr = root;
        for(j=0;j<m;++j)
        {
            int index = wordList[i][j]-'a';
            if(curr->child[index]==NULL)
                curr->child[index] = new trieNode();
            curr = curr->child[index];
        }
        curr->isLeaf = true;
        curr->index = i;
    }
}
void WordFind::searchWord(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans)
{
    searchWordRight(root, grid, i, j, str, ans);
    searchWordDown(root, grid, i, j, str, ans);
    searchWordDiag(root, grid, i, j, str, ans);
}


void WordFind::searchWordRight(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans)
{
    if(root->isLeaf==true && root->done==false)
    {
        ans[root->index] = str;
        root->done = true;
    }
    int N=grid[0].size();
    for(int k=0;k<26; ++k)
    {
        if(root->child[k]!=NULL && j+1<N && grid[i][j+1]==(char)(k+'a'))
            searchWordRight(root->child[k], grid, i, j+1, str, ans);
    }
}
void WordFind::searchWordDown(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans)
{
    if(root->isLeaf==true && root->done==false)
    {
        ans[root->index] = str;
        root->done = true;
    }
    int N=grid.size();
    for(int k=0;k<26; ++k)
    {
        if(root->child[k]!=NULL && i+1<N && grid[i+1][j]==(char)(k+'a'))
            searchWordRight(root->child[k], grid, i+1, j, str, ans);
    }
}
void WordFind::searchWordDiag(trieNode *root, vector<string> &grid, int i, int j, string str, vector<string> &ans)
{
    if(root->isLeaf==true && root->done==false)
    {
        ans[root->index] = str;
        root->done = true;
    }
    int M=grid.size();
    int N=grid[0].size();
    for(int k=0;k<26; ++k)
    {
        if(root->child[k]!=NULL && i+1<M && j+1<N && grid[i+1][j+1]==(char)(k+'a'))
            searchWordRight(root->child[k], grid, i+1, j+1, str, ans);
    }
}
