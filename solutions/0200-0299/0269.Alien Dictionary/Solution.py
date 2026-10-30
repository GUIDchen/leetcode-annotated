# 题目：269. 火星词典（Alien Dictionary）
# 思路：由相邻单词的第一个不同字母得到先后边，建图后做拓扑排序；成环或出现前缀矛盾则返回空串。
# 时间复杂度：O(C + 26²)，C 为所有单词总字符数；空间复杂度：O(26²)。
class Solution:  # LeetCode 约定的题解类
    def alienOrder(self, words: List[str]) -> str:  # words 已按外星字母序排好，返回还原出的字母顺序
        g = [[False] * 26 for _ in range(26)]  # 邻接矩阵：g[i][j] 为 True 表示字母 i 排在字母 j 前面
        s = [False] * 26  # s[i] 记录字母 i 是否在输入中出现过
        cnt = 0  # cnt 统计出现了多少种不同字母
        n = len(words)  # 单词个数
        for i in range(n - 1):  # 相邻两两比较，共 n-1 对
            for c in words[i]:  # 先登记当前单词里的所有字母
                if cnt == 26:  # 26 个字母齐了就不用再统计
                    break  # 跳出统计循环
                o = ord(c) - ord('a')  # ord 相减把字符映射成 0..25 的下标
                if not s[o]:  # 第一次见到该字母
                    cnt += 1  # 不同字母数加一
                    s[o] = True  # 标记为已出现
            m = len(words[i])  # 当前单词长度
            for j in range(m):  # 逐位比较当前单词和下一个单词
                if j >= len(words[i + 1]):  # 长词排在短词前面（前缀情形），顺序非法
                    return ''  # 直接返回空串
                c1, c2 = words[i][j], words[i + 1][j]  # 取同一位上的两个字母
                if c1 == c2:  # 相同则继续往后找第一个不同位
                    continue  # 跳过这一位
                o1, o2 = ord(c1) - ord('a'), ord(c2) - ord('a')  # 把两个字母都转成下标
                if g[o2][o1]:  # 已存在反向边，说明出现矛盾
                    return ''  # 返回空串
                g[o1][o2] = True  # 记录 c1 排在 c2 前面
                break  # 第一个不同位已确定关系，后面不再贡献边
        for c in words[n - 1]:  # 最后一个单词没有后继，单独补登记它的字母
            if cnt == 26:  # 26 个字母齐了就不再统计
                break  # 跳出统计循环
            o = ord(c) - ord('a')  # 字符转下标
            if not s[o]:  # 第一次见到该字母
                cnt += 1  # 计数加一
                s[o] = True  # 标记为已出现

        indegree = [0] * 26  # 统计每个字母的入度
        for i in range(26):  # 遍历所有起点字母
            for j in range(26):  # 遍历所有终点字母
                if i != j and s[i] and s[j] and g[i][j]:  # 只统计出现过的字母之间的边
                    indegree[j] += 1  # 终点入度加一
        q = deque()  # 拓扑排序用的双端队列
        ans = []  # 收集答案字符
        for i in range(26):  # 找初始入度为 0 的字母作为起点
            if s[i] and indegree[i] == 0:  # 必须是出现过且没有前驱的字母
                q.append(i)  # 入队
        while q:  # 队列非空就继续取出
            t = q.popleft()  # 取队首字母下标
            ans.append(chr(t + ord('a')))  # 转成字符追加到答案
            for i in range(26):  # 删除它的后继边
                if s[i] and i != t and g[t][i]:  # 只处理出现过、且这条边真实存在的后继
                    indegree[i] -= 1  # 后继入度减一
                    if indegree[i] == 0:  # 减到 0 说明前驱都排完了，可以入队
                        q.append(i)  # 入队
        return '' if len(ans) < cnt else ''.join(ans)  # 排出的字母数少于出现过的字母数说明成环，返回空串
