# 题目：384. 打乱数组（Shuffle an Array）
# 思路：构造时保存原始数组副本；shuffle 用 Fisher-Yates 洗牌，第 i 位与 [i, n-1] 中的随机位置交换。
# 时间复杂度：reset 为 O(n)，shuffle 为 O(n)；空间复杂度：O(n)，需要额外保存一份原始数组。
class Solution:  # 题解类，判题器会交替调用 reset 与 shuffle
    def __init__(self, nums: List[int]):  # 构造函数：nums 是初始数组
        self.nums = nums  # 保存当前（可变）的数组
        self.original = nums.copy()  # 复制一份原始数组，之后 shuffle 不会污染它

    def reset(self) -> List[int]:  # 恢复到初始排列并返回
        self.nums = self.original.copy()  # 用副本覆盖当前数组，保证每次 reset 都是全新列表
        return self.nums  # 返回恢复后的数组

    def shuffle(self) -> List[int]:  # 等概率地打乱当前数组并返回
        for i in range(len(self.nums)):  # Fisher-Yates：从左到右逐个确定每个位置上的元素
            j = random.randrange(i, len(self.nums))  # 在 [i, n-1] 中等概率挑一个下标 j
            self.nums[i], self.nums[j] = self.nums[j], self.nums[i]  # 交换后第 i 位定稿，不再参与后续洗牌
        return self.nums  # 返回打乱后的数组


# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.reset()
# param_2 = obj.shuffle()
