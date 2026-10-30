# 题目：1776. 车队 II（Car Fleet II）
# 思路：从右向左扫描，用单调栈维护「可能被追尾」的车；栈顶若已被别人追尾过早，则当前车追不上它，弹掉；否则追尾时间就是距离除以相对速度。
# 时间复杂度：O(n)，每辆车最多入栈出栈一次；空间复杂度：O(n) 存放答案与栈。
class Solution:  # LeetCode 约定的题解类
    def getCollisionTimes(self, cars: List[List[int]]) -> List[float]:  # cars：按位置升序的 [位置, 速度] 列表
        stk = []  # 单调栈：保存可能被追尾的车的下标
        n = len(cars)  # 车的数量
        ans = [-1] * n  # 答案：每辆车的追尾时间，-1 表示永远追不上
        for i in range(n - 1, -1, -1):  # 从最右端向左扫描
            while stk:  # 不断检查栈顶候选
                j = stk[-1]  # 栈顶候选前车的下标
                if cars[i][1] > cars[j][1]:  # 当前车更快才可能追上
                    t = (cars[j][0] - cars[i][0]) / (cars[i][1] - cars[j][1])  # 追尾时间 = 距离 / 相对速度
                    if ans[j] == -1 or t <= ans[j]:  # 追上时前车尚未追尾别人（或恰好同时）才有效
                        ans[i] = t  # 记录当前车的追尾时间
                        break  # 找到有效目标就跳出
                stk.pop()  # 追不上或前车会先追尾别人：弹出该候选
            stk.append(i)  # 当前车入栈，供左侧车辆使用
        return ans  # 返回结果
