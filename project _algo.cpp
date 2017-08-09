#include<iostream>
#include<cstdio>
#define MAX 100
#define INT_MAX 100000
using namespace std;
void func1(int[][MAX],int[][MAX],int[],int[],int,int&,int,int);
void func2(int[][MAX],int[][MAX],int[],int[],int,int&,int,int,int);
int dijkstra(int[][MAX],int[],int,int,int,int&);
int main()
{
    int n,i,j,t;
    int km_wage,day_wage;
    //cout<<"\nEnter the number of locations needed :";
    //cin>>t;
    t=10;
    char *ch[10]={"JIIT","Noida City center","Corenthum","Kaushambi","Vaishali","KArkarduma","IIT DElhi","Shipra","Windsor","Jaipuria mall"};
    int arr[MAX][MAX],sol[MAX][MAX],emp_pos[t],cost[t],opt_num=0;
    /*int arr1[5][5]={{0,3,3,4,5},
                    {3,0,15,12,8},
                    {3,15,0,23,1},
                    {4,12,23,0,9},
                    {5,8,1,9,0}};*/
    int arr1[10][10]={  {0,10,1,8,9,12,50,2,3,5},
                        {10,0,9,8,13,17,70,7,8,6},
                        {1,9,0,5,6,7,67,4,5,3},
                        {8,8,5,0,1,2,70,5,6,4},
                        {9,13,6,1,0,3,75,6,7,5},
                        {12,17,7,2,3,0,69,10,11,8},
                        {50,70,67,70,75,69,0,59,60,58},
                        {2,7,4,5,6,10,59,0,1,3},
                        {3,8,4,6,7,11,60,1,0,2},
                        {5,6,3,4,5,8,58,3,2,0}
                    };

    for(i=0;i<t;++i){
        for(j=0;j<t;++j)
            arr[i][j]=0,sol[i][j]=0;
        emp_pos[i]=0,cost[i]=0;
    }
    for(i=0;i<t;++i)
    {
        for(j=i+1;j<t;++j)
        {
            //cout<<"\nEnter the length of path from "<<i<<" to "<<j<<" :";
            arr[i][j]=arr1[i][j];
            arr[j][i]=arr[i][j];
        }
    }
    for(i=0;i<t;++i)
    {
        for(j=0;j<t;++j)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
    /*cout<<"\nWhat is the per KM wage :";
    cin>>km_wage;
    cout<<"\nWhat is the daily wage :";
    cin>>day_wage;*/
    km_wage=10,day_wage=100;
    func1(arr,sol,emp_pos,cost,t,opt_num,km_wage,day_wage);
    cout<<"\nThe solution is :\n";
    for(i=0;i<opt_num;++i){
        for(j=0;j<t;++j)
            cout<<sol[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";
    for(i=1;i<t;++i){
        cout<<"The cost to reach "<<ch[i]<<" by "<<cost[i]<<"\n";
    }
    return 0;
}
int minDistance(int dist[], bool sptSet[],int t)
{
    // Initialize min value
    int min = INT_MAX, min_index;
    for (int v = 0; v < t; v++)
        if (sptSet[v] == false && dist[v] < min) // Pick the vertex with minimum distance not included in the shortest path set
            min = dist[v], min_index = v;
    return min_index;
}
int printSolution(int dist[], int n)
{
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; i++)
            printf("%d \t\t %d\n", i, dist[i]);
}
/*
// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation.
    arr[] is the array that contains the graph in sparse matrix form.
    emp_pos[] is the array that will  store the position of the i th employ.
    current_pos is the position to which we have to reach.
    t is the number of locations.
    src is the starting position.
    opt_num is the currently no of employs in use.
    km_wage is the wage that the company will pay to each employ for a single km walk.
*/
bool IsSafe(int emp_pos[],int opt_num,int t)
{
    for(int i=0;i<opt_num;i++){
        if(emp_pos[i]==t)
            return false;
    }
    return true;
}
int dijkstra(int arr[][MAX],int emp_pos[],int current_pos,int t,int src,int& opt_num)
{
    //cout<<"\nWe calculate for the "<<current_pos<<"th employee from "<<emp_pos[src];
     int dist[current_pos];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool sptSet[current_pos]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < current_pos; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     // Distance of source vertex from itself is always 0
     dist[emp_pos[src]] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < current_pos-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(dist, sptSet,current_pos);

       // Mark the picked vertex as processed
       sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 1; v < current_pos; v++){

         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
         if (!sptSet[v] && arr[u][v] && dist[u] != INT_MAX
                                       && dist[u]+arr[u][v] < dist[v]&&IsSafe(emp_pos,opt_num,v))
            dist[v] = dist[u] + arr[u][v];
       }
     }
    /* cout<<endl;
    for(int i=0;i<current_pos;++i)
        cout<<dist[i]<<" ";
    cout<<endl;*/
     // print the constructed distance array
    return dist[current_pos-1];
}
/*
    arr[] is the array that contains the graph in sparse matrix form.
    sol[] is the array that will have the optimal path that each employ will travel respectively.
    emp_pos[] is the array that will  store the position of the i th employ.
    t is the number of locations.
    opt_num is the optimal number of employs needed for the traversal of all locations.
    km_wage is the wage that the company will pay to each employ for a single km walk.
    day_wage is the wage that the company will pay to each employ for 1 day work irrespective of the work done.
*/
void func1(int arr[][MAX],int sol[][MAX],int emp_pos[],int cost[],int t,int& opt_num,int km_wage,int day_wage)
{
    for(int l=1;l<t;++l)    // the o th index is the location of the office. All the t employs are initially at the office position.
    {
        //cout<<"\nWe calculate for the "<<l<<"th office\n";
        func2(arr,sol,emp_pos,cost,t,opt_num,km_wage,day_wage,l);
    }
}
/*
    The current_pos is the position of the location currently to be reached or added to the solution path.
*/
void func2(int arr[][MAX],int sol[][MAX],int emp_pos[],int cost[],int t,int& opt_num,int km_wage,int day_wage,int current_pos)
{
    int min=0,che=-1;
    min=arr[0][current_pos]*km_wage+day_wage; // The Total cost of adding a new employ is distance_of_current_pos_from_office*km_wage+daily_wage(as new employ has come).
    //cout<<"\nThe cost from office to "<<current_pos<<" is :"<<min;
    for(int i=0;i<opt_num;++i)
    {
        int dis=dijkstra(arr,emp_pos,current_pos+1,t,i,opt_num)*km_wage; // Find the shortest path from i th employ's position to current_pos.
        //int dis=(arr[emp_pos[i]][current_pos])*km_wage;
        //cout<<"\nThe cost to come to "<<current_pos<<" from "<<emp_pos[i]<<" is :"<<dis;
        if(dis<min){
          //  cout<<"\nHere we update";
            min=dis;
            che=i;
        }
    }
    if(che==-1)
    {
        //cout<<"\nwe need a new employee";
        opt_num++;  // We need more employs.
        emp_pos[opt_num-1]=current_pos; // make this new employ position at current_pos.
        sol[opt_num-1][current_pos]=1;    // The new employ is at current_pos.
        cost[current_pos]=min;
    }
    else{
       // cout<<"\nWe move with the existing solution. The optimal number is :"<<opt_num;
        emp_pos[che]=current_pos; //che th employ is now at current_pos
        sol[che][current_pos]=1; // mark che employ has also traversed current_pos.
        cost[current_pos]=min;
    }
}
