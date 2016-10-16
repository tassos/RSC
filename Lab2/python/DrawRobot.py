# -*- coding: utf-8 -*-
"""
Created on Sun Oct 16 19:15:16 2016

@author: tassos
"""
import numpy as np
import matplotlib.pyplot as plt

def DrawCoord(M,L,ax,lw):    
    CoX = M[0:3,3]+L*M[0:3,0]
    CoY = M[0:3,3]+L*M[0:3,1]
    CoZ = M[0:3,3]+L*M[0:3,2]
    CoO = M[0:3,3]
    
    ax.scatter(CoO[0],CoO[1],CoO[2],c='Black')
    ax.plot([CoO[0],CoX[0]],[CoO[1],CoX[1]],[CoO[2],CoX[2]],c='Red',lw=lw)
    ax.plot([CoO[0],CoY[0]],[CoO[1],CoY[1]],[CoO[2],CoY[2]],c='Blue',lw=lw)
    ax.plot([CoO[0],CoZ[0]],[CoO[1],CoZ[1]],[CoO[2],CoZ[2]],c='Green',lw=lw)
    plt.show()
    
def DrawSegment(M1,M2,ax):
    M=np.array([M1[0:3,3],M2[0:3,3]])
    ax.plot(M[:,0],M[:,1],M[:,2],lw=8)
    
def axisEqual3D(ax):
    extents = np.array([getattr(ax, 'get_{}lim'.format(dim))() for dim in 'xyz'])
    sz = extents[:,1] - extents[:,0]
    centers = np.mean(extents, axis=1)
    maxsize = max(abs(sz))
    r = maxsize/2
    for ctr, dim in zip(centers, 'xyz'):
        getattr(ax, 'set_{}lim'.format(dim))(ctr - r, ctr + r)

pi=3.14121356

M=[]
M.append(np.identity(4))
M.append(np.array([[np.cos(pi/4),-np.sin(pi/4),0,0],
                   [np.sin(pi/4),np.cos(pi/4),0,0],
                   [0,0,1,0],
                   [0,0,0,1]]))
M.append(np.array([[1,0,0,4],
                   [0,1,0,2],
                   [0,0,1,5],
                   [0,0,0,1]]))
M.append(np.array([[1,0,0,5],
                   [0,1,0,0],
                   [0,0,1,0],
                   [0,0,0,1]]))
                   
fig = plt.figure()
ax = fig.gca(projection='3d')
P=np.identity(4)
DrawCoord(P,2,ax,5)
for i in range(0,len(M)):
    N=np.identity(4)
    for k in range(i,0,-1):
        N=np.dot(M[k],N)
    DrawCoord(N,1,ax,2)
    DrawSegment(P,N,ax)
    P=N
    
axisEqual3D(ax)