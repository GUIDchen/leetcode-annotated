# 题目：735. 小行星碰撞（Asteroid Collision）
# 思路：用列表当栈——正数直接入栈；负数循环撞碎比自己小的栈顶正数，相等则同归于尽，威胁清空后自身入栈。
# 时间复杂度：O(n)，每个小行星最多入栈、出栈各一次；空间复杂度：O(n)，栈最多保存 n 个小行星。
class Solution:  # LeetCode 约定的题解类
    def asteroidCollision(self, asteroids: List[int]) -> List[int]:  # asteroids：按飞行顺序排列的小行星（正数向右、负数向左）
        stk = []  # 用 Python 列表模拟栈，保存碰撞后仍存活且自左向右不会再相撞的星球
        for x in asteroids:  # 按给定顺序从左到右遍历每个小行星
            if x > 0:  # 正数向右飞，不会主动撞到左边的星球，直接入栈
                stk.append(x)  # 入栈，成为右侧星球可能的碰撞对象
            else:  # x < 0：向左飞，可能与栈顶向右飞的星球相撞
                while stk and stk[-1] > 0 and stk[-1] < -x:  # 栈顶向右且体积更小 → 栈顶被撞碎；循环直到栈空或撞不动
                    stk.pop()  # 弹出被撞碎的栈顶星球
                if stk and stk[-1] == -x:  # 栈顶与当前星球大小相同：两者同归于尽
                    stk.pop()  # 弹出栈顶，当前星球也一起消失，不再入栈
                elif not stk or stk[-1] < 0:  # 栈空或栈顶也向左飞：两者永远不会相撞，当前星球存活
                    stk.append(x)  # 当前星球入栈，继续向右推进
        return stk  # 栈中剩下的元素就是最终答案
