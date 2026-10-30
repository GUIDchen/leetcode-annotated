# 题目：2909. 元素和最小的山形三元组 II（Minimum Sum of Mountain Triplets II）
# 核心思路：与 2908 同题不同数据规模，先预处理后缀最小值，再用滚动的前缀最小值枚举峰值，判断两侧是否都存在更小的元素。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，后缀最小值数组 right。
class Solution:  # LeetCode 约定的题解类
    def minimumSum(self, nums: List[int]) -> int:  # nums 是输入数组，返回最小山形三元组的元素和
        n = len(nums)  # 数组长度
        right = [inf] * (n + 1)  # right[i] 表示 nums[i:] 的最小值，多开一位并把末位设为 inf
        for i in range(n - 1, -1, -1):  # 从右往左递推后缀最小值
            right[i] = min(right[i + 1], nums[i])  # 后缀最小值取「右侧后缀最小值」与「当前元素」中的较小者
        ans = left = inf  # ans 存答案，left 存前缀最小值，都从 inf 开始
        for i, x in enumerate(nums):  # 正序枚举峰值位置 i 与对应元素 x
            if left < x and right[i + 1] < x:  # 左右两侧最小值都严格小于 x 才构成山形
                ans = min(ans, left + x + right[i + 1])  # 用三数之和更新最小值
            left = min(left, x)  # 当前元素并入前缀最小值，供后面的位置使用
        return -1 if ans == inf else ans  # 没找到合法三元组时返回 -1
