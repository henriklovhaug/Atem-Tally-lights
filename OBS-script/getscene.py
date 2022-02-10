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
    current_scene = obs.obs_frontend_get_current_scene()
    name = obs.obs_source_get_name(current_scene)
    if name != last_scene:
        last_scene = name
        if logging_enabled:
            print(last_scene)
