# 题目：616. 给字符串添加加粗标签（Add Bold Tag in String）🔒
# 思路：字典树存下所有目标单词，枚举每个起点匹配出全部可加粗区间，合并相交/相邻区间后再拼上 <b> 标签。
# 时间复杂度：O(n^2 + 所有单词总长)，每个起点最多向右匹配 n 个字符；空间复杂度：O(所有单词总长)，即字典树节点数。
class Trie:  # 字典树节点：把 words 挂到树上，便于从任意位置向后匹配
    def __init__(self):  # 构造函数：初始化孩子数组与结尾标记
        self.children = [None] * 128  # 128 个槽位，下标直接就是字符的 ASCII 码
        self.is_end = False  # 新节点默认不是任何单词的结尾

    def insert(self, word):  # 把一个单词插入字典树
        node = self  # 从根节点出发向下走
        for c in word:  # 逐字符沿树下移
            idx = ord(c)  # 用字符的 ASCII 码当下标
            if node.children[idx] is None:  # 该前缀路径还不存在
                node.children[idx] = Trie()  # 补建一个孩子节点
            node = node.children[idx]  # 移动到刚走过的孩子节点
        node.is_end = True  # 最后一个字符所在节点标记为单词结尾


class Solution:  # LeetCode 约定的题解类
    def addBoldTag(self, s: str, words: List[str]) -> str:  # s 是原字符串，words 是需要加粗的单词列表
        trie = Trie()  # 建树，所有单词一次性插好，供后面每个起点复用
        for w in words:  # 逐个单词插入
            trie.insert(w)  # 调用字典树插入
        n = len(s)  # 记录原串长度，后面多处要用
        pairs = []  # 收集所有需要加粗的闭区间 [i, j]
        for i in range(n):  # 枚举每个可能的匹配起点 i
            node = trie  # 每个起点都从字典树根重新出发
            for j in range(i, n):  # 从 i 开始向右逐字符扩展
                idx = ord(s[j])  # 用字符的 ASCII 码作为孩子下标
                if node.children[idx] is None:  # 没有这条分支，再往右不可能匹配
                    break  # 跳出内层循环，换下一个起点
                node = node.children[idx]  # 沿树下行到下一个字符
                if node.is_end:  # 走到了某个单词的结尾
                    pairs.append([i, j])  # 说明区间 [i, j] 需要加粗，先记录下来待合并
        if not pairs:  # 一个可加粗区间都没有
            return s  # 原串原样返回
        st, ed = pairs[0]  # 用第一个区间初始化当前合并区间 [st, ed]
        t = []  # 存放合并后的区间，起点保持递增
        for a, b in pairs[1:]:  # 顺序合并其余区间（pairs 按起点递增产生）
            if ed + 1 < a:  # 中间有间隔，说明两段既不相交也不相邻
                t.append([st, ed])  # 当前合并区间封口
                st, ed = a, b  # 换用新区间继续合并
            else:  # 否则说明两段相交或相邻
                ed = max(ed, b)  # 合并成一个更长区间，终点取较大者
        t.append([st, ed])  # 最后一个合并区间入列

        ans = []  # 结果用列表收集片段，最后统一 join，避免字符串反复拼接
        i = j = 0  # i 扫描原串，j 扫描合并后的区间数组
        while i < n:  # 依次把「未覆盖字符」和「加粗片段」拼到结果里
            if j == len(t):  # 区间已经用完
                ans.append(s[i:])  # 剩余部分整段照抄
                break  # 拼完即可结束
            st, ed = t[j]  # 取出当前要处理的合并区间
            if i < st:  # 区间左侧还有不会被加粗的字符
                ans.append(s[i:st])  # 先把这段字符原样追加
            ans.append('<b>')  # 写入加粗开始标签
            ans.append(s[st : ed + 1])  # 区间内的整段字符原样输出
            ans.append('</b>')  # 写入加粗结束标签
            j += 1  # 处理下一个区间
            i = ed + 1  # i 跳过已经加粗的这部分

        return ''.join(ans)  # 拼接所有片段得到答案
