#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct trieNode
{
    trieNode *child[26];
    bool isLeaf;
    trieNode()
    {
        for(int i=0;i<26;++i)
            child[i]=NULL;
        isLeaf = false;
    }
};

struct trieNode2
{
    trieNode2 *child[26];
    bool isLeaf;
    bool isAmbiguous;
    trieNode2()
    {
        for(int i=0; i<26;++i)
            child[i] = NULL;
        isLeaf = false;
        isAmbiguous = false;
    }
};

class CmpdWords
{
    trieNode *rootDict;
    trieNode2 *rootCmpd;
    int cntAmb;
    void makeDictionaryTrie(vector<string> &dict);
    void makeCmpdWordsTrie(vector<string> &dict);
    void findMoreAmbiguous();
    void insertCmpdWordsTrie(string cmpd);
    void DFSTraversal(trieNode *rootDict, trieNode2 *rootCmpd);
public:
    CmpdWords()
    {
        rootDict = new trieNode();
        rootCmpd = new trieNode2();
        cntAmb = 0;
    }
    int ambiguous(vector<string> dictionary);
};

int CmpdWords::ambiguous(vector<string> dictionary)
{
    makeDictionaryTrie(dictionary);
    makeCmpdWordsTrie(dictionary);
    findMoreAmbiguous();
    return cntAmb;
}


void CmpdWords::makeDictionaryTrie(vector<string> &dict)
{
    int N = dict.size();
    trieNode *curr;
    int index;
    for(int i=0;i<N;++i)
    {
        int M = dict[i].size();
        curr = rootDict;
        for(int j=0;j<M;++j)
        {
            index = dict[i][j] -  'a';
            if(curr->child[index] == NULL)
                curr->child[index] = new trieNode();
            curr = curr->child[index];
        }
        curr->isLeaf = true;
    }
}

void CmpdWords::makeCmpdWordsTrie(vector<string> &dict)
{
    int N = dict.size();
    int i, j;
    for(i=0;i<N-1;++i)
    {
        for(j=i+1;j<N;++j)
        {
            insertCmpdWordsTrie(dict[i] + dict[j]);
            insertCmpdWordsTrie(dict[j] + dict[i]);
        }
    }
}

void CmpdWords::insertCmpdWordsTrie(string cmpd)
{
    int N = cmpd.size();
    trieNode2 *curr = rootCmpd;
    for(int i=0; i<N; ++i)
    {
        int index = cmpd[i] - 'a';
        if(curr->child[index] == NULL)
            curr->child[index] = new trieNode2();
        curr = curr->child[index];
    }
    if(curr->isLeaf == true && curr->isAmbiguous == false)
    {
        curr->isAmbiguous = true;
        ++cntAmb;
    }
    curr->isLeaf = true;
}

void CmpdWords::findMoreAmbiguous()
{
    DFSTraversal(rootDict, rootCmpd);
}

void CmpdWords::DFSTraversal(trieNode *rootDict, trieNode2 *rootCmpd)
{
    if(rootDict == NULL || rootCmpd == NULL)
        return;
    if(rootDict->isLeaf && rootCmpd->isLeaf && rootCmpd->isAmbiguous==false)
    {
        rootCmpd->isAmbiguous = true;
        ++cntAmb;
    }
    for(int i=0;i<26;++i)
        DFSTraversal(rootDict->child[i], rootCmpd->child[i]);
}
