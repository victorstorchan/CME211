
# coding: utf-8



import truss
import sys

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Usage:\n $ python main.py [joints file] [beams file] [optional plot output file]")
        sys.exit()
    if len(sys.argv)==3:        
        T=truss.Truss(sys.argv[1],sys.argv[2])
        print(T)
    else:
        T=truss.Truss(sys.argv[1],sys.argv[2])
        print(T)
        T.PlotGeometry(sys.argv[3])

