import _pymengine as mengine
import datetime
import OpenGL.GL as gl

RED   = (1,0,0,1)
GREEN = (0,1,0,1)
BLUE  = (0,0,1,1)

class ColorScene(mengine.Scene):
    def __init__(self, color):
        self.color = color

    def setup(self):
        gl.glClearColor(*self.color)
        self.start_time = datetime.datetime.now()

    def render(self):
        gl.glClear(gl.GL_COLOR_BUFFER_BIT)
        if datetime.datetime.now()-self.start_time>datetime.timedelta(seconds=1):
            change_scene()

scenes = [ColorScene(RED), ColorScene(GREEN), ColorScene(BLUE)]
current_scene = 0
def change_scene():
    global current_scene
    current_scene += 1
    current_scene %= len(scenes)
    engine.set_scene(scenes[current_scene])

engine = mengine.Engine()
engine.set_scene(scenes[0])
engine.start()

