import pylab as p
import sys

path = "./outData/"
filenameMine = "mass.dat"


filenameRockstar = sys.argv[1]
#filenameAmiga = sys.argv[2]#"amiga.dat"
#Read data from files

data = []

rockstarData = p.loadtxt(path + filenameRockstar)
#amigaData = p.loadtxt(path + filenameAmiga)

data.append(p.sort(rockstarData[:,2])[::-1])
#data.append(p.sort(amigaData[:,3])[::-1])


for file in sys.argv[2:]:
    tmpData = p.loadtxt(path + str(file))
    data.append(p.sort(tmpData)[::-1])


for x in data:
    p.loglog(x,range(1,len(x)+1))

#names = ["Rockstar","Amiga","MORPH, f=0.5","MORPH, f=0.6","MORPH, f=0.7","MORPH, f=0.8","MORPH, f=0.9"]
names = ["Rockstar"]
p.xlabel("log(Mass) Msun")
p.ylabel("log(Nr of halos with mass >= Mass)")
for file in sys.argv[3:]:
    names.append(str(file[:-4]))

p.legend(names)

p.show()
