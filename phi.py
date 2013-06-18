import pylab as p

path = "/home/simen/Master/mybody-mpi/data/"
filename = "Phi6.dat"

data = p.loadtxt(path + filename)

#for x in data[:,0]:
 #   print x
p.plot(data[:,1],data[:,0])
p.show()
