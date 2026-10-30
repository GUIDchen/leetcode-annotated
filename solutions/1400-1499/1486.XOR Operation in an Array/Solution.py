# 题目：1486. 数组异或操作（XOR Operation in an Array）
# 核心思路：用生成器按定义产出 start + 2*i，再用 reduce(xor) 把它们全部异或归约。
# 时间复杂度：O(n)，遍历 n 个元素；空间复杂度：O(1)，生成器不额外建数组。
class Solution:  # LeetCode 约定的题解类
    def xorOperation(self, n: int, start: int) -> int:  # n 为元素个数，start 为首项，后继元素公差为 2
        return reduce(xor, ((start + 2 * i) for i in range(n)))  # 生成等差数列 start+2i，再用异或运算归约成单个结果
