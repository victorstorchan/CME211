# coding: utf-8



import math
import numpy as np
import matplotlib.pylab as plt
from scipy.sparse import csr_matrix
import scipy.sparse.linalg
#%matplotlib inline
#%config InlineBackend.figure_format = 'svg'



class Truss:
    def __init__(self, names_joints,names_beams):
        self.LoadData(names_joints,names_beams)
        
    def LoadData(self,names_joints,names_beams):
        list_of_joints0 =[]
        h = open(names_joints,'r')
        for line in h:
            list_of_joints0.append(line.split())
        h.close()
        n=len(list_of_joints0)
        self.list_of_joints=[]
        for i in range(1,n):
            self.list_of_joints.append(list_of_joints0[i])
        list_of_beams0 =[]
        g = open(names_beams,'r')
        for line in g:
            list_of_beams0.append(line.split())
        g.close()
        m=len(list_of_beams0)
        self.list_of_beams=[]
        for i in range(1,m):
            self.list_of_beams.append(list_of_beams0[i])
        return self.list_of_joints,self.list_of_beams
                
    def get_num_lists(self):
        (j,b)= (self.list_of_joints,self.list_of_beams)
        l=[]
        g=[]
        for i in range(len(j)):
            h=[]
            for k in range(len(j[i])):
                h.append(float(j[i][k]))
            l.append(h)
        for i in range(len(b)):
            h=[]
            for k in range(len(b[i])):
                h.append(int(b[i][k]))
            g.append(h)
        return l,g
        
                
        
    def decide_link_ij(self,k,l):#decide if the points i and j are linked
        (j,b)= (self.list_of_joints,self.list_of_beams)
        boole=False
        for i in range(len(b)):
            if (int(b[i][1])==k and int(b[i][2])==l) or (int(b[i][1])==l and int(b[i][2])==k):
                boole=True
        return boole
    
    def PlotGeometry(self,output_file ):
        (joint,b)= (self.list_of_joints,self.list_of_beams)
        matrix_link=np.zeros((len(joint),len(joint))) 
        for i in range(len(b)):
            matrix_link[int(b[i][1])-1,int(b[i][2])-1]=1
            matrix_link[int(b[i][2])-1,int(b[i][1])-1]=1#matrix_link(i,j) equal 1 means link between i and j.
        plt.figure()
        for i in range(len(joint)):
            for j in range(len(joint)):
                if matrix_link[i,j]==1:
                    x=[float(joint[j][1]),float(joint[i][1])]
                    y=[float(joint[j][2]),float(joint[i][2])]
                    plt.plot(x,y,'b')
        if len(joint)==5:
            plt.xlim(-1, 16)
            plt.ylim(-1, 9)
            plt.savefig(output_file)    
            plt.show()
        else:
            plt.xlim(-1, 4)
            plt.ylim(-1, 3)
            plt.savefig(output_file)    
            plt.show()

    def angle(self,a,b,c,d):#in the order: coordinate of the first point and of the second point of the beam
        (cos,sin)= (abs((c-a)/math.sqrt((c-a)**2+(d-b)**2)),abs((d-b)/math.sqrt((c-a)**2+(d-b)**2)))
        return (round(cos,3),round(sin,3))
        
    def info_connexion_j(self,j):#il faut vraiment avoir 12 inconnues, 1 par beam en fait. Donc on garde la forme de l avec 
                                 #l[ , , ]= le num de la connexion, la force selon l'axe des x, la force selon l'axe des y.
        (joint,b)= self.get_num_lists()
        l=[]
        for i in range(len(b)):
            (c,s)=self.angle(joint[b[i][1]-1][1],joint[b[i][1]-1][2],joint[b[i][2]-1][1],joint[b[i][2]-1][2])
            if int(b[i][1])==j:
                if joint[b[i][2]-1][1]-joint[b[i][1]-1][1]>0 and joint[b[i][2]-1][2]-joint[b[i][1]-1][2]>0:
                    l.append([i,-c,-s])#il faut calculer l'angle dès que les deux sont différents de 0.
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])<0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])>0:
                    l.append([i,c,-s])#il faut calculer l'angle dès que les deux sont différents de 0.
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])>0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])<0:
                    l.append([i,-c,s])#il faut calculer l'angle dès que les deux sont différents de 0.
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])<0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])<0:
                    l.append([i,c,s])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])==0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])<0:
                    l.append([i,0,1])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])==0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])>0:
                    l.append([i,0,-1])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])==0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])==0:
                    l.append([i,0,0])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])>0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])==0:
                    l.append([i,-1,0])
                else:
                    l.append([i,1,0])
            elif int(b[i][2])==j:
                if float(joint[b[i][2]-1][1])-float(joint[b[i][1]-1][1])>0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])>0:
                     l.append([i,c,s])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])<0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])>0:
                    l.append([i,-c,s])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])>0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])<0:
                    l.append([i,c,-s])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])<0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])<0:
                    l.append([i,-c,-s])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])==0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])<0:
                     l.append([i,0,-1])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])==0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])>0:
                    l.append([i,0,1])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])==0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])==0:
                   l.append([i,0,0])
                elif float(joint[b[i][2]-1][1]-joint[b[i][1]-1][1])>0 and float(joint[b[i][2]-1][2]-joint[b[i][1]-1][2])==0:
                    l.append([i,1,0])
                else:
                     l.append([i,-1,0])
            else:
                l.append([-1,0,0])
        return l
       
    def info_row_j(self,j):#number of time we will have to enter the number j-1 in the row info of the matrix
        (joint,b)= self.get_num_lists()
        l=self.info_connexion_j(j)
        k=0
        s=0
        for i in range(len(l)):
            if l[i][0]!=-1 and l[i][1]!=0:
                k+=1
        for i in range(len(l)):
            if l[i][0]!=-1 and l[i][2]!=0:
                s+=1
        if joint[j-1][5]==1:
            k+=1
            s+=1
        return k,s
    def info_columns_j(self,k):
        f=[] #columns of the first equation of noeud k
        g=[] #columns of the second equation of noeud k
        (joint,b)= self.get_num_lists()
        l=self.info_connexion_j(k)
        for j in range(len(b)):
            if l[j][0]!=-1:
                if l[j][1]!=0:
                    f.append(j)
        for j in range(len(b)):
            if l[j][0]!=-1:
                if l[j][2]!=0:
                    g.append(j)
        return f,g
    def add_reaction(self,k):
        (joint,b)= self.get_num_lists()
        nb_reaction=0
        for j in range(len(b)):       
            if joint[1-1][5]==1:
                nb_reaction+=1
        d=0
        l=[]
        m=[]
        for j in range(len(joint)):
            (f,g)=self.info_columns_j(j+1)
            if joint[j][5]==1:
                f.append(len(b)+d)
                g.append(len(b)+d+1)
                d+=2
            l.append(f)
            m.append(g)
        return l[k-1],m[k-1]
        
    
    def make_row(self):
        (joint,b)= self.get_num_lists()
        l=[]
        for j in range(len(joint)):
            (f,g)=self.info_row_j(j+1)
            for i in range(f):
                l.append(2*j)
            for i in range(g):
                l.append(2*j+1)
        return l
    def make_columns(self):
        (joint,b)= self.get_num_lists()
        l=[]
        for j in range(len(joint)):
            (a,b)= self.add_reaction(j+1)
            for i in range(len(a)):
                l.append(a[i])
            for i in range(len(b)):
                l.append(b[i])
                 
        return l
    
    def make_data(self):
        (joint,b)= self.get_num_lists()
        l=[]
        for j in range(1,len(joint)+1):
            for i in range(len(self.info_connexion_j(j))):
                if self.info_connexion_j(j)[i][0]!=-1:
                    if self.info_connexion_j(j)[i][1] !=0:
                        l.append(self.info_connexion_j(j)[i][1])
            if joint[j-1][5]==1:
                l.append(1)
            for i in range(len(self.info_connexion_j(j))):
                if self.info_connexion_j(j)[i][0]!=-1:
                    if self.info_connexion_j(j)[i][2] !=0:
                        l.append(self.info_connexion_j(j)[i][2])
            if joint[j-1][5]==1:
                l.append(1)
                    
        return l
    
    def make_sparse_matrix_CSR(self):
        (joint,B)= self.get_num_lists()
        row = np.array(self.make_row())
        col = np.array(self.make_columns())
        data = np.array(self.make_data())
        k=2*len(joint)
        mtx = csr_matrix((data, (row, col)), shape=(k, k))
        return mtx
    def make_vector_b(self):
        (joint,B)= self.get_num_lists()
        b= np.zeros(2*len(joint))
        for j in range(len(joint)):
            b[2*j]= -joint[j][3]
            b[2*j+1]= -joint[j][4]
        return b
    def solve_sparse_system(self):
        x=scipy.sparse.linalg.spsolve(self.make_sparse_matrix_CSR(),self.make_vector_b())
        return x
        
    def __repr__(self):
        (joint,B)= self.get_num_lists()
        k=0
        for i in range(len(joint)):
            if joint[i][5]==1:
                k+=1
        nb_unknowns= 2*k+len(B)
        nb_equations=2*len(joint)
        if nb_unknowns!=nb_equations:
            raise RuntimeError('Truss geometry not suitable for static equilbrium analysis')
        elif np.linalg.det(self.make_sparse_matrix_CSR().todense())==0:
            raise RuntimeError('Cannot solve the linear system, unstable truss?')
        else:
            string = '  Beam       Force\n -----------------\n'
            for i in range(len(B)):
                string+='  %d          %.3f\n'%(i+1, self.solve_sparse_system()[i])
            return string
    







