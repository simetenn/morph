import pylab as p

path = "./outData/"
filenameMine = "size.dat"
#Read data from files
mineData = p.loadtxt(path + filenameMine)

sortedData = p.sort(mineData)[::-1]


#print sortedData
#p.hist(sortedDataR,bins=100)
#p.hist(sortedData,bins=100)
p.loglog(sortedData,range(1,len(sortedData)+1))
#p.axis([0,9000,0,500])
#p.legend(("mine","Rockstar","AMIGA"))
##p.hist(p.log(rockstarData[:,1]),bins=100)
#p.hist(mineData,bins=100)
p.show()
