#include<iostream>
#include<fstream>
using namespace std;

ifstream file("floor.data");
ofstream file2("final.path");
class Bit{
 public:
  int row ;
  int col ;
};
class Robot;
class Map ;

class Path{
 public:
    int row ;
    int col ;
    Path* next ;
};
class Map{
    private:
      int vertex  , row , col , R[2];
      int**  met ;
      int** indexmap;
      int** adjList ;
      Bit* bit ;

    public:
      void setrow (int x) { row = x;};

      void setcol (int x) { col = x ;};

      void setR(int x , int y){
         R[0] = x ;
         R[1] = y ;
      };

      void initmet(){
          met = new int*[row];
          for(int i=0 ; i<row ; i++)
           met[i]=new int [col];
      };

      void setmap(int i , int j , int x) {met[i][j] = x ;};

      int* getadj(int x){return adjList[x];};

      Bit* getbit(){return bit ;};

      int getvertex(){return vertex;};

      void initindex();

      void setindex(int i , int j , int x){
          indexmap[i][j] = x ;
      };

      void setvertex(int x) {vertex = x;};

      void create_array();

      void creatList();

      friend class Robot ;
};

class Robot{
 private :
  int B ;
  Path*  head =NULL ;
  Path*  tail =NULL ;
  int* vertexfind ;
  int *find1 , *distance1 , *predecessor1  ;
  int *find2 , *distance2 , *predecessor2 ;
  int step ;
 public:

     void setB(int x) { B = x;};

     void initvertexfind(Map &map){
         vertexfind = new int [map.vertex+1] ;
         for(int i =0 ; i<=map.vertex ; i++)
           vertexfind[i] = 0 ;
     }


     void findpath(Map &map);

     void BFS_startpoint(Map &map , int x);

     void BFS_interpoint(Map &map , int x);

     int topoint (Map &map);

     int nextpoint(Map &map , int x , int y);

     void add_path(Map &map , int type , int x);

     int  updatefind(Map &map , int x , int remain , int type);

     void printpath();

};
void Map::initindex(){
          indexmap = new int*[row];
          for(int i=0 ; i<row ; i++ ){
            indexmap[i] = new int[col];
           for(int j=0 ; j<col ; j++ )
             indexmap[i][j] = -1 ;
          }
 };

void Map::create_array(){
    bit = new Bit[vertex];
    bit[0].row = R[0];
    bit[0].col = R[1];
    initindex();
    indexmap[R[0]][R[1]] = 0 ;

    int tmp = 1 ;
    for(int i=0 ; i<row ; i++){
       for(int j=0 ; j<col ; j++){
           if(met[i][j] == 0){
             bit[tmp].row = i;
             bit[tmp].col = j;
             setindex(i , j , tmp);
             tmp++ ;
           }
       }
    }

};

void Map::creatList(){
     adjList = new int*[vertex];
    for(int i = 0 ; i<row ; i++){
        for(int j = 0 ; j<col ; j++){
            int tmp =0 ;
            if(indexmap[i][j] != -1){
                adjList[indexmap[i][j]] = new int[4];
                for(int k=0 ; k<4 ; k++)
                 adjList[indexmap[i][j]][k] = -1 ;
             if(j+1<col&&indexmap[i][j+1] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i][j+1];
                tmp++ ;
             }
             if(j-1>0&&indexmap[i][j-1] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i][j-1];
                tmp++ ;
             }
             if(i+1<row&&indexmap[i+1][j] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i+1][j];
                tmp++ ;
             }
             if(i-1>0&&indexmap[i-1][j] != -1){
                adjList[indexmap[i][j]][tmp] = indexmap[i-1][j];
                tmp++ ;
             }
            }

        }

    }

    delete(indexmap);
}

int main (){
    int x , y , z , cleanblock=0 ;
    char bit ;
    file>>x>>y>>z ;
    Robot robot ;
    Map map ;
    map.setrow(x);
    map.setcol(y);
    map.initmet();
    robot.setB(z) ;
    for(int i=0 ; i<x ; i++){
        for(int j=0 ; j<y ; j++){
            file>>bit ;
            if(bit == '0') {
                map.setmap(i , j , 0);
                cleanblock++ ;

            }
            else if(bit == '1')  map.setmap(i , j , 1);
            else{
                map.setR(i , j);
                map.setmap(i , j , 2);
             }
        }
    }
    map.setvertex(cleanblock);
    map.create_array();
    map.creatList ();
    robot.findpath(map);
    robot.printpath();


return 0 ;

}
