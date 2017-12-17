#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct trieNode
{
    struct trieNode *child[58];
    bool isLeaf;
    vector<int> occ;
    trieNode() {
        isLeaf = false;
        for(int i=0;i<58;++i)
            child[i] = NULL;
    }
};

class SearchBox
{
    trieNode *root;
    bool whole;
    int start;
    void insertTrie(string &text);
    int searchWord(string &word);
    void insertWordTrie(string word, int index);
public:
    SearchBox()
    {
        start = 0;
        whole = false;
        root = new trieNode();
    }
    int find(string text, string search, string wholeWord, int start);
};

int SearchBox::find(string text, string search, string wholeWord, int start)
{
    insertTrie(text);
    if(wholeWord[0] == 'Y')
        whole = true;
    this->start = start;
    return searchWord(search);
}

void SearchBox::insertTrie(string &text)
{
    string word ;
    int N=text.size();
    int i, j;
    i=0;
    while(i<N)
    {
        j=i;
        word = "";
        while(i<N && text[i]!=' ')
        {
            word.push_back(text[i]);
            ++i;
        }
        insertWordTrie(word, j);
        ++i;
    }
}

void SearchBox::insertWordTrie(string word, int index)
{
    int N = word.size();
    trieNode *curr = root;
    int i, j;
    for(i=N-1;i>=0;--i)
    {
        curr = root;
        for(j=i;j<N;++j)
        {
            if(curr->child[word[j]-'A'] == NULL)
                curr->child[word[j]-'A'] = new trieNode();
            curr = curr->child[word[j]-'A'];
            curr->occ.push_back(index+i);
        }
        if(i==0)
            curr->isLeaf = true;
    }
}

int SearchBox::searchWord(string &word)
{
    int index, N;
    N = word.size();
    trieNode *curr = root;
    for(int i=0;i<N;++i)
    {
        index = word[i]-'A';
        if(curr->child[index]==NULL)
            return -1;
        curr = curr->child[index];
    }
    int M = curr->occ.size();
    for(int i=0;i<M;++i)
    {
        if(curr->occ[i] >= start)
            return curr->occ[i];
    }
    return -1;
}
