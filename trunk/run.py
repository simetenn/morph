import pylab as p
import time

def run(ScaleDensity,b,f):
    import pylab as p
    import shutil, subprocess
    
    path = "./outData/"
    savepath = "./plots/compare3/"
    inifilename = "mybody.ini"

    filenameMine = "mass.dat"
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

    sortedDataR = p.sort(rockstarData[:,2])[::-1]
    sortedData = p.sort(mineData)[::-1]
    sortedDataA = p.sort(amigaData[:,3])[::-1]


    p.figure()
    p.loglog(sortedData,range(1,len(sortedData)+1))
    p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
    p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
    p.legend(("MORPH","Rockstar","AMIGA"))
    p.xlabel("log(Mass) Msun")
    p.ylabel("log(Nr of halos with mass >= Mass)")
    name = "MassFunction_ScaleDensity="+ str(ScaleDensity) + "_b=" + str(b) + "_f="+str(f)
    p.savefig(savepath+name+".png")
    shutil.move(path+"mass.dat", path +"Mass_Scale="+ str(ScaleDensity) + "_b=" + str(b) + "_f="+str(f) +".dat")


    
def runTime(Particle,Scale):
    import pylab as p
    import shutil, subprocess, time
    
    path = "./outData/"
    savepath = "./plots/compare/"
    inifilename = "mybody.ini"

    filenameMine = "mass.dat"
    filenameRockstar = "rockstar128.dat"
    filenameAmiga = "amiga.dat"
    
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
    t1 = time.time();
    subprocess.call(["mpirun","-n","2", "./MORPH"])
    t2 = time.time();
    """
    mineData = p.loadtxt(path + filenameMine)
    rockstarData = p.loadtxt(path + filenameRockstar)
    amigaData = p.loadtxt(path + filenameAmiga)

    sortedDataR = p.sort(rockstarData[:,2])[::-1]
    sortedData = p.sort(mineData)[::-1]
    sortedDataA = p.sort(amigaData[:,3])[::-1]


    p.figure()
    p.loglog(sortedData,range(1,len(sortedData)+1))
    p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
    p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
    p.legend(("MORPH","Rockstar","AMIGA"))
    p.xlabel("log(Mass) Msun")
    p.ylabel("log(Nr of halos with mass >= Mass)")
    name = "MassFunction_Scale="+ str(Scale) + "_Particles=" + str(Particle)
    p.savefig(savepath+name+".png")

    shutil.move(path+"mass.dat", path +"Mass_Scale="+ str(Scale) + "_Particles=" + str(Particle) + ".dat")
    """
    return t2-t1


def runAll(ScaleDensity, b, f, Particle, Scale):
    import pylab as p
    import shutil, subprocess
    
    path = "./outData/"
    savepath = "./plots/compare/"
    inifilename = "mybody.ini"

    filenameMine = "mass.dat"
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

    sortedDataR = p.sort(rockstarData[:,2])[::-1]
    sortedData = p.sort(mineData)[::-1]
    sortedDataA = p.sort(amigaData[:,3])[::-1]


    p.figure()
    p.loglog(sortedData,range(1,len(sortedData)+1))
    p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
    p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
    p.xlabel("log(Mass) Msun")
    p.ylabel("log(Nr of halos with mass >= Mass)")
    p.legend(("mine","Rockstar","AMIGA"))
    name = "MassFunction_ScaleDensity="+ str(ScaleDensity) + "_b=" + str(b) + "_f="+str(f) + "_Scale=" +str(Scale) + "_Double="+str(double)
    p.savefig(savepath+name+".png")
    


#"""
ScaleDensity = [360]#range(300,400,20)
b = [0.21]#p.linspace(0.2,0.3,11)
f = p.linspace(0.5,0.9,5)
runs = len(ScaleDensity)*len(b)*len(f)
count = 1.


#"""
file = open("times.dat","w")
file.write("f   Time\n")

for i in ScaleDensity:
    for j in b:
        for k in f:
            print "__________________________________________"
            print
            print str(count/runs*100)+"%"
            print "__________________________________________"
            t1 = time.time();
            run(i,j,k)
            t2 = time.time();
            
            string = str(k) + "   " + str(t2-t1)+"\n"
            file.write(string)
            
            count += 1
                    
"""

Scales = range(1,7)#range(300,400,20)
Particles = range(10,101,10)
runs = len(Scales)*len(Particles)
count = 1.
results = p.zeros((3,runs))
print "__________________________________________"

f = open("times.dat","w")
f.write("Nr   Scale   Time\n")

for i in Particles:
    for j in Scales:
        print str(count/runs*100)+"%"
        time = runTime(i,j)
        string = str(i) + "   " + str(j) + "   " + str(time)+"\n"
        f.write(string)
        count += 1
print "__________________________________________"
"""
file.close()
#run(ScaleDensity[0],b[0],f[0])
