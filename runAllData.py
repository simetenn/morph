def run(name, method):
    import pylab as p
    import shutil, subprocess
    
    path = "./outData/"
    inifilename = "mybody.ini"
    
    inifile = open(inifilename, 'r')
    tmpinifile = open(inifilename + ".tmp", "w")

    for line in inifile:
        if line[0:18] == "unbindingMethod = ":
            line = "unbindingMethod = " + str(method)+"\n "
            
        tmpinifile.write(line)
    
    inifile.close()
    tmpinifile.close()
    shutil.move(inifilename + ".tmp", inifilename)

    #Run my halofinder
    #print "Running for: " +"ScaleDensity="+ str(ScaleDensity) + " b=" + str(b) + " f="+str(f)
    subprocess.call(["mpirun","-n","32", "./MORPH"])
    
    #Read data from files
    filename = "Mass_" + name[:-4] + "_UnbindingMethod=" + str(method)
    shutil.move(path + "mass.dat", path + filename + ".dat")




names = ["lcdm1.bin"]

for name in names:
    for method in range(4):
        run(name,method)
    
