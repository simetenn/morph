import subprocess, sys, time, pylab, numpy

N = 2;

def getMemory():
    p = subprocess.Popen(["ps", "-C", "MORPH", "v"], stdout=subprocess.PIPE, 
                                       stderr=subprocess.PIPE)
    out, err = p.communicate()
    data = out.split()
    #if len(data) > 10:
    return numpy.array(data[18:-1:10]).astype(float)
    #else:
    #    return -1
    
 
p = subprocess.Popen(["mpirun", "-n", str(N), "./MORPH"])

data = []
try:
    deltaT = float(sys.argv[1])
except:
    deltaT = 1
t = []
i = 0
while p.poll() == None:
    tmpdata = getMemory();
    if len(tmpdata) > 0:
        data.append(getMemory())
        time.sleep(deltaT)
        t.append(i*deltaT)
    i +=1

#dataArray = numpy.zeros((N,len(data)))
#i = 0
#for array in data:
#    for j in range(N):
#        dataArray[j][i] = array[j]
#    i+=1

data = numpy.array(data[:-1])
t = numpy.array(t[:-1])
legend = []

numpy.save("memory", data)
numpy.save("time", t)


pylab.figure(1)
pylab.plot(t,data[:,0])
pylab.xlabel("Time [s]")
pylab.ylabel("% Memory usage")
pylab.savefig("master.png")

pylab.figure(2)
for i in xrange(1,N):
    pylab.plot(t,data[:,i])
    legend.append("Processor nr: " + str(i))

#pylab.plot(t,data[:,1])
pylab.legend(legend,loc=2)

pylab.xlabel("Time [s]")
pylab.ylabel("% Memory usage")
pylab.savefig("slaves.png")

