// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int maxn = 300000 + 10;
const int maxlogn = 23;
int anc[maxn][maxlogn];
int edgecc;
int s[maxn];
struct Node
{
    int id;
    int son;
    int depth;
    int cnt;
}Nodes[maxn];

struct Edge
{
    int to;
    int next;
}Edges[maxn];

inline void add_edge(int from,int to)
{
    auto &p=Edges[edgecc];
    p.to=to;
    p.next=Nodes[from].son;
    Nodes[from].son=edgecc;
    edgecc++;
}

inline void give_father(int now,int father,int depth)
{
    anc[now][0]=father;
    for(int i=Nodes[now].son;i!=-1;i=Edges[i].next)
    {
        if(Edges[i].to==father)continue;
        Nodes[Edges[i].to].depth=depth;
        give_father(Edges[i].to,now,depth+1);
    }
}

inline void init_st(void)
{
    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;i<=n;i++)
        {
            anc[i][j]=anc[anc[i][j-1]][j-1];
        }
    }
}

inline void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)Nodes[i].id=i,Nodes[i].son=-1;
    for(int i=1;i<=n;i++)scanf("%d",s+i);
    for(int i=0;i<n-1;i++)
    {
        int from,to;
        scanf("%d%d",&from,&to);
        add_edge(from,to);
        add_edge(to,from);
    }
    give_father(1,-1,1);
    init_st();
}
inline int Query(int x,int y)
{
    if(Nodes[x].depth<Nodes[y].depth)swap(x,y);
    int dist=Nodes[x].depth-Nodes[y].depth;
    int i=0;
    while(dist!=0)
    {
        if((1<<i)&dist)
            x=anc[x][i],dist-=(1<<i);
        i++;
    }
    if(x==y)return x;
    if(x!=y)
    {
        for(int i=(int)log2(Nodes[x].depth);i>=0;i--)
        {
            if(anc[x][i]!=anc[y][i])
                x=anc[x][i],y=anc[y][i];
        }
    }
    return anc[x][0];
}
void DFS(int pos)
{
    for(int i=Nodes[pos].son;i!=-1;i=Edges[i].next)
    {
        if(Edges[i].to==anc[pos][0])continue;
        DFS(Edges[i].to);
        Nodes[pos].cnt+=Nodes[Edges[i].to].cnt;
    }
}
inline void Work(void)
{
    for(int i=1;i<n;i++)
    {
        Nodes[s[i]].cnt++;
        Nodes[s[i+1]].cnt++;
        Nodes[Query(s[i],s[i+1])].cnt--;
        Nodes[anc[Query(s[i],s[i+1])][0]].cnt--;
    }
    DFS(1);
    for(int i=2;i<=n;i++)
        Nodes[s[i]].cnt--;
}
inline void Give_Ans(void)
{
    for(int i=1;i<=n;i++)printf("%d\n",Nodes[i].cnt);
}
int main()
{
    init();
    Work();
    Give_Ans();
}
