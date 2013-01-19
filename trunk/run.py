import pylab as p

def run(ScaleDensity,b,f):
    import pylab as p
    import shutil, subprocess
    
    path = "/home/simen/Master/mybody-mpi/data/"
    savepath = "/home/simen/Master/mybody-mpi/plots/compare/"
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



    p.loglog(sortedData,range(1,len(sortedData)+1))
    p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
    p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
    p.legend(("mine","Rockstar","AMIGA"))
    name = "MassFunction_ScaleDensity="+ str(ScaleDensity) + "_b=" + str(b) + "_f="+str(f)
    p.savefig(savepath+name+".png")


ScaleDensity = range(300,400,10)
b = p.linspace(0.18,0.3,12)
f = p.linspace(0.4,0.9)

runs = len(ScaleDensity)*len(b)*len(f)
count = 1.
""""for i in ScaleDensity:
    for j in n:
        for k in f:
            print str(count/runs*100)+"%"
            run(i,j,k)
            count += 1"""
run(ScaleDensity[0],b[0],f[0])
