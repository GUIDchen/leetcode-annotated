# 3684. 至多 K 个不同元素的最大和 / Maximize Sum of At Most K Distinct Elements
# 核心思路：先升序排序，再从后往前挑选最大的 k 个互不相同的元素，跳过与后一位重复的值
# 时间复杂度 O(n log n)，空间复杂度 O(k)
class Solution:  # 题解类
    def maxKDistinct(self, nums: List[int], k: int) -> List[int]:  # 返回和最大的至多 k 个不同元素
        nums.sort()  # 升序排序，方便从最大值开始挑选
        n = len(nums)  # 数组长度
        ans = []  # 保存选出的答案
        for i in range(n - 1, -1, -1):  # 从末尾（最大值）向前遍历
            if i + 1 < n and nums[i] == nums[i + 1]:  # 与后一个位置的值重复，跳过以保证元素互不相同
                continue  # 继续看下一个更小的值
            ans.append(nums[i])  # 选入这个不重复的大值
            k -= 1  # 剩余可选个数减一
            if k == 0:  # 已选够 k 个
                break  # 提前结束
        return ans  # 返回选出的元素
