# 题目：2498. 青蛙过河 II（Frog Jump II）
# 思路：首段 stones[1]-stones[0] 去回都要跨越，其余石头只能隔一块跳，答案取所有隔块差与首段差的最大值。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxJump(self, stones: List[int]) -> int:  # stones 是升序的石头位置，返回来回过河所需的最小「最大跳跃长度」
        ans = stones[1] - stones[0]  # 相邻的第 0、1 块石头之间的差必须被跨越一次
        for i in range(2, len(stones)):  # 从第 2 块石头开始处理其余的隔块差
            ans = max(ans, stones[i] - stones[i - 2])  # 中间石头在去程或回程中被占用，只能隔一块跳，取该差的最大值
        return ans  # 返回所有必要跳跃长度中的最大值，即最小的最大跳跃长度
