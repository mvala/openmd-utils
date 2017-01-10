'''
Created on Nov 28, 2014

@author: mvala
'''

from openmd.blender import OpenMDBlender

if __name__ == '__main__':
    
    b = OpenMDBlender()
    args = b.get_python_arguments()

    doRender = 0
    inputFile = ''
    for arg in args:
        print(arg)
        if arg == "--render" :
            doRender = 1
        else :
            inputFile = arg
        
    if inputFile.endswith(".xyz"):
        b.clear()
        b.add_xyz(inputFile)
        if doRender : 
            b.render()
    else :
        print("No file '<name>.xyz' specified !!!")
