# 题目：3167. 字符串的更好压缩（Better Compression of String）
# 思路：一次扫描把每组「字符 + 数字串」拆开，用 Counter 累加每个字符的总次数，最后按字符升序重新拼接。
# 时间复杂度：O(n + k log k)，n 为串长，k 为不同字符数（≤26）；空间复杂度：O(k)，计数表的大小。
class Solution:  # LeetCode 约定的题解类
    def betterCompression(self, compressed: str) -> str:  # compressed 是形如 a2b3c1 的压缩串
        cnt = Counter()  # 统计每个字符出现的总次数；缺失的键默认计 0
        i, n = 0, len(compressed)  # i 为扫描指针，n 为串长
        while i < n:  # 逐组处理「字符 + 数字串」
            j = i + 1  # 从字符后面开始读数字
            x = 0  # 当前组的次数
            while j < n and compressed[j].isdigit():  # 只要后面还是数字就继续读
                x = x * 10 + int(compressed[j])  # 逐位累积成整数
                j += 1  # 后移一位
            cnt[compressed[i]] += x  # 把这一组的次数累到对应字符上
            i = j  # 跳到下一组的字符位置
        return "".join(sorted(f"{k}{v}" for k, v in cnt.items()))  # 按字符升序拼接「字符 + 总次数」；每个字符只出现一次，因此按整串排序等价于按字符排序
