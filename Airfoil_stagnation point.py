# coding: utf-8


import glob

import os.path

import math

class Airfoil:
    def __init__(self, inputdir):
        self.LoadData(inputdir)
        
    def LoadData(self, inputdir):
        inputdir+='/*'
        self.lxy0=[]
        self.lxy=[]
        self.lalpha0=[]
        self.Lcp=[]
        l=glob.glob(inputdir)
        for i in range(len(l)):
            if len(os.path.splitext(os.path.split(l[i])[1])[0])<8:
                h =open(l[i],'r')
                n=0
                while h.readline():
                    n+=1
                h.close()
                h =open(l[i],'r')
                for i in range(n):
                    self.lxy0.append(h.readline().split())
                h.close()
                for i in range(1,len(self.lxy0)):
                    self.lxy.append(self.lxy0[i])
            else:
                self.lalpha0.append(os.path.splitext(os.path.split(l[i])[1])[0][5:7])
                for i in range(len(self.lalpha0)):
                    if self.lalpha0[i]=='0.':
                        self.lalpha0[i]='0'
                h =open(l[i],'r')
                n=0
                while h.readline():
                    n+=1
                h.close()
                h =open(l[i],'r')
                lcp=[]
                for j in range(n):
                    lcp.append(h.readline().split())
                h.close()
                lcp1=[]
                for i in range(1,len(lcp)):
                    lcp1.append(lcp[i])
                self.Lcp.append(lcp1)
                
    
        
    def getlxy(self):
        l=[]
        for i in range(len(self.lxy)):
            l.append([float(self.lxy[i][0]),float(self.lxy[i][1])])
        return l
    
    def getalpha(self):
        l=[]
        for i in range(len(self.lalpha0)):
            l.append(int(self.lalpha0[i]))
        return l
    def getLcp(self):
        l=[]
        for i in range(len(self.Lcp)):
            g=[]
            for j in range(len(self.Lcp[i])):
                g.append(float(self.Lcp[i][j][0]))
            l.append(g)
        return l
    
    def computchord(self):
        lx=[]
        for i in range(len(self.getlxy())):
            lx.append(self.getlxy()[i][0])
        lxsor=sorted(lx)
        chord=lxsor[len(lxsor)-1]-lxsor[0]
        return chord
    
    def computliftforce_delta(self,alpha):
        k=0
        for i in range(len(self.getalpha())):
            if alpha==self.getalpha()[i]:
                k=i
        ldcx=[]
        ldcy=[]
        for i in range(len(self.getlxy())-1):
            if self.getlxy()[i+1][0]-self.getlxy()[i][0]>0:
                ldcx.append(self.getLcp()[k][i]*(self.getlxy()[i+1][0]-self.getlxy()[i][0])/self.computchord())
            else:
                ldcx.append(self.getLcp()[k][i]*(-self.getlxy()[i+1][0]+self.getlxy()[i][0])/self.computchord())
        for i in range(len(self.getlxy())-1):
            if self.getlxy()[i+1][1]-self.getlxy()[i][1]>0:
                ldcy.append(self.getLcp()[k][i]*(self.getlxy()[i+1][1]-self.getlxy()[i][1])/self.computchord())
            else:
                ldcy.append(self.getLcp()[k][i]*(-self.getlxy()[i+1][1]+self.getlxy()[i][1])/self.computchord())    
        return ldcx,ldcy
    
   
    
    def computliftforce(self,alpha):
        (ldcx,ldcy)=self.computliftforce_delta(alpha)
        l=0
        g=0
        for i in range(len(ldcx)):
            l+=ldcx[i]
        for i in range(len(ldcy)):
            g+=ldcy[i]
        ct=g*math.cos(alpha)-l*math.sin(alpha)
        return ct
    
    def stagnation_point(self,alpha):
        k=0
        for i in range(len(self.getalpha())):
            if alpha==self.getalpha()[i]:
                k=i
        l=sorted(self.getLcp()[k])
        x = l[len(l)-1]
        for i in range(len(self.getLcp()[k])):
            if self.getLcp()[k][i]==x:
                c = i
        (a,b)=self.getlxy()[c]
            
        return (a,b),x
    def __repr__(self):
        string = '  alpha      cl                stagnation point\n ------ -------          ------------------\n '
        for i in range(len(self.getalpha())):
            string+= '{}    '.format(self.getalpha()[i])
            string+='{}   '.format(round(self.computliftforce(self.getalpha()[i]),5))
            string+='{}\n'.format(self.stagnation_point(self.getalpha()[i]))
        return string



s =Airfoil('/Users/victorstorchan/Desktop/cme211-hw3-files-1/naca0012')



print(s)

