# 题目：3073. 最大递增三元组（Maximum Increasing Triplet Value）🔒
# 思路：先预处理后缀最大值 right，再用有序列表 SortedList 维护前缀，枚举中间下标 j 并二分找最优的 nums[i]。
# 时间复杂度：O(n log n)，每次二分与插入都是对数级；空间复杂度：O(n)，后缀最大值数组与有序列表。
class Solution:  # LeetCode 约定的题解类
    def maximumTripletValue(self, nums: List[int]) -> int:  # nums：输入数组；返回最大的 nums[i] - nums[j] + nums[k]（要求 i<j<k 且 nums[i]<nums[j]<nums[k]）
        n = len(nums)  # 数组长度，后面会反复用到
        right = [nums[-1]] * n  # right[i] 将表示从 i 到末尾的最大值，先统一初始化为末尾元素
        for i in range(n - 2, -1, -1):  # 从倒数第二个位置倒序向前扫描
            right[i] = max(nums[i], right[i + 1])  # 后缀最大值递推：取自身与右侧最大值中的较大者
        sl = SortedList([nums[0]])  # 有序列表：保存已经扫描过的前缀元素，支持对数级二分
        ans = 0  # 记录最大三元组值，初始为 0
        for j in range(1, n - 1):  # 枚举中间下标 j；左右两侧都要有元素，所以范围是 [1, n-2]
            if right[j + 1] > nums[j]:  # 右侧必须存在严格大于 nums[j] 的元素，才可能构成递增三元组
                i = sl.bisect_left(nums[j]) - 1  # 第一个大于等于 nums[j] 的位置再左移一位，就是严格小于它的最大前缀值
                if i >= 0:  # 下标合法说明左边确实存在更小的元素，可以作为 nums[i]
                    ans = max(ans, sl[i] - nums[j] + right[j + 1])  # 用当前的 i、j、k 更新答案
            sl.add(nums[j])  # 把当前元素加入有序列表，供后面的中间下标使用
        return ans  # 返回最大三元组值
