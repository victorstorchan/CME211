
# coding: utf-8
# Here we will create a function that processes the manual data
# We open the reference previously manually created:

f = open("/Users/victorstorchan/Desktop/reference0.txt","r")


#we read the reference file
refstring= f.readline().strip()
refstring


# same with reads file

g = open("/Users/victorstorchan/Desktop/reads0.txt","r")



my_list =[]
for i in g:
    my_list.append(i.strip())



my_list



refstring


#here we make the function which compute the number of alignments for each 
#manual reads, and output the list
deflist = []
for i in range(len(my_list)):
    j=0
    r=0
    newlist =[]
    for k in range(0,len(refstring)-2):
        r=0
        for j in range(3):
            if my_list[i][j] == refstring[k+j]:
                r+=1
            else:
                r =0
        if r == 3:
            newlist.append(k)
    if newlist == []:
        newlist.append(-1)
    deflist.append(newlist)



deflist

#now we will write the alignment files, reads, and in front of them, 
#the rank(s) where they align the reference. We create alignments0

h = open("/Users/victorstorchan/Desktop/alignments0_ref.txt","w")



deflist




for i in range(len(my_list)):
    print('{} {}'.format(my_list[i],deflist[i]))



for i in range(len(my_list)):
    h.writelines('{} {}\n'.format(my_list[i],deflist[i]))



h.close()
