# 题目：3864. 划分二进制字符串的最小费用（Minimum Cost to Partition a Binary String）
# 思路：前缀和统计任意分段的 '1' 个数，再递归分治：每个分段要么直接按规则计价，要么在长度为偶数时对半拆分，取两者较小值。
# 时间复杂度：O(n)，分治树共 O(n) 个结点、每个结点 O(1)；空间复杂度：O(n)，前缀和数组加 O(log n) 递归栈。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, s: str, encCost: int, flatCost: int) -> int:  # s：二进制串；encCost：敏感元素单价；flatCost：全 0 分段的固定费用
        def dfs(l: int, r: int) -> int:  # 递归求半开区间 s[l:r] 这一段的最小费用（用到外层的前缀和 pre）
            x = pre[r] - pre[l]  # 该分段中 '1' 的个数
            res = (r - l) * x * encCost if x else flatCost  # 不拆分时的费用：有 1 按长度×个数×单价，全 0 按 flatCost
            if (r - l) % 2 == 0:  # 只有长度为偶数的分段才允许对半拆分
                m = (l + r) // 2  # 取中点，分成 [l, m) 与 [m, r) 两段
                res = min(res, dfs(l, m) + dfs(m, r))  # 拆分费用等于两半各自最优费用之和，与不拆分取较小者
            return res  # 返回该分段的最小费用

        n = len(s)  # 字符串长度
        pre = [0] * (n + 1)  # 前缀和：pre[i] 表示 s[:i] 中 '1' 的个数
        for i, c in enumerate(s, 1):  # 下标从 1 开始，与前缀和数组对齐
            pre[i] = pre[i - 1] + int(c)  # 累加当前位是否为 '1'
        return dfs(0, n)  # 整串作为初始分段，答案为它的最小费用
