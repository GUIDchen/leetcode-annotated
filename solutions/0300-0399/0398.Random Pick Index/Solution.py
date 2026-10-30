# 题目：398. 随机数索引（Random Pick Index）
# 思路：蓄水池抽样。扫描数组，遇到第 n 个等于 target 的位置时以 1/n 的概率把它选为答案，使每个合法下标等概率被返回。
# 时间复杂度：O(n)，每次 pick 线性扫描一次；空间复杂度：O(1)，除保存数组外只用两个计数变量。
class Solution:  # LeetCode 约定的题解类
    def __init__(self, nums: List[int]):  # 构造函数：保存数组，供后续多次 pick 使用
        self.nums = nums  # 存为成员变量（List 由判题环境隐式导入）

    def pick(self, target: int) -> int:  # 随机返回 target 的某个下标，要求等概率
        n = ans = 0  # n 记录已遇到的 target 个数；ans 记录当前被选中的下标
        for i, v in enumerate(self.nums):  # 同时取得下标 i 与元素值 v
            if v == target:  # 只处理值等于 target 的位置
                n += 1  # 第 n 次遇到 target，计数加一
                x = random.randint(1, n)  # 在 [1, n] 中均匀随机取一个整数
                if x == n:  # 取到 n 的概率恰为 1/n
                    ans = i  # 以 1/n 的概率替换答案，这就是蓄水池抽样
        return ans  # 返回最终选中的下标


# 下面是 LeetCode 给出的调用示例（判题器代码，无需实现）：
# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
