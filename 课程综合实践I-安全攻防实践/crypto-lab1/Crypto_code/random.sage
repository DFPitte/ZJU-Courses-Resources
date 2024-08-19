import random

# 1. 随机生成一个可逆的 3x3 矩阵 MT
def generate_invertible_matrix():
    while True:
        MT = Matrix(Zmod(256), 3, 3, [random.randint(0, 255) for _ in range(9)])
        if MT.is_invertible():
            return MT

MT = generate_invertible_matrix()
print(MT)

# 2. 生成一个随机的 flag，并通过 flag 生成矩阵 FT
flag = "AAA{" + "".join(chr(random.randint(32, 126)) for _ in range(25))+"}"
FT = Matrix(Zmod(256), 3, 10)
for i in range(3):
    for j in range(10):
        FT[i, j] = ord(flag[i + j * 3])
print(flag)
print(FT)

# 3. 计算 RT = MT * FT
RT = MT * FT
print("RT (result of MT * FT):\n", RT)

# 4. 通过已知的 RT 和 MT，求解 FT
MT_inv = MT.inverse()
FT_computed = MT_inv * RT
print(FT_computed)
