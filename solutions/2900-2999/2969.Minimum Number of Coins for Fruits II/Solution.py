# 题目：2969. 购买水果需要的最少金币数 II（Minimum Number of Coins for Fruits II）
# 思路：从后往前 DP，f[i] = prices[i] + min(f[i+1..2i+1])，用单调递增双端队列维护窗口最小值。
# 时间复杂度：O(n)，每个下标最多进出队各一次；空间复杂度：O(n)（队列）。
class Solution:  # LeetCode 约定的题解类
    def minimumCoins(self, prices: List[int]) -> int:  # prices：每个水果的价格，返回最少金币数
        n = len(prices)  # n 为水果个数
        q = deque()  # 单调队列（存 1 基下标），队首对应窗口内最小的 f 值
        for i in range(n, 0, -1):  # 从后往前推，i 由 n 递减到 1
            while q and q[0] > i * 2 + 1:  # 买下 i 后可免费拿到到 2i，所以候选窗口是 [i+1, 2i+1]，超出上界的要从队首弹出
                q.popleft()  # 弹出已滑出窗口的下标
            if i <= (n - 1) // 2:  # 仅当 2i < n 时，后面还有需要花钱的水果
                prices[i - 1] += prices[q[0] - 1]  # 加上窗口内最小的 f 值（队首），prices 就地当作 f 数组
            while q and prices[q[-1] - 1] >= prices[i - 1]:  # 维护单调性：比当前值更大的尾部下标不可能再被选中
                q.pop()  # 从队尾弹出
            q.append(i)  # 当前下标入队，供更靠前的 i 使用
        return prices[0]  # f[1] 即从第 1 个水果买起的最少金币数
