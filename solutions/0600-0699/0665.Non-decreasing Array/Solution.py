# 题目：665. 非递减数列（Non-decreasing Array）
# 思路：先找出第一处下降 nums[i] > nums[i+1]，只试两种改法（压低 nums[i]、抬高 nums[i+1]），再用辅助函数判断整体是否非递减。
# 时间复杂度：O(n)，最多两次线性扫描；空间复杂度：O(1)，只原地修改输入列表。
class Solution:  # LeetCode 约定的题解类
    def checkPossibility(self, nums: List[int]) -> bool:  # nums 是输入数组，判断最多改一个元素后能否非递减
        def is_sorted(nums: List[int]) -> bool:  # 辅助函数：判断序列是否非递减
            return all(a <= b for a, b in pairwise(nums))  # pairwise 把相邻元素两两配对，所有相邻对都满足 a <= b 即为非递减

        n = len(nums)  # 数组长度
        for i in range(n - 1):  # 从左往右扫描，找第一处下降
            a, b = nums[i], nums[i + 1]  # 下降处相邻的两个元素
            if a > b:  # 出现下降，必须修改其中一个
                nums[i] = b  # 方案一：把 nums[i] 改成更小的 b
                if is_sorted(nums):  # 检查改完后是否整体非递减
                    return True  # 方案一成立，立刻返回 True
                nums[i] = nums[i + 1] = a  # 方案二：撤销 nums[i]，改成把 nums[i+1] 抬到 a
                return is_sorted(nums)  # 只允许改一次，方案二成败就是最终答案
        return True  # 没有下降，本身已经非递减
