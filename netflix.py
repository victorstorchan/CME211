# coding: utf-8




#finduser outputs a list of 2-dimentional tuple. First entry :the user of the item j, second entry: the rate of the item.

def finduser(j,l):
    my_list1=[]
    m = len(l)
    for i in range(m):
        if l[i][1]== str(j):
            my_list1.append((l[i][0],l[i][2]))
    return my_list1
        



#bothij outputs a list the users who rated both i and j items.
def bothij(i,j,l):
    my_list2=[]
    li=finduser(i,l)
    lj=finduser(j,l)
    for k in range(len(li)):
        for l in range(len(lj)):
            if li[k][0]==lj[l][0]:
                my_list2.append(li[k][0] )
    return my_list2




#moy outputs the average of all ratings for item j: it's m
def moy(j,l):
    k=0
    r=0
    for i in range(len(l)):
        if l[i][1]==str(j):
            k +=1
            r +=int(l[i][2])
    return float(r)/k




#note donnée par la kieme personne de bothij(a,b) à l'item a

def note(k,a,b,l):
    r_ak =0
    for i in range(len(finduser(a,l))):
        if finduser(a,l)[i][0]==bothij(a,b,l)[k]:
            r_ak +=int(finduser(a,l)[i][1])
    return r_ak



#computation of the numerator:
def correll_num(a,b,l):
    r =0
    for k in range(len(bothij(a,b,l))):
        r +=(note(k,a,b,l)-moy(a,l))*(note(k,b,a,l)-moy(b,l))
    return r



#computation of the denominator:
from math import sqrt
def correll_denum(a,b,l):
    r1=0
    r2=0
    for k in range(len(bothij(a,b,l))):
        r1 +=(note(k,a,b,l)-moy(a,l))*(note(k,a,b,l)-moy(a,l))
    for k in range(len(bothij(a,b,l))):
        r2 += (note(k,b,a,l)-moy(b,l))*(note(k,b,a,l)-moy(b,l))
    a=sqrt(r1*r2)
    return a
        



# computation of P_a_b, if correll_denum is null, it raises a exception



def P_a_b(a,b,l):
    try:
        return correll_num(a,b,l)/correll_denum(a,b,l)
    except ZeroDivisionError:
        print("the denominator is null")



def compt_users(l):
    a = set([])
    for i in range(len(l)):
        a.add(l[i][0])
    return len(a)



def compt_movies(l):
    a = set([])
    for i in range(len(l)):
        a.add(l[i][1])
    return (list(a),len(a))



#we put the coefficient correlation in regards of the couple of items in a list. If the denominator is null, P_a_b(a,b)=None

def make_couple_items_correl(l):
    quot =[]
    for i in range(compt_movies(l)[1]):
        for j in range(compt_movies(l)[1]):
            if i!=j:
                quot.append([[compt_movies(l)[0][i],compt_movies(l)[0][j]],P_a_b(compt_movies(l)[0][i],compt_movies(l)[0][j],l)])
    return quot



def funsimilarities(l, defaut):
    list_mov=sorted(compt_movies(l)[0])
    list_final =[]
    for i in range(len(list_mov)):
        f=[]
        for j in range(len(make_couple_items_correl(l))):
            if make_couple_items_correl(l)[j][0][0]==list_mov[i]:
                f.append([make_couple_items_correl(l)[j][0][1],make_couple_items_correl(l)[j][1]]) #dans f, on ajoute l'item comparé à i et son coeff
        g1=[]
        if defaut<len(f):
            for j in range(len(f)):
                g1.append(f[j][1])
            g2 = sorted(g1)
            r0=g2[len(f)-1] #most important coeff corel for item i
            r1= 0
            for j in range(len(f)):
                if r0==f[j][1]:
                    r1 += int(f[j][0]) #r1 is the movie relative to the biggest coeff correl with repect to i
            list_final.append([list_mov[i],[r1,r0,len(f)]])
        else:
            list_final.append([list_mov[i],' '])
    return list_final
        
            



#computation of the line of the file
def compline(MovieLens):
    h = open(MovieLens,'r')
    n=0
    while h.readline():
        n+=1
    h.close()
    return n



#final function: read and write
import time
def ecritsim(MovieLens,similarities,userthresh=5):
    t1=time.time()
    n=compline(MovieLens)
    h = open(MovieLens,'r')
    l=[]
    for i in range(n):
        l.append(h.readline().split())
    h.close()
    my_list = funsimilarities(l,userthresh)
    my_listtup=[]
    for i in range(len(my_list)):
        my_listtup.append([my_list[i][0],tuple(my_list[i][1])])
    g=open(similarities,'w')
    for i in range(len(my_listtup)):
        g.writelines('{} {}\n'.format(my_listtup[i][0],my_listtup[i][1]))
    g.close()
    t2=time.time()
    print('Input MovieLens file:{} \n Output file for similarity data:{}\n Minimum number of common users:{}\n Read {} lines with total of {} movies and {} users \n Computed simiarities in {} seconds '.format(MovieLens,similarities,userthresh,n,list(compt_movies(l))[1],compt_users(l),t2-t1))



ecritsim('/Users/victorstorchan/Desktop/u.data.txt','/Users/victorstorchan/Desktop/similarities.txt')

