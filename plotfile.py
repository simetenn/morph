import pylab as p
import sys
path = "/home/simen/Master/mybody-mpi/outData/"
filename = sys.argv[1]

data = p.loadtxt(path + filename)

p.plot(data)
#p.ylim([-1,1])
p.show()
