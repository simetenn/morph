import pylab as p
import sys

path = "./outData/"
filename = "Phi"


#for x in data[:,0]:
#   print x
#Revert these two
for i in range(0,int(sys.argv[1])):
    data = p.loadtxt(path + filename + str(i) + ".dat")
                #p.figure(1)
    p.plot( data[:,1], data[:,0])
    #p.hold("on")
    p.show()
