#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string.h>
#include<string>
#include<cstdio>

using namespace std;
typedef long long int lli;

class Suffix
{
public:
    lli origin_node;
    lli first_char_index;
    lli last_char_index;
    Suffix(lli node, lli first, lli last) :
        origin_node(node),
        first_char_index(first),
        last_char_index(last) {};
    lli Explicit() {return first_char_index > last_char_index; }
    lli Implicit() {return first_char_index <= last_char_index; }
    void Canonize();
};

class Edge
{
public:
    lli first_char_index;
    lli last_char_index;
    lli end_node;
    lli start_node;
    void Insert();
    void Remove();
    Edge();
    Edge( lli init_first, lli init_last, lli parent_node);
    lli SplitEdge(Suffix &s);
    static Edge Find(lli node, lli c);
    static lli Hash(lli node, lli c);
};

class Node
{
public:
    lli suffix_node;
    Node() { suffix_node = -1; }
    static lli Count;
};

const lli MAX_LENGTH = 500005;
const lli HASH_TABLE_SIZE = 2000003;

Edge Edges[HASH_TABLE_SIZE];
lli Node::Count = 1;
Node Nodes[MAX_LENGTH*2];

char T[MAX_LENGTH];
lli N, M;

Edge::Edge()
{
    start_node = -1;
}

Edge::Edge(lli init_first, lli init_last, lli parent_node)
{
    first_char_index = init_first;
    last_char_index = init_last;
    start_node = parent_node;
    end_node = Node::Count++;
}

lli Edge::Hash(lli node, lli c)
{
    return ((node<<8) + c)%HASH_TABLE_SIZE;
}

void Edge::Insert()
{
    lli i = Hash(start_node, T[first_char_index]);
    while(Edges[i].start_node!=-1)
        i = ++i % HASH_TABLE_SIZE;
    Edges[i] = *this;
}

void Edge::Remove()
{
    lli i = Hash(start_node, T[first_char_index]);
    while(Edges[i].start_node!=start_node || Edges[i].first_char_index!=first_char_index)
        i = ++i % HASH_TABLE_SIZE;
    for( ; ; )
    {
        Edges[i].start_node = -1;
        lli j = i;
        for( ; ; )
        {
            i = ++i % HASH_TABLE_SIZE;
            if(Edges[i].start_node==-1)
                return ;
            lli r = Hash(Edges[i].start_node, T[Edges[i].first_char_index]);
            if(i>=r && r>j)
                continue;
            if(r>j && j>i)
                continue;
            if(j>i && i>=r)
                continue;
            break;
        }
        Edges[j] = Edges[i];
    }
}

Edge Edge::Find(lli node, lli c)
{
    lli i = Hash(node, c);
    for( ; ; )
    {
        if(Edges[i].start_node==node && T[Edges[i].first_char_index]==c)
            return Edges[i];
        if(Edges[i].start_node==-1)
            return Edges[i];
        i = ++i %HASH_TABLE_SIZE;
    }
}

lli Edge::SplitEdge(Suffix &s)
{
    Remove();
    Edge *new_edge = new Edge(first_char_index,
                              first_char_index+s.last_char_index-s.first_char_index,
                              s.origin_node);
    new_edge->Insert();
    Nodes[new_edge->end_node].suffix_node = s.origin_node;
    first_char_index += s.last_char_index-s.first_char_index+1;
    start_node = new_edge->end_node;
    Insert();
    return new_edge->end_node;
}

void Suffix::Canonize()
{
    if(!Explicit())
    {
        Edge edge = Edge::Find(origin_node, T[first_char_index]);
        lli edge_span = edge.last_char_index - edge.first_char_index;
        while(edge_span <= (last_char_index-first_char_index))
        {
            first_char_index += edge_span+1;
            origin_node = edge.end_node;
            if(first_char_index<=last_char_index)
            {
                edge = Edge::Find(edge.end_node, T[first_char_index]);
                edge_span = edge.last_char_index-edge.first_char_index;
            }
        }
    }
}

void AddPrefix(Suffix &active, lli last_char_index)
{
    lli parent_node;
    lli last_parent_node = -1;

    for( ; ; )
    {
        Edge edge;
        parent_node = active.origin_node;
        if(active.Explicit())
        {
            edge = Edge::Find(active.origin_node, T[last_char_index]);
            if(edge.start_node != -1)
                break;
        }
        else
        {
            edge = Edge::Find(active.origin_node, T[active.first_char_index]);
            lli span = active.last_char_index-active.first_char_index;
            if(T[edge.first_char_index+span+1] == T[last_char_index])
                break;
            parent_node = edge.SplitEdge(active);
        }
        Edge *new_edge = new Edge(last_char_index, N, parent_node);
        new_edge->Insert();
        if(last_parent_node>0)
            Nodes[last_parent_node].suffix_node = parent_node;
        last_parent_node = parent_node;

        if(active.origin_node==0)
            active.first_char_index++;
        else
            active.origin_node = Nodes[active.origin_node].suffix_node;
        active.Canonize();
    }
    if(last_parent_node>0)
        Nodes[last_parent_node].suffix_node = parent_node;
    active.last_char_index++;
    active.Canonize();
}

lli lcsLength;
lli lcsBeginIndex;
string alphabet;
lli alphabetSize;
#define ALPHA 28

lli findLCS(lli node, lli i1, lli i2, lli depth)
{
    lli c, i;
    lli mask = 0;
    lli flag = 0;
    for(lli f=0; f<28; ++f)
    {
        c = alphabet[f];
        i = Edge::Hash(node, c);
        if(Edges[i].start_node==-1)
            continue;
        if(Edges[i].first_char_index<=i1 && i1<=Edges[i].last_char_index)
            mask |= 1;
        else if(Edges[i].first_char_index<=i2 && i2<=Edges[i].last_char_index)
            mask |= 2;
        else
            mask |= findLCS(Edges[i].end_node, i1, i2, depth + (Edges[i].last_char_index-Edges[i].first_char_index)+1);
    }
    if(mask==3)
    {
        if(depth>lcsLength)
            lcsLength = depth;
    }
    return mask;
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);
    //cin.getline(T, MAX_LENGTH/2); //add non-matching symbol(dollar sign) at last
    scanf("%s", T);
    N = strlen(T)-1;
    T[++N] = '-';
    M = N;
    //cin.getline(T+N+1, MAX_LENGTH/2);
    scanf("%s", T+N+1);
    N = strlen(T);
    T[N] = '#';

    Suffix active(0, 0, -1);
    for(lli i=0; i<=N; ++i)
        AddPrefix(active, i);

    alphabet = "abcdefghijklmnopqrstuvwxyz-#";
    alphabetSize = alphabet.size();
    lcsLength = 0;
    findLCS(0, M, N, 0);
    //cout<<lcsLength<<endl;
    printf("%d\n", lcsLength);
    return 0;
}
