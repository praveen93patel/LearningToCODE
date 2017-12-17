#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct trieNode
{
    struct trieNode *child[20];
    bool isLeaf;
    trieNode()
    {
        for(int i=0; i<20; ++i)
            child[i] = NULL;
        isLeaf = false;
    }
};

class TagalogDictionary
{
    trieNode *root;
    int *prior_alpha;
    int *alpha_prior;
    int ng;
    void init();
    void insertTrie(string &str);
    void DFTraversal(vector<string> &ans, string &str, trieNode *root);
public:
    TagalogDictionary()
    {
        root = new trieNode();
        prior_alpha = new int[26];
        alpha_prior = new int[26];
        init();
    }
    vector<string> sortWords(vector<string> words);
};

void TagalogDictionary::init()
{
    int p = 0;
    for(int i=0;i<26;++i)
    {
        alpha_prior[i] = p;
        prior_alpha[p] = i;
        ++p;
        if((char)(i+'a')=='n')
        {
            ng = p;
            ++p;
        }
    }
    alpha_prior[10] = 2;
    prior_alpha[2] = 10;
}



vector<string> TagalogDictionary::sortWords(vector<string> words)
{
   // sort(words.begin(), words.end(), MyCompare);
    //return words;
    int N = words.size();
    for(int i=0;i<N;++i)
        insertTrie(words[i]);
    vector<string> ans;
    string str;
    DFTraversal(ans, str, root);
    return ans;
}

void TagalogDictionary::insertTrie(string &str)
{
    int N = str.size();
    int i=0;
    trieNode *curr = root;
    int index;
    while(i<N)
    {
        if(i<N-1 && str[i]=='n' && str[i+1]=='g')
        {
            index = ng;
            i+=2;
        }
        else
        {
            index = alpha_prior[str[i]-'a'];
            ++i;
        }
        if(curr->child[index]==NULL)
            curr->child[index] = new trieNode();
        curr = curr->child[index];
    }
    curr->isLeaf = true;
}

void TagalogDictionary::DFTraversal(vector<string> &ans, string &str, trieNode *root)
{
    if(root==NULL)
        return ;
    if(root->isLeaf == true)
    {
        ans.push_back(str);
    }
    for(int i=0; i<26; ++i)
    {
        if(root->child[i] != NULL)
        {
            if(i==ng)
                str = str + "ng";
            else
                str.push_back((char)(prior_alpha[i]+'a'));
            DFTraversal(ans, str, root->child[i]);
            if(i==ng)
                str.pop_back();
            str.pop_back();
        }
    }
}

/*bool MyCompare(string a, string b)
{
    int M = a.size();
    int N = b.size();
    int i, j;
    int p1, p2;
    i=j=0;
    while(i<M && j<N)
    {
        if(i<M-1 && a[i] == 'n' && a[i+1]=='g')
        {
            p1 = ng;
            i+=2;
        }
        else
        {
            p1 = alph_prior[a[i]-'a'];
            ++i;
        }
        if(j<N-1 && b[j]=='n' && b[j+1]=='g')
        {
            p2 = ng;
            j+=2;
        }
        else
        {
            p2 = alph_prior[b[j]-'a'];
            ++j;
        }
        if(p1<p2)
            return true;
        else if(p1>p2)
            return false;
    }
    if(j<N)
        return true;
    return false;
}*/
