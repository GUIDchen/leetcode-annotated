# 题目：68. 文本左右对齐（Text Justification）
# 思路：贪心取出当前行能容纳的单词，最后一行或单单词行左对齐，其余行把空格总数均分给各间隙、余数优先补给靠左的间隙。
# 时间复杂度：O(N·L)，N 为单词数、L 为 maxWidth，结果中每个字符都要被写入；空间复杂度：O(N·L)，保存返回的所有行。
class Solution:  # LeetCode 约定的题解类
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:  # words：单词表；maxWidth：每行宽度
        ans = []  # 保存已排版好的每一行
        i, n = 0, len(words)  # i 为当前行起点的单词下标，n 为单词总数
        while i < n:  # 逐个处理每一行
            t = []  # t：本行选中的单词
            cnt = len(words[i])  # cnt：本行已占长度（单词长度之和 + 单词间至少一个空格）
            t.append(words[i])  # 先把当前单词放进本行
            i += 1  # 指针后移，准备尝试下一个单词
            while i < n and cnt + 1 + len(words[i]) <= maxWidth:  # 再加一个单词（含一个空格）仍不超宽就继续装
                cnt += 1 + len(words[i])  # 累加该单词长度与它前面的空格
                t.append(words[i])  # 该单词也归入本行
                i += 1  # 指针继续后移
            if i == n or len(t) == 1:  # 最后一行，或本行只有一个单词：必须左对齐
                left = ' '.join(t)  # 单词之间只用一个空格连接
                right = ' ' * (maxWidth - len(left))  # 右侧补空格凑满行宽
                ans.append(left + right)  # 左对齐行加入答案
                continue  # 本行结束，处理下一行
            space_width = maxWidth - (cnt - len(t) + 1)  # 可分配空格总数：行宽减去纯字母总长（cnt 多算了 len(t)-1 个空格，需扣回）
            w, m = divmod(space_width, len(t) - 1)  # w 是每个间隙均分的空格数，m 是余数（分给最左边的 m 个间隙）
            row = []  # 用列表收集本行的各个片段
            for j, s in enumerate(t[:-1]):  # 遍历除最后一个单词外的每个单词
                row.append(s)  # 接上单词本身
                row.append(' ' * (w + (1 if j < m else 0)))  # 接上空格：均分 w 个，前 m 个间隙再多 1 个
            row.append(t[-1])  # 最后一个单词后面不补空格
            ans.append(''.join(row))  # 两端对齐行拼接后加入答案
        return ans  # 返回全部排版结果
