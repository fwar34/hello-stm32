from PIL import Image
import sys
import os


if len(sys.argv) != 4:
    print("Usage: {} <image-file> <width> <height>".format(sys.argv[0]))
    sys.exit(1)

fname = sys.argv[1]

W = int(sys.argv[2])
print("\r\n")
print("<width> " + str(W))

H = int(sys.argv[3])
print("<height> " + str(H))

img = Image.open(fname)
img = img.convert('RGB')
# 如果指定了宽和高，则进行缩放
if W != img.width or H != img.height:
# if W is not None and H is not None:
    img = img.resize((W, H), Image.Resampling.LANCZOS)
# elif width is not None:
#     ratio = width / image.width
#     new_height = int(image.height * ratio)
#     image = image.resize((width, new_height), Image.Resampling.LANCZOS)
# elif height is not None:
#     ratio = height / image.height
#     new_width = int(image.width * ratio)
#     image = image.resize((new_width, height), Image.Resampling.LANCZOS)

# if img.width != int(W) or img.height != int(H):
#     print("Error: 图片尺寸输入错误 )!!!");
#     sys.exit(2)

f = open("picFile.txt", "w+")

f.write("// size " + str(W) + " x " + str(H) + " \n");
f.write("const unsigned short IMG_DATA[] = { \n ");

for y in range(0, img.height):
    s = ""
    for x in range(0, img.width):
        (r, g, b) = img.getpixel((x, y))
        color565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3)
        color565 = ((color565 & 0xFF00) >> 8) | ((color565 & 0xFF) << 8)
        s += "0x{:04X},".format(color565)
    s += "  \n"
    f.write(s)

f.write("}; \r\n")
f.close()
print("\r\n转换完成\r\n")
