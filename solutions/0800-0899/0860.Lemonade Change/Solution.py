# 题目：860. 柠檬水找零（Lemonade Change）
# 思路：贪心。按顺序模拟找零，尽量保留更灵活的 5 元：付 10 元找 5 元，付 20 元优先「10 元 + 5 元」，不够再用三张 5 元。
# 时间复杂度：O(n)，n 为顾客人数；空间复杂度：O(1)，只维护 5 元与 10 元的张数。
class Solution:  # LeetCode 约定的题解类
    def lemonadeChange(self, bills: List[int]) -> bool:  # bills：顾客依次支付的钞票面额，返回能否全部找开
        five = ten = 0  # 同时初始化手中 5 元与 10 元的张数为 0
        for v in bills:  # 按时间顺序处理每一位顾客
            if v == 5:  # 顾客付 5 元，无需找零
                five += 1  # 直接收下一张 5 元
            elif v == 10:  # 顾客付 10 元，需要找回 5 元
                ten += 1  # 收下一张 10 元
                five -= 1  # 找出一张 5 元
            else:  # 顾客付 20 元，需要找回 15 元
                if ten:  # 手里还有 10 元时优先用它，保留更灵活的 5 元
                    ten -= 1  # 找出一张 10 元
                    five -= 1  # 再找出一张 5 元
                else:  # 没有 10 元，只能全部用 5 元凑 15 元
                    five -= 3  # 一次性找出三张 5 元
            if five < 0:  # 检查 5 元是否被找成负数，即刚才的找零失败
                return False  # 立刻判定无法完成
        return True  # 所有顾客都成功找零
