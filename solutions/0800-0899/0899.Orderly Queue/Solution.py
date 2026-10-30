# 题目：899. 有序队列（Orderly Queue）
# 核心思路：k == 1 只能循环移位，枚举 n 种移位取最小；k >= 2 可任意交换字符，直接排序。
# 时间复杂度：k == 1 时 O(n^2)，k >= 2 时 O(n log n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def orderlyQueue(self, s: str, k: int) -> str:  # s：输入字符串；k：每次可移动的字符数
        if k == 1:  # 只能循环移位，逐个枚举取最小
            ans = s  # 用原串作为当前最优解
            for _ in range(len(s) - 1):  # 一共 n 种不同的循环移位，原串已比较过
                s = s[1:] + s[0]  # 首字符搬到末尾，得到下一个循环移位
                ans = min(ans, s)  # 保留字典序更小的那个
            return ans  # 返回最小的循环移位
        return "".join(sorted(s))  # k >= 2 时可任意交换，直接升序排列
