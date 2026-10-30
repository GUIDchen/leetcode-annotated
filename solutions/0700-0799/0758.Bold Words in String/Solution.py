# 题目：758. 字符串中的加粗单词（Bold Words in String）——中等（付费题）
# 思路：把所有关键词建成 Trie，枚举 s 的每个起点在 Trie 上匹配得到覆盖区间，合并区间后再统一在原文上插入 <b>…</b>。
# 时间复杂度：O(n^2 + L)，n 为 s 长度、L 为所有关键词总长；空间复杂度：O(L * 128)，Trie 结点数，另加 O(n) 的区间列表。
class Trie:  # 字典树，用于快速判断某个前缀是否是关键词
    def __init__(self):  # 构造函数：初始化一个空结点
        self.children = [None] * 128  # 128 个孩子指针，直接用字符的 ASCII 码当下标
        self.is_end = False  # 标记这里是否是某个关键词的结尾

    def insert(self, word):  # 把关键词 word 插入字典树
        node = self  # 从根结点开始
        for c in word:  # 逐字符沿树下行
            idx = ord(c)  # 字符的 ASCII 码，用来取孩子下标
            if node.children[idx] is None:  # 该字符的子结点还不存在
                node.children[idx] = Trie()  # 新建一个结点挂上去
            node = node.children[idx]  # 走到子结点
        node.is_end = True  # 最后一个字符所在结点标记为关键词结尾


class Solution:  # LeetCode 约定的题解类
    def boldWords(self, words: List[str], s: str) -> str:  # words 是关键词表，s 是待加粗的原串
        trie = Trie()  # 建一棵空字典树
        for w in words:  # 遍历所有关键词
            trie.insert(w)  # 逐个插入 Trie
        n = len(s)  # 原串长度
        pairs = []  # 收集所有被关键词覆盖的区间 [起点, 终点]
        for i in range(n):  # 枚举每个匹配起点
            node = trie  # 每个起点都从根重新开始匹配
            for j in range(i, n):  # 从 i 开始向右延伸
                idx = ord(s[j])  # 当前字符的 ASCII 码，正好作为孩子下标
                if node.children[idx] is None:  # Trie 上走不下去，再长也不可能是关键词
                    break
                node = node.children[idx]  # 沿着 Trie 向下走
                if node.is_end:  # 走到关键词结尾
                    pairs.append([i, j])  # 记录这一段的覆盖区间
        if not pairs:  # 一个关键词都没匹配到
            return s  # 原样返回
        st, ed = pairs[0]  # 用第一个区间初始化当前合并段
        t = []  # 合并后互不重叠的区间
        for a, b in pairs[1:]:  # 顺序扫描其余区间（pairs 天然按起点递增）
            if ed + 1 < a:  # 与当前合并段既不相邻也不重叠
                t.append([st, ed])  # 收束当前合并段
                st, ed = a, b  # 从当前区间重新开始合并
            else:  # 重叠或首尾相邻
                ed = max(ed, b)  # 把右端点扩展到更远的一侧
        t.append([st, ed])  # 别忘了把最后一段合并结果收进去

        ans = []  # 用列表收集片段，最后统一 join，避免字符串反复拼接
        i = j = 0  # i 是原串上的游标，j 是当前待处理的合并区间下标
        while i < n:  # 扫描完整个原串为止
            if j == len(t):  # 所有区间都处理完，剩下的都是普通文本
                ans.append(s[i:])  # 一次性拼接剩余部分
                break  # 结束循环
            st, ed = t[j]  # 取出当前合并区间
            if i < st:  # 区间之前还有普通文本
                ans.append(s[i:st])  # 原样拷贝这段普通文本
            ans.append('<b>')  # 加粗开始标签
            ans.append(s[st : ed + 1])  # 加粗区间内的子串
            ans.append('</b>')  # 加粗结束标签
            j += 1  # 处理下一个合并区间
            i = ed + 1  # 游标跳过整个已加粗区间

        return ''.join(ans)  # 把片段拼成最终字符串返回
