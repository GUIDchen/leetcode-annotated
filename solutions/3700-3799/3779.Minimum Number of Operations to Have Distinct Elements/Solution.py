# 3779. 得到互不相同元素的最少操作次数 / Minimum Number of Operations to Have Distinct Elements
# 核心思路：每次操作删除末尾三个元素，所以从后往前扫描并记录出现过的值，第一次遇到重复值的位置 i 决定必须删到哪一组，返回 i//3+1。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为数组长度。
class Solution:  # 定义题解类
    def minOperations(self, nums: List[int]) -> int:  # 返回使剩余前缀元素互不相同的最少操作次数
        st = set()  # 记录从后往前已经出现过的不同元素
        for i in range(len(nums) - 1, -1, -1):  # 从后往前扫描，模拟每次删掉末尾三个元素
            if nums[i] in st:  # 该元素在前缀里重复出现
                return i // 3 + 1  # 需要删掉它所在的整组及其后元素
            st.add(nums[i])  # 记录该元素已出现
        return 0  # 没有重复元素，无需任何操作
