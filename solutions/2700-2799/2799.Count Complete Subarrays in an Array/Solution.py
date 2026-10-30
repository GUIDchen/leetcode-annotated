# 题目：2799. 统计完全子数组的数目（Count Complete Subarrays in an Array）
# 思路：先求整个数组的元素种类数 cnt，再枚举起点 i 用集合向右扩展，集合大小等于 cnt 即为完全子数组。
# 时间复杂度：O(n^2)，最坏情况枚举所有子数组；空间复杂度：O(n)，集合最多保存 n 个不同的值。
class Solution:  # LeetCode 约定的题解类
    def countCompleteSubarrays(self, nums: List[int]) -> int:  # nums：输入数组；返回完全子数组的个数
        cnt = len(set(nums))  # 整个数组的元素种类数，子数组必须覆盖全部这些种类
        ans, n = 0, len(nums)  # ans：答案计数器；n：数组长度
        for i in range(n):  # 枚举子数组的左端点 i
            s = set()  # 每个起点各用一个空集合，统计以 i 为起点的子数组包含的种类
            for x in nums[i:]:  # 从 i 开始向右逐个取元素，等价于枚举右端点 j（切片会复制一份，不影响结果）
                s.add(x)  # 把当前元素加入集合
                if len(s) == cnt:  # 种类数达到全局种类数，说明该子数组是「完全子数组」
                    ans += 1  # 答案加一
        return ans  # 返回完全子数组的总数
