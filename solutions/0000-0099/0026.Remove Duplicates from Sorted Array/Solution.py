# 题目：26. 删除有序数组中的重复项（Remove Duplicates from Sorted Array）
# 思路：双指针原地覆盖。k 是已去重区间的长度（下一个可写位置），顺序遍历每个元素 x，只要它不等于已保留的最后一个值 nums[k-1] 就写到 k 位置。数组有序保证重复项相邻。
# 时间复杂度：O(n)，每个元素只访问一次；空间复杂度：O(1)，只用常数个额外变量，结果原地写在 nums 里。
class Solution:  # LeetCode 约定的题解类
    def removeDuplicates(self, nums: List[int]) -> int:  # nums：升序数组（原地修改），返回去重后的长度
        k = 0  # k 既是已保留的不重复元素个数，也是下一个待写入的位置下标
        for x in nums:  # 顺序遍历当前元素 x；因为 k 不大于当前下标，写 nums[k] 不会覆盖后续元素
            if k == 0 or x != nums[k - 1]:  # 第一个元素直接保留；否则与已保留的最后一个值比较，不同才是新值
                nums[k] = x  # 把新值放到前 k 个有效元素之后
                k += 1  # 有效长度加一，写指针后移
        return k  # 返回去重后的长度
