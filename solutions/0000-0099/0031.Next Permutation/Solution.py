# 题目：31. 下一个排列（Next Permutation）
# 思路：从右往左找第一个「升序对」的下标 i（nums[i] < nums[i+1]），再从右往左找第一个大于 nums[i] 的 nums[j] 并交换，最后把 i 右侧后缀反转成升序，即得下一个字典序排列；若整体降序则反转后变成最小排列。
# 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(1)，后缀切片会临时占用 O(n) 但算法本身原地改写 nums。
class Solution:  # LeetCode 约定的题解类
    def nextPermutation(self, nums: List[int]) -> None:  # nums：当前排列，原地修改成下一个排列，函数不需要返回值
        n = len(nums)  # 数组长度，用于确定扫描上界
        i = next((i for i in range(n - 2, -1, -1) if nums[i] < nums[i + 1]), -1)  # 从右往左找第一个升序对的下标；找不到说明整体降序，默认给 -1
        if ~i:  # ~i 非零等价于 i != -1，说明存在可以变大的位置
            j = next((j for j in range(n - 1, i, -1) if nums[j] > nums[i]))  # 从右往左找第一个大于 nums[i] 的元素，它一定存在
            nums[i], nums[j] = nums[j], nums[i]  # 交换两者，让第 i 位变成刚好更大的值
        nums[i + 1 :] = nums[i + 1 :][::-1]  # 把 i 后面的后缀反转成升序；i == -1 时从下标 0 开始，整体反转成最小排列
