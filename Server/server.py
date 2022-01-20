from http.server import HTTPServer, BaseHTTPRequestHandler


status = {
    "/cam1": "live",
    "/cam2": "inactive",
    "/cam3": "inactive",
    "/cam4": "inactive",
}


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
    httpd = HTTPServer(("", 8000), Handler)
    httpd.serve_forever()
