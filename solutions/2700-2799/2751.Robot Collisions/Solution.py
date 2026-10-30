# 题目：2751. 机器人碰撞（Robot Collisions）
# 思路：按下标位置从左到右扫描，用栈保存仍向右走的机器人；遇到向左的机器人就与栈顶反复结算血量，最后收集存活者。
# 时间复杂度：O(n log n)，排序主导，每个机器人最多入栈出栈一次；空间复杂度：O(n)，栈与答案数组。
class Solution:  # LeetCode 约定的题解类
    def survivedRobotsHealths(self, positions, healths, directions):  # positions：位置；healths：血量；directions：方向；返回按原顺序的存活血量
        idx = sorted(range(len(positions)), key=lambda i: positions[i])  # 下标按位置升序排序，等价于把机器人从左到右排好
        stk = []  # 栈：存仍然向右走、可能与后面机器人碰撞的下标

        for i in idx:  # 按位置从左到右处理每个机器人
            if directions[i] == "R":  # 向右走：入栈等待右边向左的机器人
                stk.append(i)  # 记录该机器人
                continue  # 向右的机器人不会立即碰撞

            while stk and healths[i]:  # 当前向左的机器人未毁，且栈中还有向右的机器人
                j = stk[-1]  # 栈顶是最近的向右机器人
                if healths[j] > healths[i]:  # 栈顶血量更高：当前机器人被毁
                    healths[j] -= 1  # 栈顶掉 1 点血
                    healths[i] = 0  # 当前机器人血量置 0
                elif healths[j] < healths[i]:  # 当前机器人血量更高：栈顶被毁
                    healths[i] -= 1  # 当前机器人掉 1 点血，继续向左撞
                    healths[j] = 0  # 栈顶血量置 0
                    stk.pop()  # 被毁的栈顶出栈
                else:  # 双方血量相等：同归于尽
                    healths[i] = healths[j] = 0  # 双方血量都置 0
                    stk.pop()  # 栈顶出栈
                    break  # 当前机器人已毁，跳出内层循环

        return [h for h in healths if h > 0]  # 只保留血量大于 0 的机器人，顺序与原数组一致
