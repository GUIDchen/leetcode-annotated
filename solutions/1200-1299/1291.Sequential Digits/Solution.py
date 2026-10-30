# 题目：1291. 顺次数（Sequential Digits）
# 核心思路：枚举起始数字与依次拼接的后续数字，构造出全部顺次数，筛出落在 [low, high] 内的并按升序返回。
# 时间复杂度：O(1)，顺次数总量固定（本代码只生成 36 个）；空间复杂度：O(1)，答案规模为常数。
class Solution:  # LeetCode 约定的题解类
    def sequentialDigits(self, low: int, high: int) -> List[int]:  # 题解方法对外可见
        ans = []  # low、high 是取值区间，返回区间内所有「顺次数」（相邻数位依次加一）
        for i in range(1, 9):  # ans 收集所有满足区间的顺次数
            x = i  # 枚举起始数字 1..8；起始为 9 时后面无数字可接，故不取 9
            for j in range(i + 1, 10):  # x 从单个数字 i 开始，往后不断拼接连续数字
                x = x * 10 + j  # 枚举下一个要拼上的数字 j
                if low <= x <= high:  # 在末尾拼接数字 j，相当于长度加一
                    ans.append(x)  # 判断拼出的数是否落在 [low, high] 内
        return sorted(ans)  # 落在区间内，加入答案
