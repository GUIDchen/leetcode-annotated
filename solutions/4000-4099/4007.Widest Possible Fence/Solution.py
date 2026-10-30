# 题目：4007. 栅栏的最宽宽度（Widest Possible Fence）
# 思路：木板只能单块使用、两块同长拼成 2x、或两种长度拼成 x+y，所以候选宽度必为 x、2x、x+y；先按长度分组计数，再枚举基准长度 x，把每种宽度能提供的条数累加到 t，取最大值。
# 时间复杂度：O(k^2)，k 为不同长度的种数；空间复杂度：O(k)，两个哈希表分别存长度计数与宽度计数。
class Solution:  # LeetCode 约定的题解类
    def maximumWidth(self, planks: list[int]) -> int:  # planks：每块木板的长度；返回能拼出的最大宽度
        cnt = Counter(planks)  # 统计每种长度的木板块数
        ans = 0  # ans 记录最大宽度（最终由 t 的最大值给出）
        t = defaultdict(int)  # 宽度 → 能拼成该宽度的木板条数，缺失时默认 0
        for x, v1 in cnt.items():  # 枚举作为基准的长度 x 及其数量 v1
            t[x] += v1  # 单块 x 自身就能拼成宽度 x
            t[x * 2] += v1 // 2  # 两块 x 首尾相接拼成宽度 2x，贡献 v1 // 2 条
            for y, v2 in cnt.items():  # 再枚举另一种长度 y 与 x 配对
                if y > x:  # 只处理 y > x，避免同一对长度重复统计
                    t[x + y] += min(v1, v2)  # 配对条数受两种长度数量的较小值限制
        return max(t.values())  # 所有宽度中条数的最大值就是栅栏的最宽宽度
