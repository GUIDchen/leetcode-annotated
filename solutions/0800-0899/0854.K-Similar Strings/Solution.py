# 题目：854. 相似度为 K 的字符串（K-Similar Strings）
# 思路：BFS 逐层扩展交换状态；每次固定最左侧的第一个不匹配位，只枚举能把它变正确的交换，剪掉无效分支。
# 时间复杂度：最坏 O(n · 状态数)，实际远小于全排列；空间复杂度：O(状态数)，队列与访问集合。
class Solution:  # 题解类
    def kSimilarity(self, s1: str, s2: str) -> int:  # s1 与 s2 是长度相同的字符异位串，返回最少交换次数
        def next(s):  # 生成 s 所有值得尝试的一次交换结果
            i = 0  # 指向第一个与 s2 不匹配的位置
            while s[i] == s2[i]:  # 跳过已经匹配的前缀
                i += 1  # 前进到下一位
            res = []  # 保存交换后的新串
            for j in range(i + 1, n):  # 在 i 之后尝试交换
                if s[j] == s2[i] and s[j] != s2[j]:  # 交换后 i 位能匹配且 j 位也能改善，交换才有效
                    res.append(s2[: i + 1] + s[i + 1 : j] + s[i] + s[j + 1 :])  # 用切片直接构造交换 i、j 两字符后的新串
            return res  # 返回这一层的所有后继状态

        q = deque([s1])  # BFS 队列，起点是 s1
        vis = {s1}  # 已访问状态集合，防止重复入队
        ans, n = 0, len(s1)  # ans 为交换次数，n 为串长
        while 1:  # 逐层扩展，题目保证可达所以不会死循环
            for _ in range(len(q)):  # 只处理当前这一层的所有状态
                s = q.popleft()  # 取队首状态
                if s == s2:  # 已经变成目标串
                    return ans  # 当前层数即最少交换次数
                for nxt in next(s):  # 枚举所有有效的一次交换结果
                    if nxt not in vis:  # 只处理没访问过的状态
                        vis.add(nxt)  # 标记为已访问
                        q.append(nxt)  # 入队，留待下一层扩展
            ans += 1  # 一层结束，交换次数加一
