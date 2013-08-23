path = "/outData/"
savepath = "./plots/compare/"
filenameRockstar = "rockstar128.dat"

names = ["lcdm1.bin"]

for name in names:

    filenameRockstar = "rockstar_" + name + ".dat"
    
    data = []

    rockstarData = p.loadtxt(path + filenameRockstar)

    data.append(p.sort(rockstarData[:,2])[::-1])
    
    for method in range(4):
        tmpData = p.loadtxt(path + "Mass_" + name[:-4] + "_UnbindingMethod=" + str(method) + ".dat"
        data.append(p.sort(tmpData)[::-1])
        
    for x in data:
        p.loglog(x,range(1,len(x)+1))
            
    names = ["Rockstar"]
    for method in range(4):
        if method == 0:
            names.append("None")
        if method == 1:
            names.append("Spherical")
        if method == 2:
            names.append("Acceleration")
        if method == 3:
            names.append("Loaded")
        
    p.legend(names)

    p.xlabel("log(Mass) Msun")
    p.ylabel("log(Nr of halos with mass >= Mass)")
    filename = "MassFunctionCompare_" + name + ".png"
    p.savefig(savepath+name[:-4]+".png")

