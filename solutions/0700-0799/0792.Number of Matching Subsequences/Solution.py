# 题目：792. 匹配子序列的单词数（Number of Matching Subsequences）
# 思路：按「下一个待匹配字符」把候选串分到 defaultdict(deque) 的 26 个桶；扫母串时遇到 c 就推进 c 桶，匹配完的计数。
# 时间复杂度：O(|s| + 所有候选串总长)，每个字符只被推进一次；空间复杂度：O(所有候选串总长)，桶里存剩余后缀。
class Solution:  # LeetCode 约定的题解类
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:  # s 是母串，words 是候选串列表，返回其中是 s 子序列的个数
        d = defaultdict(deque)  # 键为字符、值为双端队列的默认字典；访问缺失的键会自动创建空队列
        for w in words:  # 按首字符给所有候选串分桶
            d[w[0]].append(w)  # 把候选串放进它首字符对应的桶
        ans = 0  # 匹配成功的计数
        for c in s:  # 顺序扫描母串，保证子序列保持原有顺序
            for _ in range(len(d[c])):  # 只处理进入本轮前就在桶里的串：先固定次数，新入桶的留到后续字符处理
                t = d[c].popleft()  # 从桶头取出候选串（popleft 是 O(1)）
                if len(t) == 1:  # 已匹配到最后一个字符
                    ans += 1  # 该串是 s 的子序列，计数加一
                else:  # 否则还有剩余字符需要继续匹配
                    d[t[1]].append(t[1:])  # 去掉首字符后按新首字符重新入桶
        return ans  # 返回匹配成功的总数
