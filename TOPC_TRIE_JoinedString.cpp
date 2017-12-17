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
        isLeaf = false;
        for(int i=0;i<26;++i)
            child[i] = NULL;
    }
};

class JoinedString
{
    int N;
    int max_size;
    trieNode *root;
    vector<trieNode*> rootWord;
    void sortWords(vector<string> &words);
    void DFSTraversal(trieNode *root, vector<string> &words, string &str);
    void makeTrieWords(vector<string> &words);
    void insertSuffixTrie(trieNode **rootRef, string &str);
    void joinWordsUtil(vector<string> &words, int c, int prev, vector<bool> &visited, string &str, string &ans);
    int LCP(trieNode *root, string &word);
public:
    JoinedString()
    {
        root = new trieNode();
        max_size = 100000;
    }
    string joinWords(vector<string> words);
};

string JoinedString::joinWords(vector<string> words)
{
    N = words.size();
    sortWords(words);
    makeTrieWords(words);
    vector<bool> visited(N, false);
    string str = "";
    string ans;
    joinWordsUtil(words, 0, -1, visited, str, ans);
    return ans;
}

void JoinedString::joinWordsUtil(vector<string> &words, int c, int prev, vector<bool> &visited, string &str, string &ans)
{
    if(c == N)
    {
        if(str.size() < max_size)
        {
            max_size = str.size();
            ans = str;
        }
        return;
    }
    string temp;
    for(int i=0;i<N;++i)
    {
        if(!visited[i])
        {
            visited[i] = true;
            if(prev==-1)
                temp = words[i];
            else
            {
                int k = LCP(rootWord[prev], words[i]);
                temp = words[i].substr(k);
            }
            str = str+temp;
            joinWordsUtil(words, c+1, i, visited, str, ans);
            str.erase(str.end()-temp.size());
            visited[i] = false;
        }
    }
}

int JoinedString::LCP(trieNode *root, string &word)
{
    int N = word.size();
    trieNode *curr = root;
    int i=0;
    while(curr->child[i]!=NULL)
        curr = curr->child[i++];
    return i;
}

void JoinedString::makeTrieWords(vector<string> &words)
{
    int N = words.size();
    for(int i=0; i<N; ++i)
    {
        rootWord[i] = new trieNode();
        insertSuffixTrie(&rootWord[i], words[i]);
    }
}

void JoinedString::insertSuffixTrie(trieNode **rootRef, string &str)
{
    trieNode *root = *rootRef;
    int N = str.size();
    for(int i=N-1;i>=0;--i)
    {
        trieNode *curr = root;
        for(int j=i;j<N;++j)
        {
            int index = str[j]-'A';
            if(curr->child[index]==NULL)
                curr->child[index] = new trieNode();
        }
    }
}

void JoinedString::sortWords(vector<string> &words)
{
    int N = words.size();
    trieNode *curr;
    for(int i=0;i<N;++i)
    {
        curr = root;
        int M = words[i].size();
        for(int j=0;j<M;++j)
        {
            int index = words[i][j]-'A';
            if(curr->child[index]==NULL)
                curr->child[index] = new trieNode();
            curr = curr->child[index];
        }
        curr->isLeaf = true;
    }
    words.clear();
    string str;
    DFSTraversal(root, words, str);
}

void JoinedString::DFSTraversal(trieNode *root, vector<string> &words, string &str)
{
    if(root == NULL)
        return ;
    if(root->isLeaf == true)
    {
        words.push_back(str);
    }
    for(int i=0;i<26;++i)
    {
        if(root->child[i]!=NULL)
        {
            str.push_back((char)(i+'A'));
            DFSTraversal(root->child[i], words, str);
            str.pop_back();
        }
    }
}
