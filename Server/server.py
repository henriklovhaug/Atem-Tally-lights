from http.server import HTTPServer, BaseHTTPRequestHandler
import PyATEMMax
import time
import netifaces as ni

atem = PyATEMMax.ATEMMax()


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
    switcher.disconnect()
    return ip

status = {
    "/cam1": "live",
    "/cam2": "inactive",
    "/cam3": "inactive",
    "/cam4": "inactive",
}

def on_camera_change(params):
    print("--------------------------")
    print("Current input: ",atem.programInput[0].videoSource)
    print("Current preview: ",atem.previewInput[0].videoSource)
    print("--------------------------")
    current = list(str(atem.programInput[0].videoSource))[5] if list(str(atem.programInput[0].videoSource))[0] == "i" else 0
    print(current)


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
    ip = find_atem_ip()
    atem = PyATEMMax.ATEMMax() # When disconnected, variable should be reassigned. Why? I dunno, it works
    atem.registerEvent(atem.atem.events.receive, on_camera_change)
    atem.connect(ip)
    atem.waitForConnection()
    print("Current Atem device is: ", atem.atemModel)
    flip = True
    while True:
        # print(atem.connected)
        # print(ip)
        time.sleep(0.5)

