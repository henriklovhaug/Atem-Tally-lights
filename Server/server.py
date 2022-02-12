# Someone was here
import PyATEMMax
import time
import netifaces as ni
import sys
from requests_futures.sessions import FuturesSession

atem = PyATEMMax.ATEMMax()
session = FuturesSession()


class Camera():
    def __init__(self, ip, number):
        self.ip = ip
        self.number = number
        self.live = 0
        self.preview = 0


cameralist: [] = [
        Camera("192.168.2.4", 1),
        Camera("192.168.2.5", 2),
        Camera("192.168.2.6", 3),
        Camera("192.168.2.7", 4)
]


def find_atem_ip() -> str:
    ni.ifaddresses('eth0')
    while not ni.AF_INET in ni.ifaddresses('eth0').keys():
        time.sleep(1)
    ip = ni.ifaddresses('eth0')[ni.AF_INET][0]['addr']
    ip_subnet = str(ip).split(".")[2]
    print(ip)
    print(ip_subnet)
    for i in range(254, 1, -1):
        ip = f"192.168.{ip_subnet}.{i}"
        print(f"Checking {ip}", end="\r")
        sys.stdout.flush()
        atem.ping(ip)
        if atem.waitForConnection(waitForFullHandshake=False):
            print(f"ATEM found at {ip}")
            break
    return ip


def is_atem_ip(ip) -> bool:
    atem.ping(ip)
    return atem.waitForConnection(waitForFullHandshake=False)


def on_camera_change(params):

    print("--------------------------")
    print("live input: ", atem.programInput[0].videoSource)
    print("preview: ", atem.previewInput[0].videoSource)
    print("--------------------------")

    live = int(list(str(atem.programInput[0].videoSource))[5]) if list(
        str(atem.programInput[0].videoSource))[0] == "i" else None

    preview = int(list(str(atem.previewInput[0].videoSource))[5]) if list(
        str(atem.previewInput[0].videoSource))[0] == "i" else None

    if live != None:
        for camera in cameralist:
            if camera.number == live:
                if camera.live == 0:
                    update_camera(camera, "live", 1)
            else:
                if camera.live == 1:
                    update_camera(camera, "live", 0)

    if preview != None:
        for camera in cameralist:
            if camera.number == preview:
                if camera.preview == 0:
                    update_camera(camera, "preview", 1)
            else:
                if camera.preview == 1:
                    update_camera(camera, "preview", 0)


def update_camera(camera: Camera, camera_property, state):
    try:
        r = session.get(f"http://{camera.ip}/{camera_property}/{state}")
        if camera_property == "live":
            camera.live = state
        else:
            camera.preview = state
    except OSError:
        pass


if __name__ == "__main__":
    ip = find_atem_ip()
    # When disconnected, variable should be reassigned. Why? I dunno, it works
    atem = PyATEMMax.ATEMMax()
    atem.registerEvent(atem.atem.events.receive, on_camera_change)
    atem.registerEvent(atem.atem.events.disconnect, find_atem_ip)
    atem.connect(ip)
    atem.waitForConnection()
    print("live Atem device is: ", atem.atemModel)
    while True:
        time.sleep(42)  # DO NOT REMOVE! HAS TO BE 42!
