# 题目：3452. 好数字之和（Sum of Good Numbers）
# 思路：所谓好数字，就是它严格大于下标差 k 的左右邻居（邻居越界时视为不存在）。逐个下标检查：只要存在越界约束之外的邻居不比它小，就跳过；两侧都满足才把它累加进答案。
# 时间复杂度：O(n)，每个下标只做常数次比较；空间复杂度：O(1)，只用了一个累加变量。
class Solution:  # LeetCode 约定的题解类
    def sumOfGoodNumbers(self, nums: List[int], k: int) -> int:  # nums：目标数组；k：邻居下标距离；返回所有好数字之和
        ans = 0  # ans 累加所有好数字的值
        for i, x in enumerate(nums):  # i 是下标，x 是 nums[i]，逐个检查它是否为好数字
            if i >= k and x <= nums[i - k]:  # 左邻居存在时，x 必须严格大于它
                continue  # 不比左邻居大，不是好数字，跳过
            if i + k < len(nums) and x <= nums[i + k]:  # 右邻居存在时，x 也必须严格大于它
                continue  # 不比右邻居大，不是好数字，跳过
            ans += x  # 两侧邻居都比它小（或不存在），把它计入答案
        return ans  # 返回所有好数字之和
