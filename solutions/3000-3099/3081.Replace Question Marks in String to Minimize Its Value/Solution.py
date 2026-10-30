# 题目：3081. 替换字符串中的问号使分数最小（Replace Question Marks in String to Minimize Its Value）
# 思路：用小根堆每次取 (频次最小, 字母最小) 的字母分配给一个问号，收集 k 个字母后升序排列按序填回，即可得到字典序最小的结果。
# 时间复杂度：O(n + k log 26 + k log k)，每个问号一次堆操作；空间复杂度：O(n)，结果串与字母计数。
class Solution:  # LeetCode 约定的题解类
    def minimizeStringValue(self, s: str) -> str:  # s 中含有 '?'，用尽量小的字母替换使它分数最小，返回字典序最小的结果
        cnt = Counter(s)  # 统计原串中每个字符的出现次数
        pq = [(cnt[c], c) for c in ascii_lowercase]  # 把 26 个字母的 (频次, 字母) 组成列表
        heapify(pq)  # 原地建小根堆：堆顶是频次最小、字母也最小的候选
        t = []  # t 依次保存每个问号最终要填入的字母
        for _ in range(s.count("?")):  # 问号有几个，就贪心地选几次字母
            v, c = pq[0]  # v 是堆顶的当前最小频次，c 是对应字母
            t.append(c)  # 把这个字母分配给一个问号
            heapreplace(pq, (v + 1, c))  # 弹出堆顶并把频次加一后重新入堆
        t.sort()  # 选出的字母升序排列，按序填入问号即得字典序最小
        cs = list(s)  # 转成列表以便按下标修改字符
        j = 0  # j 指向 t 中下一个待填入的字母
        for i, c in enumerate(s):  # 第二次遍历：找出并替换所有问号
            if c == "?":  # 只处理问号位置
                cs[i] = t[j]  # 用贪心选出的字母替换该问号
                j += 1  # 指针后移，准备填下一个问号
        return "".join(cs)  # 拼回字符串返回
