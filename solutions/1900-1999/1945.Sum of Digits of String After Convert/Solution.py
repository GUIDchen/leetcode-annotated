# 题目：1945. 字符串转化后的各位数字之和（Sum of Digits of String After Convert）
# 思路：先用 join 把每个字母换成 1..26 的十进制串并拼接，再循环 k 次求各位数字之和，最后把收敛的字符串转成整数。
# 时间复杂度：O(n + k·D)，D 为数字串长度且每次至少缩短一位；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def getLucky(self, s: str, k: int) -> int:  # s：小写字母串；k：数字和变换的次数
        s = ''.join(str(ord(c) - ord('a') + 1) for c in s)  # ord(c) - ord('a') + 1 得到 1..26，str 转成十进制串后由 join 拼接（10 以上占两位）
        for _ in range(k):  # 重复 k 次数字和变换；_ 表示不关心当前是第几轮
            t = sum(int(c) for c in s)  # sum 累加当前串中每个字符对应的数字
            s = str(t)  # 用这一轮的和替换 s，供下一轮继续收敛
        return int(s)  # k 轮后 s 已是一位数，转成 int 返回
