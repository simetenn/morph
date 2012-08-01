from numpy import random

nrParticle = 20
nrData = 10
data = random.uniform(-1,1,nrParticle*nrData)
data.resize(nrParticle,nrData)

filename = "particles.dat"
file = open(filename, 'w')

i = 1
for line in data:
    string = "1 0 "
    for number in line[:-2]:
        string += str(number)+" "
    if i == nrParticle:
        string += str(line[-1])    
    else:
        string += str(line[-1])+"\n"
    file.write(string)
    i+=1

file.close()
