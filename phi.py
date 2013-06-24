import pylab as p

path = "./outData/"
filename = "Phi6.dat"


#for x in data[:,0]:
#   print x
#Revert these two
#for i in range(0,3):
data = p.loadtxt(path + filename)
                 #p.figure(1)
p.plot( data[:,1], data[:,0])
p.hold("on")
p.show()
