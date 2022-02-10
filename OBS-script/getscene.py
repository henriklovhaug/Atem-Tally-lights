import obspython as obs

last_scene = ""
logging_enabled = False


def script_description():
    return "Script to report active scene"


def script_properties():
    props = obs.obs_properties_create()
    obs.obs_properties_add_bool(props, "logging_enabled", "Logging")
    return props


def script_update(settings):
    global logging_enabled
    logging_enabled = obs.obs_data_get_bool(settings, "logging_enabled")


def script_tick(seconds):
    global last_scene, logging_enabled
    current_scene_as_source = obs.obs_frontend_get_current_scene()
    current_scene = obs.obs_scene_from_source(current_scene_as_source)
    name = obs.obs_source_get_name(current_scene_as_source)
    
    if name != last_scene:
        last_scene = name
        if logging_enabled:
            # print(obs.obs_scene_enum_items(current_scene))
            print(f"Scene: {last_scene}")
            print("Sources: ")
            for scene_item in obs.obs_scene_enum_items(current_scene):
                as_source = obs.obs_sceneitem_get_source(scene_item)
                print(obs.obs_source_get_name(as_source))
            print()
