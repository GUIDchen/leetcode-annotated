# 题目：2243. 计算字符串的数字和（Calculate Digit Sum of a String）
# 思路：只要串长大于 k 就模拟一轮：每 k 个字符切一组，组内求和后转成字符串拼起来，直到串长不超过 k。
# 时间复杂度：O(n log n)，每轮长度至少缩短到约 n/3，总体呈几何级数；空间复杂度：O(n)，用于存放新串。
class Solution:  # LeetCode 约定的题解类
    def digitSum(self, s: str, k: int) -> str:  # s 是数字串，k 是每组的字符个数
        while len(s) > k:  # 长度不超过 k 时不再需要分组，循环结束
            t = []  # t 收集本轮各组求和后的字符串片段
            n = len(s)  # 缓存当前串长度，后面判断最后一组边界时要用
            for i in range(0, n, k):  # 每 k 个字符划为一组，i 是组首下标
                x = 0  # 本组各位数字之和
                for j in range(i, min(i + k, n)):  # 组内逐个字符求和，最后一组可能不足 k 个
                    x += int(s[j])  # 把字符转成整数后累加
                t.append(str(x))  # 把本组的和转成字符串存入列表
            s = "".join(t)  # 拼接成新的数字串，进入下一轮
        return s  # 返回最终的数字串
