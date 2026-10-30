# 题目：672. 灯泡开关 Ⅱ（Bulb Switcher II）
# 思路：最终状态只取决于四种操作各被按了奇数次还是偶数次；前 6 盏灯即可代表全部，故枚举 16 种组合并用位掩码去重。
# 时间复杂度：O(1)，固定枚举 16 种组合；空间复杂度：O(1)，集合最多保存 16 个状态。
class Solution:  # LeetCode 约定的题解类
    def flipLights(self, n: int, presses: int) -> int:  # n：灯泡个数；presses：必须按下的总次数
        ops = (0b111111, 0b010101, 0b101010, 0b100100)  # 四种操作对前 6 盏灯的翻转掩码（位 5 是第 1 盏，位 0 是第 6 盏）
        n = min(n, 6)  # 每 6 盏灯一个周期，超过 6 的部分状态重复，可截断
        vis = set()  # 收集可达状态，自动去重
        for mask in range(1 << 4):  # 枚举 4 种操作选或不选的全部 16 种组合
            cnt = mask.bit_count()  # 本组合实际按下的次数
            if cnt <= presses and cnt % 2 == presses % 2:  # 次数不超标且奇偶一致时，组合才可达
                t = 0  # 本组合得到的状态掩码
                for i, op in enumerate(ops):  # 逐种操作判断是否被选中
                    if (mask >> i) & 1:  # 第 i 位为 1 表示选用这种操作
                        t ^= op  # 异或等价于叠加一次翻转
                t &= (1 << 6) - 1  # 只保留低 6 位
                t >>= 6 - n  # 右移只留下前 n 盏灯对应的位
                vis.add(t)  # 记录该可达状态
        return len(vis)  # 不同状态的数量即为答案
