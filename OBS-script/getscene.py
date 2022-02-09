import obspython as obs
from time import sleep


def script_description():
    return "Script to report active scene"


last_scene = ""


def script_tick(seconds):
    global last_scene
    current_scene = obs.obs_frontend_get_current_scene()
    name = obs.obs_source_get_name(current_scene)
    if name != last_scene:
        last_scene = name
        print(last_scene)
