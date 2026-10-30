# 题目：722. 删除注释（Remove Comments）
# 思路：按行内字符逐位扫描，维护「是否处于块注释」状态；块注释可跨行，用缓冲 t 把被切开的多行拼回一行。
# 时间复杂度：O(N)，N 为源码总字符数；空间复杂度：O(N)，输出占用的空间。
class Solution:  # LeetCode 约定的题解类
    def removeComments(self, source: List[str]) -> List[str]:  # source：按行给出的源码
        ans = []  # 保存删除注释后的各行
        t = []  # 当前行缓冲（用字符列表拼接更高效）
        block_comment = False  # 是否处于块注释中
        for s in source:  # 逐行扫描源码
            i, m = 0, len(s)  # 行内下标 i 与行长 m
            while i < m:  # 逐字符扫描当前行
                if block_comment:  # 处于块注释中，只寻找结束标记
                    if i + 1 < m and s[i : i + 2] == "*/":  # 找到块注释结束标记
                        block_comment = False  # 退出块注释
                        i += 1  # 额外跳过 '/'
                else:  # 不在块注释中
                    if i + 1 < m and s[i : i + 2] == "/*":  # 块注释开始
                        block_comment = True  # 进入块注释状态
                        i += 1  # 跳过 '*'
                    elif i + 1 < m and s[i : i + 2] == "//":  # 遇到行注释
                        break  # 丢弃本行剩余内容
                    else:  # 普通字符
                        t.append(s[i])  # 追加到当前行缓冲
                i += 1  # 处理下一个字符
            if not block_comment and t:  # 本行结束且不在块注释内，缓冲非空则可输出一行
                ans.append("".join(t))  # 把缓冲拼接成一行并收集
                t.clear()  # 清空缓冲，准备下一行
        return ans  # 返回删除注释后的结果
