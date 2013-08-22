import pylab as p

def run(ScaleDensity,b,f):
    import pylab as p
    import shutil, subprocess
    
    path = "/outData/"
    savepath = "./plots/compare/"
    inifilename = "mybody.ini"

    filenameMine = "size.dat"
    filenameRockstar = "rockstar128.dat"
    filenameAmiga = "amiga.dat"

    
    inifile = open(inifilename, 'r')
    tmpinifile = open(inifilename + ".tmp", "w")

    for line in inifile:
    
        if line[0:15] == "ScaleDensity = ":
            line = "ScaleDensity = "+ str(ScaleDensity)+"\n "
        if line[0:4] == "b = ":
            line = "b = " + str(b)+"\n " 
        if line[0:4] == "f = ":
            line = "f = " + str(f)+"\n "
        
        tmpinifile.write(line)
    
    inifile.close()
    tmpinifile.close()
    shutil.move(inifilename + ".tmp", inifilename)

    #Run my halofinder
    #print "Running for: " +"ScaleDensity="+ str(ScaleDensity) + " b=" + str(b) + " f="+str(f)
    subprocess.call(["mpirun","-n","2", "./MORPH"])
    
    #Read data from files
    mineData = p.loadtxt(path + filenameMine)
    rockstarData = p.loadtxt(path + filenameRockstar)
    amigaData = p.loadtxt(path + filenameAmiga)

    sortedDataR = p.sort(rockstarData[:,1])[::-1]
    sortedData = p.sort(mineData)[::-1]
    sortedDataA = p.sort(amigaData[:,4])[::-1]


    p.figure()
    p.loglog(sortedData,range(1,len(sortedData)+1))
    p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
    p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
    p.legend(("mine","Rockstar","AMIGA"))
    name = "MassFunction_ScaleDensity="+ str(ScaleDensity) + "_b=" + str(b) + "_f="+str(f)
    p.savefig(savepath+name+".png")



    
def runTime(Particle,Scale):
    import pylab as p
    import shutil, subprocess, time
    
    path = "/home/simen/Master/mybody-mpi/data/"
    savepath = "/home/simen/Master/mybody-mpi/"
    inifilename = "mybody.ini"
    
    inifile = open(inifilename, 'r')
    tmpinifile = open(inifilename + ".tmp", "w")

    for line in inifile:
    
        if line[0:21] == "LinkingLenghtScale = ":
            line = "LinkingLenghtScale = "+ str(Scale)+"\n "
        if line[0:20] == "NrParticlesDouble = ":
            line = "NrParticlesDouble = " + str(Particle)+"\n " 
       
        tmpinifile.write(line)
    
    inifile.close()
    tmpinifile.close()
    shutil.move(inifilename + ".tmp", inifilename)

    #Run my halofinder
    #print "Running for: " +"ScaleDensity="+ str(ScaleDensity) + " b=" + str(b) + " f="+str(f)
    t1 = time.clock();
    subprocess.call(["mpirun","-n","2", "./main"])
    t2 = time.clock();
    
    return t2-t1


def runAll(ScaleDensity, b, f, Particle, Scale):
    import pylab as p
    import shutil, subprocess
    
    path = "./outData/"
    savepath = "./plots/compare/"
    inifilename = "mybody.ini"

    filenameMine = "size.dat"
    filenameRockstar = "halos_0.ascii"
    filenameAmiga = "amiga.dat"

    
    inifile = open(inifilename, 'r')
    tmpinifile = open(inifilename + ".tmp", "w")

    for line in inifile:
    
        if line[0:15] == "ScaleDensity = ":
            line = "ScaleDensity = "+ str(ScaleDensity)+"\n "
        if line[0:4] == "b = ":
            line = "b = " + str(b)+"\n " 
        if line[0:4] == "f = ":
            line = "f = " + str(f)+"\n "
        if line[0:21] == "LinkingLenghtScale = ":
            line = "LinkingLenghtScale = "+ str(Scale)+"\n "
        if line[0:20] == "NrParticlesDouble = ":
            line = "NrParticlesDouble = " + str(Particle)+"\n " 
            
        tmpinifile.write(line)
    
    inifile.close()
    tmpinifile.close()
    shutil.move(inifilename + ".tmp", inifilename)

    #Run my halofinder
    #print "Running for: " +"ScaleDensity="+ str(ScaleDensity) + " b=" + str(b) + " f="+str(f)
    subprocess.call(["mpirun","-n","2", "./main"])
    
    #Read data from files
    mineData = p.loadtxt(path + filenameMine)
    rockstarData = p.loadtxt(path + filenameRockstar)
    amigaData = p.loadtxt(path + filenameAmiga)

    sortedDataR = p.sort(rockstarData[:,1])[::-1]
    sortedData = p.sort(mineData)[::-1]
    sortedDataA = p.sort(amigaData[:,4])[::-1]


    p.figure()
    p.loglog(sortedData,range(1,len(sortedData)+1))
    p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
    p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
    p.legend(("mine","Rockstar","AMIGA"))
    name = "MassFunction_ScaleDensity="+ str(ScaleDensity) + "_b=" + str(b) + "_f="+str(f) + "_Scale=" +str(Scale) + "_Double="+str(double)
    p.savefig(savepath+name+".png")



ScaleDensity = [360]#range(300,400,20)
b = p.linspace(0.2,0.3,12)
f = p.linspace(0.5,0.9,4)
Scales = range(1,7)#range(300,400,20)
Particles = range(10,51,5)
runs = len(ScaleDensity)*len(b)*len(f)*len(Scales)*len(Particles)
count = 1.



for i in ScaleDensity:
    for j in b:
        for k in f:
            for l in Particles:
                for m in Scales:
                    print "__________________________________________"
                    print
                    print str(count/runs*100)+"%"
                    print "__________________________________________"
                    runAll(i,j,k,l,m)
                    count += 1
                    
"""

Scales = range(1,7)#range(300,400,20)
Particles = range(10,51,5)
runs = len(Scales)*len(Particles)
count = 1.
results = p.zeros((3,runs))
print "__________________________________________"

f = open("times.dat","w")
f.write("Nr   Scale   Time\n")

for i in Particles:
    for j in Scales:
        print str(count/runs*100)+"%"
        string = str(i) + "   " + str(j) + "   " + str(0)+"\n"
        f.write(string)
        count += 1
print "__________________________________________"
""""
f.close()
#run(ScaleDensity[0],b[0],f[0])
