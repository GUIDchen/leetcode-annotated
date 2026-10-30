# 题目：3347. 执行操作后元素的最高频率 II（Maximum Frequency of an Element After Performing Operations II）
# 思路：每个 nums[i] 都能通过一次操作变成 [x-k, x+k] 内任意值，用差分事件表统计能落到某值上的元素个数，再与「原本次数 + 操作次数上限」取小。
# 时间复杂度：O(n log n)（排序事件表 O(n log n)）；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:  # k：每次操作可增减的最大幅度；numOperations：最多可执行的操作次数
        cnt = defaultdict(int)  # 每个值在原数组中出现的次数（这些元素不需要消耗操作）
        d = defaultdict(int)  # 差分事件表：坐标 -> 事件增量
        for x in nums:  # 为每个元素建立它能够覆盖到的区间
            cnt[x] += 1  # 统计原值出现次数
            d[x] += 0  # 在 x 处建一个 0 值事件，保证扫描时能取到坐标 x，且不影响前缀和
            d[x - k] += 1  # 区间左端：从 x-k 开始该元素可以被凑出
            d[x + k + 1] -= 1  # 区间右端后一位：x+k 之后不再覆盖
        ans = s = 0  # ans 存最优答案；s 是差分前缀和，即能变成当前坐标的元素个数
        for x, t in sorted(d.items()):  # 按坐标升序扫描事件表
            s += t  # 前缀和等于能变成 x 的元素个数
            ans = max(ans, min(s, cnt[x] + numOperations))  # 原本是 x 的元素不耗操作，其余每个最多用一次操作且受总次数限制
        return ans  # 返回最高频率
