import pylab as p
import sys

path = "./outData/"
filename = "Phi0.dat"


#for x in data[:,0]:
#   print x
#Revert these two
#for i in range(0,int(sys.argv[1])):
data = p.loadtxt(path + filename)
                #p.figure(1)
p.plot(data[:,1], data[:,0])
p.xlabel("Radius from halo center [Mpc/h]")
p.ylabel("Gravitational potential [Mpc^2/Gyr^2]")
    #p.hold("on")
p.show()
