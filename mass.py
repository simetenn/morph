import pylab as p
import sys

path = "./outData/"
filenameMine = "mass.dat"


filenameRockstar = "halos_0.ascii"
filenameAmiga = "amiga.dat"
#Read data from files

data = []

rockstarData = p.loadtxt(path + filenameRockstar)
amigaData = p.loadtxt(path + filenameAmiga)

data.append(p.sort(rockstarData[:,2])[::-1])
data.append(p.sort(amigaData[:,3])[::-1])


for file in sys.argv[1:]:
    tmpData = p.loadtxt(path + str(file))
    data.append(p.sort(tmpData)[::-1])


for x in data:
    p.loglog(x,range(1,len(x)+1))

names = ["Rockstar","AMIGA"]
for file in sys.argv[1:]:
    names.append(str(file[:-4]))

p.legend(names)

p.show()
