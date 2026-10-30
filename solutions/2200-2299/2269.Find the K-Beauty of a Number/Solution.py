# 题目：2269. 找到一个数字的 K 美丽值（Find the K-Beauty of a Number）
# 思路：把 num 转成字符串，遍历所有长度为 k 的子串，转回整数后检查它非零且整除 num，累加满足条件的子串数。
# 时间复杂度：O(d·k)，d 为数字位数、每段切片与转换 O(k)；空间复杂度：O(d)，保存数字的字符串副本。
class Solution:  # LeetCode 约定的题解类
    def divisorSubstrings(self, num: int, k: int) -> int:  # num：原数字；k：子串长度；返回 K 美丽值的个数
        ans = 0  # 合法子串计数
        s = str(num)  # 转成字符串，便于按下标切片
        for i in range(len(s) - k + 1):  # 枚举每个长度为 k 的子串起点，保证右端点不越界
            t = int(s[i : i + k])  # 截取长度 k 的子串并转成整数
            if t and num % t == 0:  # 子串非零（短路避免除零）且能整除 num
                ans += 1  # 满足条件，美丽值加一
        return ans  # 返回美丽值个数
