import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

x,y,z1 = np.loadtxt("./prueba.txt",unpack = True)

z2 = (x*x-1)*(y*y-1)*(x*x+y*y-0.25)
z = abs(z1-z2)

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot_trisurf(x,y,z1)
plt.show()
