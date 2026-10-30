# 题目：1181. 前后拼接（Before and After Puzzle）
# 思路：先用 split 取出每条短语的首词与尾词；两两配对，若前者尾词等于后者首词且不是同一条，
#       就拼接并去掉重复词，最后 set 去重 + 排序。时间复杂度 O(n^2 * L)，空间 O(n^2)。
class Solution:  # LeetCode 约定的题解类
    def beforeAndAfterPuzzles(self, phrases: List[str]) -> List[str]:  # phrases 为短语列表，返回所有可拼接出的新短语
        ps = []  # ps 保存每条短语的（首词, 尾词）
        for p in phrases:  # 逐条短语预处理
            ws = p.split()  # 按空白切分成单词，首尾即首词与尾词
            ps.append((ws[0], ws[-1]))  # 只需首尾两个词就能判断能否拼接
        n = len(ps)  # 短语条数
        ans = []  # 收集所有拼接结果（之后再去重）
        for i in range(n):  # 枚举作为前缀的短语下标
            for j in range(n):  # 枚举作为后缀的短语下标
                if i != j and ps[i][1] == ps[j][0]:  # 不能自己接自己，且前者尾词要等于后者首词
                    ans.append(phrases[i] + phrases[j][len(ps[j][0]) :])  # 切掉后者首词（长度就是重复词长度），再拼到前者后面
        return sorted(set(ans))  # 去重并排序，set 消除重复项、sorted 满足字典序要求
