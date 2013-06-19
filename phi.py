import pylab as p

path = "./outData/"
filename = "tmpPhi"


#for x in data[:,0]:
 #   print x
#Revert these two
for i in range(0,3):
    data = p.loadtxt(path + filename + str(i))
    p.figure(1)
    p.plot(data[:,0], data[:,1])
    p.hold("on")
p.show()
