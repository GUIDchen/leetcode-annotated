# 题目：164. 最大间距（Maximum Gap）
# 核心思路：按平均间距把值域分桶，只记录每桶的最小值和最大值；最大间距必然出现在相邻非空桶之间，因此一趟分桶即可线性求解。
# 时间复杂度：O(n)，三趟线性遍历；空间复杂度：O(n)，桶列表随元素个数增长。
class Solution:  # LeetCode 约定的题解类
    def maximumGap(self, nums: List[int]) -> int:  # 返回升序排列后相邻元素的最大差值
        n = len(nums)  # 元素个数
        if n < 2:  # 少于两个元素时不存在间距
            return 0  # 按题目要求返回 0
        mi, mx = min(nums), max(nums)  # 一次遍历求出值域两端，避免重复扫描
        bucket_size = max(1, (mx - mi) // (n - 1))  # 桶宽取平均间距向下取整，至少为 1 避免除以 0
        bucket_count = (mx - mi) // bucket_size + 1  # 覆盖整个值域所需的桶数
        buckets = [[inf, -inf] for _ in range(bucket_count)]  # 每桶记录 [最小值, 最大值]，inf 表示空桶
        for v in nums:  # 把所有元素分配到桶中
            i = (v - mi) // bucket_size  # 数值到桶下标的线性映射
            buckets[i][0] = min(buckets[i][0], v)  # 维护桶内最小值
            buckets[i][1] = max(buckets[i][1], v)  # 维护桶内最大值
        ans = 0  # 最大间距，最小也是 0
        prev = inf  # 上一个非空桶的最大值；inf 占位让首个桶的差值为负，不影响答案
        for curmin, curmax in buckets:  # 按值域顺序扫描所有桶
            if curmin > curmax:  # 最小值仍大于最大值，说明该桶没有元素
                continue  # 跳过空桶
            ans = max(ans, curmin - prev)  # 间距只可能出现在相邻非空桶之间
            prev = curmax  # 用当前桶最大值作为下一次比较的基准
        return ans  # 返回最大间距
