#include<stdio.h>
#define Max_Vertices 20
#define Max_length 20
#define Max_Element 40
typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n;
}Graph;
typedef struct {
    int data[Max_length];
    int size;
}List;
typedef struct {
    int data[Max_Element];
    int size;
}Stack;
// -------------GRAPH------------------ //
// Ham khoi tao do thi
void init_Graph(Graph *G, int n){
    int i,j;
    G->n=n;
    for(i=1; i<=n ;i++){
        for(j=1; j<=n ;j++){
            G->A[i][j]=0;
        }
    }
}
// Ham them cung vao do thi vo huong 2->3 & 3->2 = 1
void add_edge(Graph *G, int x, int y){
    G->A[x][y]=1;
    G->A[y][x]=1;
}
// Ham kiem tra lang gieng
int adjacent(Graph *G, int x, int y){
    return (G->A[x][y]!=0);
}
// Ham tinh bac cua dinh
int degree(Graph *G, int x){
    int i,deg=0;
    for(i=1; i<=G->n; i++){
        if(G->A[i][x]==1) deg++; //adjacent(G,i,x)
    }
    return deg;
}
// -------------LIST------------------ //
// Khoi tao list de luu dinh lang gieng
void make_nullList(List *L){
    L->size=0;
}
// Them dinh lang gieng x vao list
void push_back(List *L, int x){
    L->data[L->size]=x;
    L->size++;
}
// Tra ve 1 list cac dinh lang gieng cua dinh x
List neighbors(Graph *G, int x){
    int i;
    List L;
    make_nullList(&L);
    for(i=1; i<=G->n; i++){
        if(G->A[i][x]==1) push_back(&L,i); //adjacent(G,i,x)
    }
    return L;
}
// Lay dinh tai vi tri i
int element_at(List *L, int i){
    return L->data[i-1];
}
// -------------STACK------------------ //
// Khoi tao stack
void make_nullStack(Stack *S){
    S->size=Max_Element;
}
// Kiem tra stack rong
int empty_stack(Stack *S){
    return S->size==Max_Element;
}
// Them phan tu vao stack
void push(Stack *S, int x){
    if(S->size!=0){
        S->size--;
        S->data[S->size]=x;
    }
}
// Lay phan tu ra khoi stack
void pop(Stack *S){
    if(!empty_stack(S)){
        S->size++;
    }
}
// Lay gia tri phan tu trong stack
int top(Stack *S){
    return S->data[S->size];
}
// Duyet do thi dinh x theo chieu sau
List depth_first_search(Graph *G, int x, int parent[]){
    // danh sach luu cac dinh duoc duyet tu cua dinh x
	List list_dfs; 
    make_nullList(&list_dfs);
    Stack S;
    int u,i;
    make_nullStack(&S);
    push(&S,x);
    parent[x]=0;
    // Tao list de danh dau dinh duoc duyet
    int mark[Max_Vertices]; // do dai cua mark == so luong dinh
    for(i=1; i<=G->n; i++){ // khoi tao cac dinh la chua danh dau
        mark[i]=0;
    }
    // Thuc hien duyet do thi
    while(!empty_stack(&S)){
        u=top(&S);
        pop(&S);
        if(mark[u]==1) continue;
        mark[u]=1;
        push_back(&list_dfs,u);
        List u_neighbors=neighbors(G,u); //Luu list cac phan tu lang gieng cua u
        for(i=1; i<=u_neighbors.size; i++){
            int v = element_at(&u_neighbors,i);
            if(mark[v]==0){
            	parent[v]=u;
            	push(&S,v);
			}
        }
    }
    return list_dfs;
}
int main(){
    FILE *file = freopen("input2.txt","r",stdin);
    int n,m,u,v,i,j;
    scanf("%d%d",&n,&m);
    // Khoi tao do thi
    Graph G;
    init_Graph(&G,n);
    for(i=1; i<=m; i++){
        scanf("%d%d",&u,&v);
        add_edge(&G,u,v);
    }
    // Tao list luu tat ca cac dinh duoc danh dau chua
    int mark_dfs[Max_Vertices];
    int parent[Max_Vertices];
    for(i=1; i<=G.n; i++){
        mark_dfs[i]=0;
        parent[i]=-1;
    }
    
    // Duyet do thi khong lien thong
    for(i=1; i<=G.n; i++){
        if(mark_dfs[i]==0){
            List list_v = depth_first_search(&G,i,parent);
            for(j=1; j<=list_v.size; j++){
                mark_dfs[list_v.data[j-1]]=1;
            }
        }
    }
    // In cac dinh va parent tuong ung cua do thi
    for(i=1; i<=G.n; i++){
        printf("%d %d\n",i,parent[i]);
    }
    fclose(file);
}
