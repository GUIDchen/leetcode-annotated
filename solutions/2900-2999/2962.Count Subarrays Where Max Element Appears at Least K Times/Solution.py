# 题目：2962. 统计最大元素出现至少 K 次的子数组（Count Subarrays Where Max Element Appears at Least K Times）
# 思路：先求出数组最大值 mx，再用滑动窗口枚举左端点，右端点单调右移直到窗口内 mx 出现 k 次，累加合法右端点的个数。
# 时间复杂度：O(n)，右端点 j 只增不减，每个下标最多被扫过一次；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countSubarrays(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是最大元素至少要出现的次数，返回满足条件的子数组个数
        mx = max(nums)  # 先求出整个数组的最大值
        n = len(nums)  # 缓存数组长度，后面反复用到
        ans = cnt = j = 0  # ans 记录答案；cnt 是窗口内最大值个数；j 是窗口右端点（左闭右开）；一行同时初始化
        for x in nums:  # 枚举左端点，x 就是 nums[i]
            while j < n and cnt < k:  # 右端点不断右移，直到窗口内有 k 个最大值或者越界
                cnt += nums[j] == mx  # 布尔值参与加法：nums[j] 等于最大值就加 1
                j += 1  # 右端点后移一位
            if cnt < k:  # 右端点已到末尾仍不足 k 个，左端点再右移只会更少
                break  # 提前结束枚举
            ans += n - j + 1  # 窗口已满足条件，右端点取 j-1..n-1 都合法，共 n-j+1 个
            cnt -= x == mx  # 左端点右移：若离开窗口的 x 是最大值就减掉
        return ans  # 返回答案
