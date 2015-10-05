# coding: utf-8

# Here we will write the data we need: reads and reference:

reffile='reference3.txt'
readsfile='reads3.txt'
reflength=100000
nreads=60000
readslength=50
reffiledata= open("/Users/victorstorchan/Desktop/reference3.txt","w")
readsfiledata=open("/Users/victorstorchan/Desktop/reads3.txt","w")


# assignletter convert a random number (n will be random when we'll
#call assign, and convert it into a letter):

def assignletter(n):
    if n == 0:
        return 'A'
    elif n ==1:
        return 'C'
    elif n ==2:
        return'G'
    else:
        return 'T'


# To respect the proportions of the different kind of reads, we proceed 
#as the instructions says to do. Decide_align decide what type of reads 
# we want to create:

def decide_align(x):
    if x<=0.75:
        return 1
    elif x>0.75 and x<=0.9:
        return 0
    else:
        return 2
        


# Now we create the reference:

import random

refpart=""
for i in range(reflength*3/4):
    refpart += assignletter(random.randint(0,3))

refgoodlength= refpart+refpart[(reflength*3/4-reflength/4):]
reffiledata.write("{}\n".format(refgoodlength))
reffiledata.close()




len(refgoodlength)





#now, we write the data into the different files, using our functions
# decide_align and assignletter:

import string
import random
def createdata(y):
    k1=0
    k2=0
    k0=0
    for i in range(y):
        l=decide_align(random.random())
        if l ==1:
            k1 +=1
            alea1=random.randint(1,reflength/2)
            copy_ref1=refgoodlength[alea1:alea1+readslength]
            readsfiledata.write("{}\n".format(copy_ref1))
        elif l==2:
            k2 +=1
            alea2=random.randint(reflength*3/4,reflength-readslength)
            copy_ref2=refgoodlength[alea2:alea2+readslength]
            readsfiledata.write("{}\n".format(copy_ref2))
        else:
            r=0
            randomreads=""
            while r != -1:
                for i in range(readslength):
                    randomreads += assignletter(random.randint(0,3))
                r=string.find(refgoodlength,randomreads)
            k0 +=1
            readsfiledata.write("{}\n".format(randomreads))
    print("align_0={}%, align_1={}%, align_2={}%".format(100*k0/nreads,100*k1/nreads,100*k2/nreads))




createdata(nreads)




readsfiledata.close()






