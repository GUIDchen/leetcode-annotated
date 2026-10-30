# 3280. 将日期转换为二进制表示（Convert Date to Binary）
# 核心思路：按 '-' 切分年、月、日，逐段用 int 转成十进制再以 :b 格式化成二进制，最后用 '-' 拼接。
# 复杂度：时间 O(1)，空间 O(1)

class Solution:  # 定义题解类
    def convertDateToBinary(self, date: str) -> str:  # 返回该日期对应的二进制表示字符串
        return "-".join(f"{int(s):b}" for s in date.split("-"))  # 切出年、月、日，各自转成二进制文本后用 '-' 拼回
