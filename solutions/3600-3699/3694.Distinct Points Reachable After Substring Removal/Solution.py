# 3694. Distinct Points Reachable After Substring Removal（3694. 删除子字符串后不同的终点）
# 核心思路：先求出每走一步后的前缀坐标；删掉长度恰为 k 的子串 [i-k+1, i] 后，终点 = 总位移 - 该子串的位移，把所有结果放进集合去重后计数。
# 复杂度：时间 O(n)，空间 O(n)，n 为字符串长度。
class Solution:  # 定义题解类
    def distinctPoints(self, s: str, k: int) -> int:  # 主函数：返回删除长度恰为 k 的子串后可能到达的不同终点个数
        n = len(s)  # n 为字符串长度
        f = [0] * (n + 1)  # f[i] 记录走完前 i 步后的横坐标
        g = [0] * (n + 1)  # g[i] 记录走完前 i 步后的纵坐标
        x = y = 0  # 当前坐标为 (x, y)
        for i, c in enumerate(s, 1):  # 逐字符模拟行走，起始下标取 1
            if c == "U":  # 向上走，纵坐标加一
                y += 1  # 纵坐标 +1
            elif c == "D":  # 向下走，纵坐标减一
                y -= 1  # 纵坐标 -1
            elif c == "L":  # 向左走，横坐标减一
                x -= 1  # 横坐标 -1
            else:  # 其余情况（'R'）向右走
                x += 1  # 横坐标 +1
            f[i] = x  # 记录走完前 i 步后的横坐标
            g[i] = y  # 记录走完前 i 步后的纵坐标
        st = set()  # 用元组作坐标，集合自动去重
        for i in range(k, n + 1):  # 枚举被删除的长度为 k 的区间右端点 i
            a = f[n] - (f[i] - f[i - k])  # 新终点横坐标 = 全程位移 - 被删区间位移
            b = g[n] - (g[i] - g[i - k])  # 新终点纵坐标 = 全程位移 - 被删区间位移
            st.add((a, b))  # 把坐标加入集合
        return len(st)  # 集合大小就是不同终点的个数
