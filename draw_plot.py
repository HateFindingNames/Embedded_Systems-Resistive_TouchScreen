import matplotlib.pyplot as plt
import matplotlib.animation as animation
import matplotlib.patches as patches
from svgpath2mpl import parse_path
from svgpathtools import svg2paths
import serial
import serial.tools.list_ports

WIDTH = 212.2
HEIGHT = 159.4
ASPECT = (WIDTH/30, HEIGHT/30)

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

		# self.pen_size_c = [None]
		# self.pen_size_indicator = [1]

		# self.active_pen = None
		feather_path, attributes = svg2paths('Feather.svg')
		feather_marker = parse_path(attributes[0]['d'])

		self.fig, self.ax = plt.subplots(figsize=ASPECT)
		self.ax.set_aspect('auto')

		self.buttons = [
			patches.Rectangle((-WIDTH/2, -HEIGHT/2), WIDTH/4, 20, lw=0, edgecolor=None, facecolor='r'),
			patches.Rectangle((-WIDTH/2+(WIDTH/4), -HEIGHT/2), WIDTH/4, 20, lw=0, edgecolor=None, facecolor='g'),
			patches.Rectangle((-WIDTH/2+(WIDTH/4)*2, -HEIGHT/2), WIDTH/4, 20, lw=0, edgecolor=None, facecolor='b'),
			patches.Rectangle((-WIDTH/2+(WIDTH/4)*3, -HEIGHT/2), WIDTH/4, 20, lw=.5, edgecolor='#000000', facecolor='#FFFFFF')
			# patches.Circle((WIDTH/2 - 15, -HEIGHT/2 + 30), radius=7, edgecolor='black', facecolor='white'),
			# patches.Circle((WIDTH/2 - 15, -HEIGHT/2 + 58), radius=7, edgecolor='black', facecolor='white')
		]

		self.ax.set_xlim(-WIDTH/2, WIDTH/2)
		self.ax.set_ylim(-HEIGHT/2, HEIGHT/2)
		for button in self.buttons:
			self.ax.add_patch(button)
		self.ax.text(WIDTH/2 - (WIDTH/8), -HEIGHT/2 + 10, "Clear", fontsize=12, horizontalalignment='center', verticalalignment='center')
		# self.ax.text(WIDTH/2 - 15, -HEIGHT/2 + 30, "-", fontsize=12, horizontalalignment='center', verticalalignment='center')
		# self.ax.text(WIDTH/2 - 15, -HEIGHT/2 + 58, "+", fontsize=12, horizontalalignment='center', verticalalignment='center')
		self.ax.set_title('Malspaß mit Dennis und TJ')

		self.r_pen, = self.ax.plot(self.r_xs, self.r_ys, ls='', c='r', ms=1, marker='o', animated=True)
		self.g_pen, = self.ax.plot(self.g_xs, self.g_ys, ls='', c='g', ms=1, marker='o', animated=True)
		self.b_pen, = self.ax.plot(self.b_xs, self.b_ys, ls='', c='b', ms=1, marker='o', animated=True)
		self.pen, = self.ax.plot(self.b_xs, self.b_ys, marker=feather_marker, ms=240, ls='', c='black', animated=True)

		# self.pen_size = self.ax.scatter(WIDTH/2 - 15, -HEIGHT/2 + 44, c=self.pen_size_c[0], s=self.pen_size_indicator)

	def update(self, i, r_xs, r_ys, g_xs, g_ys, b_xs, b_ys):
		line = ser.readline().decode('ascii')
		values = line.split('\t')
		xval = float(values[0])
		yval = float(values[1])
		self.pen.set_xdata(xval)
		self.pen.set_ydata(yval)

		if yval < -HEIGHT/2+20:
			if xval < (-WIDTH/2 + WIDTH/4):
				self.switch_color = 'r'
				# self.pen_size_c = ['r']
				# self.pen_size.set_color(self.pen_size_c)
				# self.active_pen = self.r_pen
			elif xval >= (-WIDTH/2 + WIDTH/4) and xval < (-WIDTH/2 + WIDTH/2):
				self.switch_color = 'g'
				# self.pen_size_c = ['g']
				# self.pen_size.set_color(self.pen_size_c)
				# self.active_pen = self.g_pen
			elif xval >= (-WIDTH/2 + WIDTH/2) and xval < (-WIDTH/2 + 3*WIDTH/4):
				self.switch_color = 'b'
				# self.pen_size_c = ['b']
				# self.pen_size.set_color(self.pen_size_c)
				# self.active_pen = self.b_pen
			elif xval >= -WIDTH/2.0+(WIDTH/4.0)*3:
				self.r_xs = []
				self.r_ys = []
				self.g_xs = []
				self.g_ys = []
				self.b_xs = []
				self.b_ys = []
				self.r_pen.set_xdata(self.r_xs)
				self.r_pen.set_ydata(self.r_ys)
				self.g_pen.set_xdata(self.g_xs)
				self.g_pen.set_ydata(self.g_ys)
				self.b_pen.set_xdata(self.b_xs)
				self.b_pen.set_ydata(self.b_ys)

				return self.r_pen, self.g_pen, self.b_pen, self.pen#, self.pen_size

		# elif xval > WIDTH/2 - 22 and xval < WIDTH/2 - 8:
		# 	if yval > -HEIGHT/2 + 23 and yval < -HEIGHT/2 + 37:
		# 		self.pen_size_indicator[0] -= 0.1
		# 		self.pen_size.set_sizes(self.pen_size_indicator)
		# 		self.active_pen.set_sizes(self.pen_size_indicator)

		# 	elif yval > -HEIGHT/2 + 51 and yval < -HEIGHT/2 + 65:
		# 		self.pen_size_indicator[0] += 0.1
		# 		self.pen_size.set_sizes(self.pen_size_indicator)
		# 		self.pen_size.set_sizes(self.pen_size_indicator)
		else:
			if self.switch_color == 'r':
				self.r_xs.append(xval)
				self.r_ys.append(yval)
				self.r_pen.set_xdata(self.r_xs)
				self.r_pen.set_ydata(self.r_ys)
			elif self.switch_color == 'g':
				self.g_xs.append(xval)
				self.g_ys.append(yval)
				self.g_pen.set_xdata(self.g_xs)
				self.g_pen.set_ydata(self.g_ys)
			elif self.switch_color == 'b':
				self.b_xs.append(xval)
				self.b_ys.append(yval)
				self.b_pen.set_xdata(self.b_xs)
				self.b_pen.set_ydata(self.b_ys)

		# Limit x and y lists to 500 items
		# self.r_xs = self.r_xs[-500:]
		# self.r_ys = self.r_ys[-500:]
		# self.g_xs = self.g_xs[-500:]
		# self.g_ys = self.g_ys[-500:]
		# self.b_xs = self.b_xs[-500:]
		# self.b_ys = self.b_ys[-500:]

		return self.r_pen, self.g_pen, self.b_pen, self.pen#, self.pen_size

	def animate(self):
		ani = animation.FuncAnimation(self.fig, self.update, fargs=(self.r_xs, self.r_ys, self.g_xs, self.g_ys, self.b_xs, self.b_ys), interval=1, blit=True)
		plt.tight_layout()
		plt.show()

Pad = Draw()
Pad.animate()