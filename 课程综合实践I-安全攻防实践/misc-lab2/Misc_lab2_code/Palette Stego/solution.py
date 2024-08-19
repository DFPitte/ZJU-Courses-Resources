from PIL import Image

def extract(image_path):
    img = Image.open(image_path)

    message_bits = []

    # 获取图像的尺寸
    width, height = img.size

    for y in range(height):
        for x in range(width):
            pixel = img.getpixel((x, y))
            # 获取该像素对应的调色板颜色值的最低有效位
            lsb = pixel & 1
            message_bits.append(lsb)

    message_bytes = [int(''.join(map(str, message_bits[i:i+8])), 2) for i in range(0, len(message_bits), 8)]
    message = ''.join(chr(byte) for byte in message_bytes if 32 <= byte <= 126)
    return message
image_path = '1.png'

hidden_message = extract(image_path)
print(hidden_message)
