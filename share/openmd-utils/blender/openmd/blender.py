'''
Created on Nov 28, 2014

@author: mvala
'''

import bpy

class OpenMDBlender(object):
    '''
    OpenMD blender utils
    '''

    def __init__(self):
        '''
        Constructor
        '''
        print("Creating OpenMDBlender class ...")
        self.args = []
        
    def get_python_arguments(self) : 
        '''
        Returns Blender python arguments
        '''
        
        args = []
        import sys
        isPythonArg = 0
        for arg in sys.argv:
            if arg == "--" :
                isPythonArg = 1
                continue            
            if isPythonArg == 0 :
                continue
            else :
                args.append(arg)
        return args
        
    def clear(self) :
        '''
        Removing all objects from blender
        '''
        bpy.ops.object.mode_set(mode='OBJECT')
        bpy.ops.object.select_by_type(type='MESH')
        bpy.ops.object.delete(use_global=False)
        bpy.ops.object.select_by_type(type='CAMERA')
        bpy.ops.object.delete(use_global=False)
        bpy.ops.object.select_by_type(type='LAMP')
        bpy.ops.object.delete(use_global=False)
    
        for item in bpy.data.meshes:
            bpy.data.meshes.remove(item)
    
    def set_active_camera(self) :
        '''
        Setting first camera as active
        '''
        for ob in bpy.context.scene.objects :
            if ob.type == 'CAMERA':
                bpy.context.scene.camera = ob
                break
#                 print('Set camera %s' % ob.name )
            
    def add_xyz(self, filepath) :
        '''
        Adding xyz file
        '''
        bpy.ops.import_mesh.xyz(filepath=filepath,use_camera=True,use_lamp=True,use_frames=True)
        # FIXME : Viewport is not refreshed 
        bpy.data.scenes[0].frame_current = 0
        self.set_active_camera()
        bpy.ops.wm.save_as_mainfile(filepath=filepath.replace(".xyz",".blend"))
        

    def render(self) :
        '''
        Rendering
        '''
        print("Rendering...")
        bpy.data.scenes['Scene'].render.resolution_percentage = 100
        bpy.data.scenes[0].render.image_settings.file_format='AVI_JPEG';
        bpy.ops.render.render(animation=True)
