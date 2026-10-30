# 题目：686. 重复叠加字符串匹配（Repeated String Match）
# 思路：先把 a 叠加到长度不小于 b，再多试 2 次以覆盖起点错位的情形；每次判断 b 是否为子串，都失败则返回 -1。
# 时间复杂度：O(n·m)，每次子串匹配 O(n·m)，常数次匹配；空间复杂度：O(n)，需要保存叠加后的字符串。
class Solution:  # LeetCode 约定的题解类
    def repeatedStringMatch(self, a: str, b: str) -> int:  # a 是用于重复的字符串，b 是目标子串
        m, n = len(a), len(b)  # m 是 a 的长度，n 是 b 的长度
        ans = ceil(n / m)  # 向上取整：至少需要叠加几次，长度才够 b
        t = [a] * ans  # 用列表存每一份 a，避免反复拼接字符串带来的开销
        for _ in range(3):  # 最多再多试 2 次，覆盖起点错位的情况
            if b in ''.join(t):  # 把列表拼成一个字符串，判断 b 是否为其子串
                return ans  # 找到就返回当前的叠加次数
            ans += 1  # 叠加次数加一
            t.append(a)  # 再追加一份 a 后继续检查
        return -1  # 试满仍找不到，返回 -1
