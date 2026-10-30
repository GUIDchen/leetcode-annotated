# 题目：2779. 数组的最大美丽值（Maximum Beauty of an Array After Applying Operation）
# 思路：每个元素 x 最多变成区间 [x - k, x + k] 中的任意值，能被变成同一个值等价于这些区间有公共交点；用差分数组在数值轴上统计区间覆盖数，前缀和的最大值就是答案。
# 时间复杂度：O(n + m)，m 是数值轴长度（与最大值和 k 成正比）；空间复杂度：O(m)，差分数组大小为 m。
class Solution:  # LeetCode 约定的题解类
    def maximumBeauty(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是每个元素最多可加/减的次数
        m = max(nums) + k * 2 + 2  # 数值轴长度：覆盖到最大值 + k*2 后再多留 2 格，防止下标越界
        d = [0] * m  # 差分数组：d[v] 记录数值 v 处区间覆盖数的增量
        for x in nums:  # 把每个元素可取值域 [x - k, x + k] 的贡献打到差分数组上
            d[x] += 1  # 区间左端点：覆盖数从 x 处开始加一
            d[x + k * 2 + 1] -= 1  # 区间右端点后一格：覆盖数在此处减一，区间长度为 2k + 1
        return max(accumulate(d))  # 对差分数组求前缀和，其最大值即最多有多少个元素能变成同一个值
