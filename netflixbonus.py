def funsimilarities(l, nmax, defaut):
    list_mov=sorted(compt_movies(l)[0])
    list_final =[]
    for i in range(len(list_mov)):
        f=[]
        l0=[]
        l1=[]
        l2=[]
        for j in range(len(make_couple_items_correl(l))):
            if make_couple_items_correl(l)[j][0][0]==list_mov[i]:
                f.append([make_couple_items_correl(l)[j][0][1],make_couple_items_correl(l)[j][1]]) #dans f, on ajoute l'item comparé à i et son coeff
        g1=[]
        if defaut<len(f):
            for j in range(len(f)):
                g1.append(f[j][1])
            g2 = sorted(g1)
            for k in range(nmax):
                l0.append(g2[len(g2)-k-1]) #list of most important coeffs corel for item i
            for k in range(len(l0)):
                for j in range(len(f)):
                    if l0[k]==f[j][1]:
                        l1.append(int(f[j][0])) #l1 is the movies relative to the nmax-biggest coeffs correl with repect to i
            for k in range(len(l1)):
                l2.append([l1[k],l0[k],len(bothij(list_mov[i],l1[k],l))])
            list_final.append([list_mov[i],l2])
        else:
            list_final.append([list_mov[i],' '])
    return list_final
        
