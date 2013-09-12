import pylab as p
import sys
path = "./"#"outData/"
filename = sys.argv[1]

data = p.loadtxt(path + filename)
print data[:,1]
p.plot(data[:,0],data[:,1])
p.xlabel("f")
p.ylabel("time");
#p.ylim([-1,1])
p.show()
