import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.patches as patches
from matplotlib import style
import numpy as np
import serial
import serial.tools.list_ports

WIDTH = 212.2
HEIGHT = 159.4

BAUD = 115200

# Initialize serial port
ports = serial.tools.list_ports.comports(include_links=False)
for i, port in enumerate(ports):
	port = str(port)
	if port.find("Arduino") != -1:
		ser = serial.Serial(ports[i].device, BAUD, timeout=None)
		print("Connected to", port)
		if ser.isOpen():
			ser.close()
		ser.open()

class Draw:
	def __init__(self):
		self.switch_color = None

		self.r_xs = []
		self.r_ys = []
		self.g_xs = []
		self.g_ys = []
		self.b_xs = []
		self.b_ys = []

		self.fig, self.ax = plt.subplots()

		self.rects = [
			patches.Rectangle((-WIDTH/2, -HEIGHT/2), WIDTH/4, 20, lw=0, edgecolor=None, facecolor='r'),
			patches.Rectangle((-WIDTH/2+(WIDTH/4), -HEIGHT/2), WIDTH/4, 20, lw=0, edgecolor=None, facecolor='g'),
			patches.Rectangle((-WIDTH/2+(WIDTH/4)*2, -HEIGHT/2), WIDTH/4, 20, lw=0, edgecolor=None, facecolor='b'),
			patches.Rectangle((-WIDTH/2+(WIDTH/4)*3, -HEIGHT/2), WIDTH/4, 20, lw=.5, edgecolor='#000000', facecolor='#FFFFFF')
		]

		self.ax.set_xlim(-WIDTH/2, WIDTH/2)
		self.ax.set_ylim(-HEIGHT/2, HEIGHT/2)
		for rect in self.rects:
			self.ax.add_patch(rect)
		self.ax.text(WIDTH/2 - (WIDTH/8), -HEIGHT/2 + 10, "Clear", fontsize=12, horizontalalignment='center', verticalalignment='center')
		self.ax.set_title('Malspaß mit Dennis und TJ')

	def update(self, i, r_xs, r_ys, g_xs, g_ys, b_xs, b_ys):
		line = ser.readline().decode('ascii')
		values = line.split('\t')
		xval = float(values[0])*-1
		yval = float(values[1])

		if yval < -HEIGHT/2+20:
			if xval < (-WIDTH/2 + WIDTH/4):
				self.switch_color = 'r'
			elif xval >= (-WIDTH/2 + WIDTH/4) and xval < (-WIDTH/2 + WIDTH/2):
				self.switch_color = 'g'
			elif xval >= (-WIDTH/2 + WIDTH/2) and xval < (-WIDTH/2 + 3*WIDTH/4):
				self.switch_color = 'b'
			elif xval >= -WIDTH/2.0+(WIDTH/4.0)*3:
				self.r_xs = []
				self.r_ys = []
				self.g_xs = []
				self.g_ys = []
				self.b_xs = []
				self.b_ys = []
		else:
			if self.switch_color == 'r':
				self.r_xs.append(xval)
				self.r_ys.append(yval)
			elif self.switch_color == 'g':
				self.g_xs.append(xval)
				self.g_ys.append(yval)
			elif self.switch_color == 'b':
				self.b_xs.append(xval)
				self.b_ys.append(yval)

		# Limit x and y lists to 500 items
		# self.r_xs = self.r_xs[-500:]
		# self.r_ys = self.r_ys[-500:]
		# self.g_xs = self.g_xs[-500:]
		# self.g_ys = self.g_ys[-500:]
		# self.b_xs = self.b_xs[-500:]
		# self.b_ys = self.b_ys[-500:]

		# Draw x and y lists
		r_scat = self.ax.scatter(self.r_xs, self.r_ys, s=1, facecolor='r')
		g_scat = self.ax.scatter(self.g_xs, self.g_ys, s=1, facecolor='g')
		b_scat = self.ax.scatter(self.b_xs, self.b_ys, s=1, facecolor='b')

		return r_scat, g_scat, b_scat

	def animate(self):
		ani = animation.FuncAnimation(self.fig, self.update, fargs=(self.r_xs, self.r_ys, self.g_xs, self.g_ys, self.b_xs, self.b_ys), interval=1, blit=True)
		plt.tight_layout()
		plt.show()

Pad = Draw()
Pad.animate()