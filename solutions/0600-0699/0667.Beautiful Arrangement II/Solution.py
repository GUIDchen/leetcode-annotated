# 题目：667. 优美的排列 II（Beautiful Arrangement II）
# 思路：前 k 个位置左右交替取最小/最大值，得到 k 个不同的相邻差 k, k-1, …, 1；其余位置单调填充，差值恒为 1。
# 时间复杂度：O(n)，两个循环共扫 n 次；空间复杂度：O(n)，结果列表。
class Solution:  # LeetCode 约定的题解类
    def constructArray(self, n: int, k: int) -> List[int]:  # 构造 1..n 的排列，使相邻元素差值恰好有 k 种
        l, r = 1, n  # 双指针：l 是未用的最小值，r 是未用的最大值
        ans = []  # 结果列表，逐个 append
        for i in range(k):  # 前 k 个位置左右交替取值
            if i % 2 == 0:  # 偶数下标先取小端
                ans.append(l)  # 放入当前最小值
                l += 1  # 小指针右移
            else:  # 奇数下标取大端
                ans.append(r)  # 放入当前最大值
                r -= 1  # 大指针左移，使相邻差依次为 k, k-1, …, 1
        for i in range(k, n):  # 剩余位置单调填充，差值都是 1
            if k % 2 == 0:  # k 为偶数时上一轮停在大端侧
                ans.append(r)  # 从大端继续递减填入
                r -= 1  # 大指针左移
            else:  # k 为奇数时上一轮停在小端侧
                ans.append(l)  # 从小端继续递增填入
                l += 1  # 小指针右移
        return ans  # 返回构造结果
