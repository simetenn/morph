import pylab as p
import sys
from mpl_toolkits.mplot3d import Axes3D

try:
    name = str(sys.argv[1])
except:
    name = "positions.dat"
    #name = "positions_all.dat"
#print "Using file: " + name 
    
particles = [] 
with open(name, "r") as infile:
    for line in infile:
        particles.append(line.split())
        #data = []
        #for number in line.split():
        #    data.append(float(number))
            
        #particles.append(p.array(data))
    

particles = p.array(particles,float)
#particles = particles[::10,:]
"""
p.scatter(particles[:,0],particles[:,1], c=particles[:,-1])
p.show()
"""

index = p.where(particles[:,-1] == 0)

fig = p.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(particles[index[0],0],particles[index[0],1],particles[index[0],2], s=1,c=particles[index[0],-1],linewidths=0.1)
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_zlabel('Z-axis')
p.show()

