# 3397. 执行操作后不同元素的最大数量 / Maximum Number of Distinct Elements After Operations
# 核心思路：先排序，再贪心地从小到大为每个元素取 [x-k, x+k] 内大于上一个已占用值的最小值，取得到就贡献一个不同元素
# 复杂度：时间 O(n log n)（排序主导）、空间 O(1)（不计排序开销）
class Solution:  # 定义 Solution 类
    def maxDistinctElements(self, nums: List[int], k: int) -> int:  # 求执行操作后不同元素的最大数量
        nums.sort()  # 升序排序，便于从左到右贪心分配
        ans = 0  # 记录不同元素个数
        pre = -inf  # 记录上一个已被占用的值，初始为负无穷
        for x in nums:  # 按从小到大依次处理每个元素
            cur = min(x + k, max(x - k, pre + 1))  # 在可取值区间 [x-k, x+k] 内贪心地取大于 pre 的最小值
            if cur > pre:  # 取到的值大于 pre，说明可以新增一个不同元素
                ans += 1  # 不同元素个数加一
                pre = cur  # 更新已被占用的最大值
        return ans  # 返回答案
