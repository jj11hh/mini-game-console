import os
from png import Reader as PngReader
from typing import Sequence


def asset_path(path):
    return "./Assets/" + path


# a grayscale image is assumed
def pack_img(source: Sequence[int], src_width: int, src_height: int, dst_width: int, dst_height: int) -> bytearray:
    def sample(x, y):
        iy = int(y * src_height)
        ix = int(x * src_width)
        line = iy * src_width
        idx = line + ix
        return source[idx]

    assert(dst_height % 8 == 0)
    pages = dst_height // 8
    dst = bytearray(dst_width * pages)
    for page in range(pages):
        for x in range(dst_width):
            code = 0
            for y in range(page * 8, (page+1) * 8):
                fx, fy = float(x) / dst_width, float(y) / dst_height
                col = int(sample(fx, fy) > 0)
                code <<= 1
                code |= col

            dst[page * dst_width + x] = code

    return dst


def array2c(arr: Sequence[int], name):
    lines = [f"const unsigned char {name}[] = {{\n"]
    length = len(arr)
    # emit 16 chars per-line
    for i in range(0, length, 16):
        lines.append("".join(["{:#04X},".format(x) for x in arr[i:i+16]]) + "\n")

    lines.append("};\n")
    return "".join(lines)


def concat_rows(rows):
    rows = list(rows)
    if len(rows) < 1:
        return bytearray("")

    # extract red component from image
    acc = rows[0][1::4]
    for i in range(1, len(rows)):
        acc.extend(rows[i][1::4])

    return acc

class AssetPacker:
    def __init__(self):
        self._images = {}

    def add_png(self, path_without_ext):
        png_reader = PngReader(asset_path(path_without_ext + ".png"))
        width, height, font8x8_img, info = png_reader.asRGBA8()
        codes = pack_img(concat_rows(font8x8_img), width, height, width // 4, height // 4)
        self._images[path_without_ext] = codes

    def generate_code(self, f):
        f.write('#include "assets.h"\n'.encode("utf-8"))
        f.write(b'\n')

        for name, image in self._images.items():
            f.write(array2c(image, name).encode("utf-8"))

        f.write(b'\n')

    def build(self):
        with open(os.path.abspath("./Src/assets.c"), "wb") as f:
            self.generate_code(f)


def main():
    # load 8x8 ascii font
    packer = AssetPacker()
    packer.add_png("font8x8")

    packer.build()


if __name__ == "__main__":
    main()

# The following code should print "ABCD"
# def render(img, width, page, start_line, num_lines):
#     start = page * width + start_line
#     for i in range(start, start + num_lines):
#         c = img[i]
#         line = ""
#         for b in range(8):
#             if c & (1 << b):
#                 line += 'x'
#             else:
#                 line += ' '
#
#         print(line)
#
#
# render(codes, width // 4, 4, 0, 32)
