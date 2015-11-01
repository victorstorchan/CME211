#include <iostream>
#include <fstream>
#include <string>
   
enum hand{
    nord,
    sud,
    est,
    ouest
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
    std::cout << "Usage:" << std::endl;
    std::cout <<  " ./mazesolver <maze file> <solution file> " << std::endl;
    return 0;
    }
  
    std::string filename = argv[1];
    std::string filename2 = argv[2];
    std::ifstream f;
    f.open(filename.c_str());
    if (f.is_open()) {
    int ni;
    int nj;
    int i,j;
    f >> ni >> nj;
    int a[ni][nj];
    for (int i = 0; i < ni; i++) {
    for (int j = 0; j < nj; j++) {
      a[i][j] = 1;
      
    }
  }
    while(f>>i>>j){
        a[i][j]=-1;
    }
    f.close();
    int cout;
    cout =0;
    while(a[0][cout]<0){
        cout++;
    }
    int b[2];
    b[0]=0;
    b[1]=cout;
    hand d = sud;
    std::ofstream g;
    g.open(filename2.c_str());
    if (g.is_open()) {
    g << b[0] << " "<< b[1] << std::endl;
    while(b[0]!=ni-1){
        int i =b[0];
        int j =b[1];
        int v,w;
        

        switch(d){
             case sud:
             if (a[i][j-1]>0){
                v=i;
                w=j-1;
                d = ouest;
             }
             else if (a[i+1][j]>0){
                v=i+1;
                w=j;
             }
             else if (a[i][j+1]>0){
                v=i;
                w=j+1;
                d =est;
             }
             else{
                v=i-1;
                w=j;
                d= nord;
             }
             b[0]=v;
            b[1]=w;
            g << b[0] << " "<< b[1] << std::endl;break; 
            case ouest:
             if (a[i-1][j]>0){
                v=i-1;
                w=j;
                d = nord;
             }
             else if (a[i][j-1]>0){
                v=i;
                w=j-1;
             }
             else if (a[i+1][j]>0){
                v=i+1;
                w=j;
                d =sud;
             }
             else{
                v=i;
                w=j+1;
                d= est;
             }
             b[0]=v;
            b[1]=w;
            g<< b[0] << " "<< b[1] << std::endl;break;
            case est:
             if (a[i+1][j]>0){
                v=i+1;
                w=j;
                d = sud;
             }
             else if (a[i][j+1]>0){
                v=i;;
                w=j+1;
             }
             else if (a[i-1][j]>0){
                v=i-1;
                w=j;
                d =nord;
             }
             else{
                v=i;
                w=j-1;
                d= ouest;
             }
             b[0]=v;
            b[1]=w;
            g << b[0] << " "<< b[1] << std::endl;break; 
            case nord:
             if (a[i][j+1]>0){
                v=i;
                w=j+1;
                d = est;
             }
             else if (a[i-1][j]>0){
                v=i-1;
                w=j;
             }
             else if (a[i][j-1]>0){
                v=i;
                w=j-1;
                d =ouest;
             }
             else{
                v=i+1;
                w=j;
                d= sud;
             }
             b[0]=v;
            b[1]=w;
            g << b[0] << " "<< b[1] << std::endl;break;     

        }//bracket of the switch
        }//bracket of the while
        g.close();
    }//bracket of the openg
    else {
    std::cout << "Failed to open file" << std::endl;
  }
}
  else {
    std::cout << "Failed to open file" << std::endl;
  }


  
    return 0;
}
