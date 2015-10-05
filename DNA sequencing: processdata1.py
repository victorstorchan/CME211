# coding: utf-8

# We open the files to reads the data, and we want to create one to write
#the alignments:

reffile = open("/Users/victorstorchan/Desktop/reference3.txt","r")
readsfile=open("/Users/victorstorchan/Desktop/reads3.txt","r")
alignfile=open("/Users/victorstorchan/Desktop/alignments3.txt","a+")
reflength=100000
nreads=60000
readslength=50
list_of_reads =[]
for j in range(nreads):
    list_of_reads.append(readsfile.readline().strip())
ref=reffile.readline().strip()    


# Here, annex is a recursive function and helps to compute the list of the
#alignments of all reads when we will call it :

def annex(j,i,newlist):
    comp =ref.find(j,i)
    if comp!=-1 and i<reflength:
        newlist.append(comp)
        annex(j,comp+1,newlist)
    return newlist   


# Now, we process the data, we record the time of processing and the number
#of each kind of reads:


import time

time0=time.time()

list_align =[]
for j in list_of_reads:
    a = annex(j,0,[])
    list_align.append(a)
for i in range(len(list_align)):
    if list_align[i]==[]:
        list_align[i]=-1
time1=time.time()
k1=0
k2=0
k0=0
for j in range(nreads):
    b=len(annex(list_of_reads[j],0,[]))
    if b==0:
        k0+=1
    elif b==1:
        k1+=1
    else:
        k2+=1
print("align_0 ={}% align_1={}% align_2={}%".format(100*k0/nreads,100*k1/nreads,100*k2/nreads))
print("elapse_time is {}".format(time1-time0))




for i in range(nreads):
    alignfile.writelines('{} {}\n'.format(list_of_reads[i],list_align[i]))




alignfile.close()



