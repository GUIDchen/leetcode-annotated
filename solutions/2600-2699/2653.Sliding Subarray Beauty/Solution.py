# 题目：2653. 滑动子数组的美丽值（Sliding Subarray Beauty）
# 思路：维护长度 k 的滑动窗口与值域计数桶，每次在桶中从小到大找第 x 个数；负数不足 x 个时美丽值为 0。
# 时间复杂度：O(n × 50)，50 是值域常数，每个窗口扫一遍桶；空间复杂度：O(n + 101)，答案数组与计数桶。
class Solution:  # LeetCode 约定的题解类
    def getSubarrayBeauty(self, nums: List[int], k: int, x: int) -> List[int]:  # nums：原数组；k：窗口长度；x：第 x 小；返回每个窗口的美丽值
        def f(x: int) -> int:  # 求第 x 小的负数；cnt 在后面定义，调用时才解析闭包
            s = 0  # 目前累计到的元素个数
            for i in range(50):  # 只扫负数区间：下标 0..49 对应 -50..-1
                s += cnt[i]  # 把当前值的计数累加进来
                if s >= x:  # 累计个数达到 x，当前值就是第 x 小
                    return i - 50  # 桶下标减 50 还原真实数值
            return 0  # 负数不足 x 个，按定义美丽值为 0

        cnt = [0] * 101  # 值域桶：下标 = 数值 + 50，覆盖 -50..50
        for v in nums[:k]:  # 统计第一个长度为 k 的窗口
            cnt[v + 50] += 1  # 数值映射成桶下标后计数加一
        ans = [f(x)]  # 第一个窗口的美丽值
        for i in range(k, len(nums)):  # 窗口右移，i 是新进窗口的元素下标
            cnt[nums[i] + 50] += 1  # 新元素进窗口
            cnt[nums[i - k] + 50] -= 1  # 最左侧元素移出窗口
            ans.append(f(x))  # 计算并追加新窗口的美丽值
        return ans  # 返回所有窗口的美丽值
