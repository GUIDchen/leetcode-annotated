# 题目：3921. 分数验证器（Score Validator）
# 思路：按题意从左到右模拟：数字事件把数值加进总分，"W" 只累加计数器并在到达 10 时立即停止，其余事件（WD/NB）各加 1 分。
# 时间复杂度：O(n)，每个事件只处理一次；空间复杂度：O(1)，只用 score 与 counter 两个变量。
class Solution:  # LeetCode 约定的题解类
    def scoreValidator(self, events: list[str]) -> list[int]:  # events：事件数组，返回 [总分, 计数器]
        score = counter = 0  # 总分与计数器同时初始化为 0
        for event in events:  # 从左到右依次处理每个事件
            if event.isdigit():  # 事件是纯数字字符串，属于可加分事件
                score += int(event)  # 转成整数累加进总分
            elif event == "W":  # 三振事件：只累加计数器，不加分
                counter += 1  # 计数器加一
                if counter == 10:  # 计数器到达 10
                    break  # 立刻停止处理后面的事件
            else:  # 剩下的是 "WD"、"NB" 这类事件
                score += 1  # 这类事件各加 1 分
        return [score, counter]  # 按题目要求返回总分与计数器
