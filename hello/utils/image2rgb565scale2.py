from PIL import Image
import sys
import os
# import pdb

def rgb_to_rgb565(r, g, b):
    """
    将 RGB 颜色值转换为 RGB565 格式
    :param r: 红色通道值 (0-255)
    :param g: 绿色通道值 (0-255)
    :param b: 蓝色通道值 (0-255)
    :return: RGB565 格式的 16 位整数
    """
    r5 = (r >> 3) & 0x1F
    g6 = (g >> 2) & 0x3F
    b5 = (b >> 3) & 0x1F
    rgb565 = (r5 << 11) | (g6 << 5) | b5
    return rgb565

def read_image_to_rgb565_array(file_path, width, height):
    """
    读取 PNG 文件并转换为 RGB565 数组，可指定输出的宽和高
    :param file_path: PNG 文件的路径
    :param width: 输出图片的宽度，若为 None 则使用原始图片宽度
    :param height: 输出图片的高度，若为 None 则使用原始图片高度
    :return: RGB565 数组
    """
    try:
        # pdb.set_trace()
        # 打开 PNG 文件
        image = Image.open(file_path)
        # 转换为 RGB 模式
        image = image.convert('RGB')

        # 如果指定了宽和高，则进行缩放
        if width != image.width and height != image.height and width != 0 and height != 0:
            image = image.resize((width, height), Image.Resampling.LANCZOS)
            print("AAAA")
        elif width != image.width and width != 0:
            ratio = width / image.width
            new_height = int(image.height * ratio)
            image = image.resize((width, new_height), Image.Resampling.LANCZOS)
            print("BBBB: width " + str(width) + " height: " + str(new_height))
        elif height != image.height and height != 0:
            ratio = height / image.height
            new_width = int(image.width * ratio)
            image = image.resize((new_width, height), Image.Resampling.LANCZOS)
            print("CCCC: width " + str(new_width) + " height: " + str(height))

        width, height = image.size

        f = open("picFile.txt", "w+")
        f.write("#ifndef INC_IMAGE_H_\n")
        f.write("#define INC_IMAGE_H_\n\n")
        f.write("#define IMG_WIDTH " + str(width) + "\n")
        f.write("#define IMG_HEIGHT " + str(height) + "\n\n")
        f.write("// size " + str(width) + " x " + str(height) + "\n");
        f.write("const unsigned short IMG_DATA[] = { \n ");
        rgb565_array = []
        # 遍历图像的每个像素
        for y in range(height):
            s = ""
            for x in range(width):
                # 获取像素的 RGB 值
                r, g, b = image.getpixel((x, y))
                # 将 RGB 值转换为 RGB565 格式
                rgb565 = rgb_to_rgb565(r, g, b)
                rgb565_array.append(rgb565)
                s += "0x{:04X},".format(rgb565)
            s += "  \n"
            f.write(s)
        f.write("}; \n\n")
        f.write("#endif // INC_IMAGE_H_")
        f.close()
        print("\r\n转换完成\r\n")
        return rgb565_array
    except Exception as e:
        print(f"读取文件时出错: {e}")
        return []

def convert_process():
    # if len(sys.argv) != 4:
    #     print("Usage: {} <image-file> <width> <height>".format(sys.argv[0]))
    #     sys.exit(1)

    fname = sys.argv[1]

    W = 0
    if len(sys.argv) == 3 and sys.argv[2] is not None:
        W = int(sys.argv[2])
        print("\r\n")
        print("<width> " + sys.argv[2])

    H = 0
    if len(sys.argv) == 4 and sys.argv[3] is not None:
        H = int(sys.argv[3])
        print("<height> " + sys.argv[3])

    read_image_to_rgb565_array(fname, W, H)

convert_process()
# 使用示例
# file_path = 'your_image.png'
# output_width = 320
# output_height = 240
# rgb565_array = read_image_to_rgb565_array(file_path, output_width, output_height)
# if rgb565_array:
#     print(f"转换后的 RGB565 数组长度: {len(rgb565_array)}")
#     # 可以根据需要进一步处理或保存这个数组

