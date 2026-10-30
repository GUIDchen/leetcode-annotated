# 3602. 十六进制和三十六进制转化 / Hexadecimal and Hexatrigesimal Conversion
# 核心思路：把 n 的平方转成十六进制、n 的立方转成三十六进制，共用一个“除 k 取余、末位逆序”的进制转换函数，最后拼接两段字符串返回。
# 复杂度：时间 O(log n)，空间 O(log n)，即结果字符串的长度。
class Solution:  # 定义题解类
    def concatHex36(self, n: int) -> str:  # 主函数：返回 n^2 的十六进制与 n^3 的三十六进制拼接串
        def f(x: int, k: int) -> str:  # 内部辅助函数：把十进制 x 转换成 k 进制字符串
            res = []  # 用列表按低位到高位收集字符，最后再逆序
            while x:  # 不断取余直到 x 被除尽
                v = x % k  # 取出当前最低位数字
                if v <= 9:  # 0~9 的位用数字字符表示
                    res.append(str(v))  # 追加对应的数字字符
                else:  # 10 及以上的位用大写字母表示
                    res.append(chr(ord("A") + v - 10))  # 追加 A 起算的字母字符
                x //= k  # 去掉已处理的最低位
            return "".join(res[::-1])  # 低位在前，切片反转后拼接成结果

        x, y = n**2, n**3  # 分别取出 n 的平方与立方
        return f(x, 16) + f(y, 36)  # 平方转十六进制、立方转三十六进制后拼接返回
