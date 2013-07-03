import pylab as p

path = "/home/simen/Master/mybody-mpi/outData/"
filenameMine = "mass.dat"
filenameRockstar = "halos_0.ascii"
filenameAmiga = "amiga.dat"
#Read data from files
mineData = p.loadtxt(path + filenameMine)
rockstarData = p.loadtxt(path + filenameRockstar)
amigaData = p.loadtxt(path + filenameAmiga)

sortedDataR = p.sort(rockstarData[:,2])[::-1]
sortedData = p.sort(mineData)[::-1]
sortedDataA = p.sort(amigaData[:,3])[::-1]


#print sortedData
#p.hist(sortedDataR,bins=100)
#p.hist(sortedData,bins=100)
p.loglog(sortedData,range(1,len(sortedData)+1))
p.loglog(sortedDataR,range(1,len(sortedDataR)+1))
p.loglog(sortedDataA,range(1,len(sortedDataA)+1))
#p.axis([0,9000,0,500])
p.legend(("mine","Rockstar","AMIGA"))
##p.hist(p.log(rockstarData[:,1]),bins=100)
#p.hist(mineData,bins=100)
p.show()
