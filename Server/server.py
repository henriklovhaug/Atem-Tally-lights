from http.server import HTTPServer, BaseHTTPRequestHandler
import PyATEMMax
import time
import netifaces as ni
import requests

atem = PyATEMMax.ATEMMax()

prev_preview = 0
prev_current = 0


# State:
#   0 = Off
#   1 = Preview
#   2 = Active
class Camera():
    def __init__(self,ip,number):
        self.ip = ip
        self.number = number
        self.state = 0


camera1 = Camera("192.168.1.4", 1)
camera2 = Camera("192.168.1.5", 2)
camera3 = Camera("192.168.1.6", 3)
camera4 = Camera("192.168.1.7", 4)
cameralist: [] = [camera1, camera2, camera3, camera4]


def find_atem_ip() -> str:
    ni.ifaddresses('eth0')
    ip = ni.ifaddresses('eth0')[ni.AF_INET][0]['addr']
    ip_subnet = str(ip).split(".")[2]
    print(ip)
    print(ip_subnet)
    for i in range(1, 255):
        ip = f"192.168.{ip_subnet}.{i}"
        print(f"Checking {ip}", end="\r")
        atem.ping(ip)
        if atem.waitForConnection(waitForFullHandshake=False):
            print(f"ATEM found at {ip}")
            break
    return ip


def is_atem_ip(ip) -> bool:
    atem.ping(ip)
    return atem.waitForConnection(waitForFullHandshake=False)


def on_camera_change(params):
    global prev_preview
    global prev_current

    # print("--------------------------")
    # print("Current input: ", atem.programInput[0].videoSource)
    # print("Current preview: ", atem.previewInput[0].videoSource)
    # print("--------------------------")
    current = list(str(atem.programInput[0].videoSource))[5] if list(
        str(atem.programInput[0].videoSource))[0] == "i" else 0

    preview = list(str(atem.previewInput[0].videoSource))[5] if list(
        str(atem.previewInput[0].videoSource))[0] == "i" else 0

    if prev_current != current:
        update_camera(cameralist[int(current)-1 if current != 0 else 0], 2)
        update_camera(cameralist[int(prev_current)-1 if current != 0 else 0], 0)
        prev_current = current

    if prev_preview != preview:
        update_camera(cameralist[int(prev_preview)-1 if current != 0 else 0], 0)
        if preview != current:
            update_camera(cameralist[int(preview)-1 if current != 0 else 0], 1)
        prev_preview = preview

    #print(current)


def update_camera(camera: Camera, state):
    if state == 2:
        try:
            r = requests.get("http://"+camera.ip)
            print(r.status_code)
            print("Send turn on request")
        except OSError:
            print("failed to connect")
            pass
    elif state == 1:
        try:
            r = requests.get("http://"+camera.ip+"/preview")
            print(r.status_code)
            print("Sent preview request")
        except OSError:
            pass
    else:
        try:
            r = requests.get("http://"+camera.ip+"/off")
            print(r.status_code)
            print("Sent preview request")
        except OSError:
            pass



class Handler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        self.written_bytes = 0

        for key, value in status.items():
            if self.path == key:
                self.written_bytes += self.wfile.write(value.encode())

        if self.written_bytes == 0:
            self.wfile.write("Endpoint not in use".encode())


if __name__ == "__main__":
    # ip = find_atem_ip()
    ip = "192.168.0.240"
    # When disconnected, variable should be reassigned. Why? I dunno, it works
    atem = PyATEMMax.ATEMMax()
    atem.registerEvent(atem.atem.events.receive, on_camera_change)
    atem.connect(ip)
    atem.waitForConnection()
    print("Current Atem device is: ", atem.atemModel)
    while True:
        # print(atem.connected)
        # print(ip)
        time.sleep(0.5)
