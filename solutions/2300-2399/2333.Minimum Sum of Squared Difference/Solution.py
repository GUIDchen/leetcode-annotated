# 题目：2333. 最小差值平方和（Minimum Sum of Squared Difference）
# 思路：先用桶统计逐位绝对差的分布与总和；总差不超过 k 就全清零，否则从最大差值逐层往下削，优先削平大差值（对平方和收益最大）。
# 时间复杂度：O(n + M)，M = 10⁵ 为差值上界；空间复杂度：O(M)，计数桶。
class Solution:  # LeetCode 约定的题解类
    def minSumSquareDiff(  # 签名分多行书写
        self, nums1: List[int], nums2: List[int], k1: int, k2: int  # k1/k2 是两个数组各自允许的增减次数
    ) -> int:  # 返回调整后的最小平方和
        k = k1 + k2  # 两类操作对差值的效果相同，合并成总预算
        s = mx = 0  # s 是绝对差总和，mx 是最大差值，一行同时赋初值
        cnt = [0] * 100001  # 值域桶：下标是差值，元素是出现次数（差值不超过 10⁵）
        for a, b in zip(nums1, nums2):  # 逐位配对两个数组
            v = abs(a - b)  # 当前这一位的绝对差
            cnt[v] += 1  # 差值 v 的出现次数加一
            s += v  # 累加总差值
            mx = max(mx, v)  # 更新最大差值
        if s <= k:  # 总差值不超过预算，可以全部清零
            return 0  # 平方和为 0
        for v in range(mx, 0, -1):  # 从最大差值往下逐层削平
            if cnt[v] == 0:  # 该层没有元素
                continue  # 跳过空桶
            take = min(cnt[v], k)  # 本层最多能把 take 个差值从 v 降到 v-1
            k -= take  # 扣掉这些搬运消耗的预算
            cnt[v] -= take  # 差值 v 的个数减少
            cnt[v - 1] += take  # 被削平的元素落到 v-1 层
            if k == 0:  # 预算已经用完
                break  # 提前结束，不必再往下削
        return sum(v * v * cnt[v] for v in range(mx + 1))  # 逐桶累加 v² × 个数，得到最小平方和
