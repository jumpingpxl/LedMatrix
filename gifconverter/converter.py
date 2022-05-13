from PIL import Image, ImageFilter, ImageSequence
import os
import sys

gif_name = sys.argv[1]
image = Image.open('input/' + gif_name + '.gif')

frames = image.n_frames

if os.path.exists("output/" + gif_name + ".matrix"):
  os.remove("output/" + gif_name + ".matrix")

file = open("output/" + gif_name + ".matrix", "w")

file.write(str(image.n_frames))
file.write('\n')

for z in range(frames):
    image.seek(z)
    image_data = image.convert('RGB')
    output = ""

    for y in range(image.width):
        for x in range(image.height):
            r, g, b = image_data.getpixel((x, y))

            output += ";" + str(r) + "," + str(g) + "," + str(b)

    file.write(str(image.tell()) + ";" + str(image.info['duration']) + output)
    file.write('\n')

file.close()