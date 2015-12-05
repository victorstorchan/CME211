import sys
import matplotlib.pyplot as plt
import numpy as np

def find_nearest(array,value):
    idx = (np.abs(array-value)).argmin()
    return idx


def process (inputfile_data,inputfile_solver):
    h0 = open(inputfile_data,'r')
    l=[]
    for line in h0:
        l.append(line.split())
    h0.close()
    length=float(l[0][0])
    wid=float(l[0][1])
    h=float(l[0][2])
    y, x = np.mgrid[slice(0,wid + h, h),
                slice(0, length + h, h)]
    
    g=open(inputfile_solver,'r')
    m=[]
    for line in g:
        m.append(line.split())
    g.close()
    m2=np.zeros(len(m))
    for i in range(len(m)):
        m2[i]=float(m[i][0])
    m3=list(reversed(m2))
    z=np.zeros(len(m2))
    z[:]=m3[:]
    z1=np.reshape(z,(wid/h-1,length/h))
    z2=np.transpose(z1)
    z3=[]
    for i in range(1,int(wid/h)-1):
        z3.append(z2[0][i])
    r=np.add.accumulate(z3)#we will add twice the periodic nodes
    s=0
    for i in range(int(wid/h)-1):
        for j in range(int(length/h)-1):
            s+=z1[i][j]
    s+=r[len(r)-1]
    mean= float(s)/(wid/h-2+(wid/h-1)*length/h)
    
    y_iso=[]
    x_iso=np.linspace(0,int(length),int(length/h))
    for i in range(int(length/h)):
        y_iso.append(find_nearest( z2[i], mean )*h)

    x= np.linspace(0, length, num=length/h)
    y=np.linspace(0,wid,num=wid/h-1)
    plt.pcolor(x,y,z1)
    plt.plot(x_iso,y_iso,'k-')
    plt.colorbar()
    plt.axis([0, length, -wid, 2*wid])
    plt.show()
    return mean
    
if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage:\n $ python checksoln.py [inputx.txt] [solution<#>.txt] ") 
        sys.exit()
    if len(sys.argv)==3:        
        a=process(sys.argv[1],sys.argv[2])
        print('Input file processed:{}'.format(sys.argv[1]))
        print('Mean Temperature:{}'.format(a))
        





