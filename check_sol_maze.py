import numpy as np
import sys
def checksoln(mazefile,pseudo_sol):
    #we store the data in list and numpy array.
    lmaze0=[]
    h = open(mazefile,'r')
    for line in h:
        lmaze0.append(line.split())
    h.close()
    lmaze=[]
    for i in range(len(lmaze0)):
        lmaze_i=[]
        for j in range(2):
            lmaze_i.append(int(lmaze0[i][j]))
        lmaze.append(lmaze_i)
        
    lsol0=[]
    g = open(pseudo_sol,'r')
    for line in g:
        lsol0.append(line.split())
    g.close()
    lsol=[]
    for i in range(len(lsol0)):
        lsol_i=[]
        for j in range(2):
            lsol_i.append(int(lsol0[i][j]))
        lsol.append(lsol_i)
    array_maze =np.array(lmaze)
    #test of the solution:
    boole0 =True
    k=1
    for j in range(len(lmaze)):
        if array_maze[j][0]==0:
            k+=1
    for j in range(1,k):
        if array_maze[j][1]==lsol[0][1]:
            boole0 =False
    boole1=False
    m=0
    for i in range(len(lsol)-1):
        if (abs(lsol[i+1][0]-lsol[i][0])==1 and abs(lsol[i+1][1]-lsol[i][1])==0) or \
        (abs(lsol[i+1][0]-lsol[i][0])==0 and abs(lsol[i+1][1]-lsol[i][1])==1):
            m+=1
    if m == len(lsol)-1:
        boole1=True
    n=0
    boole2=True
    for i in range(len(lsol)):
        for j in range(1,len(lmaze)):
            if array_maze[j][0]==lsol[i][0] and array_maze[j][1]==lsol[i][1]:
                n+=1
    if n>0:
        boole2=False
    boole3=True
    a=np.zeros(len(lmaze))
    for i in range(len(lmaze)):
        a[i]=array_maze[i][0]
    b=max(a)-1
    for i in range(len(lmaze)):
        if array_maze[i][0]==b:
            if array_maze[i][0]==lsol[len(lsol)-1][0] and array_maze[i][1]==lsol[len(lsol)-1][1]:
                boole3=False
    string=""
    if boole2 and boole1 and boole0 == True:
        string += 'Solution is valid!'
    else:
        string +='Solution is NOT valid!'
    return string

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage:\n $ python checksoln.py [maze file] [solution_to_test file] ") 
        sys.exit()
    if len(sys.argv)==3:        
        st=checksoln(sys.argv[1],sys.argv[2])
        print(st)
