#### vector实现建图

```cpp
const int MAX_EDGES=100010;
vector <int> ver[MAX_EDGES],edge[MAX_EDGES];
 
void add(int x,int y,int z){//保存从x到y权值为z的有向边
    ver[x].push_back(y);
    edge[x].push_back(z);
}
 
for(int i=0;i<ver[x].size();i++){//遍历从x出发的所有边
    int y=ver[x][i];
    int z=edge[x][i];
       //有向边(x,y,z)
}

```
