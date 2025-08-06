# python3 load_npz_and_print.py xxx.npz
import numpy as np
import sys

def print_npz_contents(npz_file_path):
    try:
        # 尝试加载NPZ文件
        with np.load(npz_file_path) as data:
            print(f"✅ 成功读取文件: {npz_file_path}")
            print(f"文件包含 {len(data.files)} 个数组\n")

            # 遍历所有数组
            for array_name in data.files:
                array = data[array_name]
                print(f"🔹 数组名称: '{array_name}'")
                print(f"   形状: {array.shape} | 数据类型: {array.dtype}")
                print(f"   值:")

                # 遍历并打印每个元素
                if array.ndim == 0:  # 标量
                    print(f"   {array}")
                elif array.ndim == 1:  # 一维数组
                    for i, val in enumerate(array):
                        print(f"   [{i}] = {val}")
                else:  # 多维数组
                    # 使用np.nditer高效遍历所有维度
                    it = np.nditer(array, flags=['multi_index'])
                    while not it.finished:
                        index_str = "][".join(map(str, it.multi_index))
                        print(f"   [{index_str}] = {it[0]}")
                        it.iternext()

                print("-" * 50)  # 分隔线

    except Exception as e:
        print(f"❌ 读取文件时出错: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("使用方法: python read_npz.py <npz文件路径>")
        sys.exit(1)

    npz_file_path = sys.argv[1]
    print_npz_contents(npz_file_path)