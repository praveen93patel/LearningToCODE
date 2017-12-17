#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

struct trieNode
{
    struct trieNode *child[26];
    bool isLeaf;
    trieNode()
    {
        isLeaf = false;
        for(int i=0;i<26;++i)
            child[i] = NULL;
    }
};

class CyclicWords
{
    int DW;
    trieNode *root;
    void insertTrie(string word);
public:
    CyclicWords()
    {
        DW = 0;
        root = new trieNode();
    }
    int differentCW(vector<string> words);
};

int CyclicWords::differentCW(vector<string> words)
{
    int N = words.size();
    for(int i=0;i<N;++i)
    {
        insertTrie(words[i]);
    }
    return DW;
}

void CyclicWords::insertTrie(string word)
{
    trieNode *curr = root;
    int N = word.size();
    for(int i=0;i<N; ++i)
    {
        if(curr->child[word[i]-'a'] == NULL)
            curr->child[word[i]-'a'] = new trieNode();
        curr = curr->child[word[i]-'a'];
    }
    if(curr->isLeaf == true)
        return ;
    curr->isLeaf = true;
    ++DW;
    word += word;
    for(int i=1;i<N;++i)
    {
        curr = root;
        for(int j=0;j<N;++j)
        {
            if(curr->child[word[i+j]-'a'] == NULL)
                curr->child[word[i+j]-'a'] = new trieNode();
            curr = curr->child[word[i+j]-'a'];
        }
        if(curr->isLeaf == true)
            return;
        curr->isLeaf = true;
    }
}
