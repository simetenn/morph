import pylab as p
#import scipy.signal
import scipy.ndimage.filters
import scipy.interpolate

path = "./outData/"
savepath = "./plots/compare/"

datasett = ["lcdm1.bin"]#,"symm_A.bin", "symm_B.bin", "symm_C.bin", "symm_D.bin"]
#datasett = ["fofr4.bin", "fofr5.bin", "fofr6.bin"]
nrBins = 1000
NrParticles = 20
sigma = 2

method = 2


legendnames = []
for n in datasett:
    legendnames.append(n[:-4])



for name in datasett:
    MData = p.loadtxt(path + "Mass_" + name[:-4] + "_UnbindingMethod=" + str(method) + ".dat")
    RData = p.loadtxt(path + name[:-4] + "Rockstar.dat")
    MData = (p.sort(MData)[::-1])
    RData = (p.sort(RData[:,2])[::-1])
    MData = MData[p.where(MData >= NrParticles*9.26490e9)]
    RData = RData[p.where(RData >= NrParticles*9.26490e9)]


    histMdata = (p.histogram(MData,nrBins)[0])
    histRdata = (p.histogram(RData,nrBins)[0])

    x = (p.histogram(MData,nrBins)[1][1:])
        
    massM = p.zeros(nrBins)
    massR = p.zeros(nrBins)
    massM[-1] = histMdata[-1]
    massR[-1] = histRdata[-1]
    for i in range(nrBins-2,-1,-1):
        massM[i] = histMdata[i] + massM[i+1]
        massR[i] = histRdata[i] + massR[i+1]
    
    tmp = (massR - massM)/massM.astype(float)
    diff = (scipy.ndimage.filters.gaussian_filter(tmp,sigma))
    p.plot(x,diff)
    p.hold("on")
        
p.xlabel("Mass [Msun/h]")
p.ylabel("Fractional difference between Rockstar and MORPH")
p.title("Fractional difference between Rockstar and MORPH")
p.show("on")
    
#filename = "MassDifferencefofr_Rockstar.png"
#p.savefig(savepath+filename)
p.clf()
    
