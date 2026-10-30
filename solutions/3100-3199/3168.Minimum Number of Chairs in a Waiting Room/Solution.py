# 题目：3168. 候诊室中的最少椅子数（Minimum Number of Chairs in a Waiting Room）
# 思路：按时间顺序模拟，维护「当前空椅子数」；有人进来而空椅子为 0 时新增一张，新增总数就是历史峰值。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用两个计数器。
class Solution:  # LeetCode 约定的题解类
    def minimumChairs(self, s: str) -> int:  # s 由 'E'（进门）与 'L'（离开）组成
        cnt = left = 0  # cnt：累计分配过的椅子数；left：当前空着的椅子数
        for c in s:  # 按时间顺序处理每个事件
            if c == "E":  # 有人进门
                if left:  # 还有空椅子（非 0 即真）可以直接坐
                    left -= 1  # 占用一张椅子
                else:  # 否则说明没有空椅子了
                    cnt += 1  # 只能新增一张椅子
            else:  # 否则就是 'L'，有人离开
                left += 1  # 空出一张椅子
        return cnt  # 分配过的椅子总数就是最少椅子数
