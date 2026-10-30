# 题目：27. 移除元素（Remove Element）
# 思路：快慢双指针原地覆盖。慢指针 k 指向下一个可写位置，顺序遍历数组，凡是不等于 val 的元素都保留到 k 位置，等于 val 的元素则被后来的元素覆盖。
# 时间复杂度：O(n)，一趟遍历；空间复杂度：O(1)，只用常数个额外变量，结果原地写在 nums 里。
class Solution:  # LeetCode 约定的题解类
    def removeElement(self, nums: List[int], val: int) -> int:  # nums：待处理数组（原地修改）；val：要删除的值；返回剩余元素个数
        k = 0  # k 记录已保留的元素个数，也是下一个待写入的位置
        for x in nums:  # 顺序遍历当前元素 x；k 不大于当前下标，所以写 nums[k] 不会覆盖未读元素
            if x != val:  # 当前元素不是要删除的值，需要保留
                nums[k] = x  # 把它写到前 k 个有效元素之后
                k += 1  # 有效长度加一，写指针后移
        return k  # 返回保留下来的元素个数
