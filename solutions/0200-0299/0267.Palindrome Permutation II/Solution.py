# 题目：267. 回文排列 II（Palindrome Permutation II）
# 思路：先找出唯一的中间字符，再用回溯从中间向两侧成对地添加字符，收集所有回文排列。
# 时间复杂度：O(n!)，最坏枚举全部排列；空间复杂度：O(n)，递归深度与当前回文长度同阶。
class Solution:  # LeetCode 约定的题解类
    def generatePalindromes(self, s: str) -> List[str]:  # s 为输入字符串，返回全部不同的回文排列
        def dfs(t):  # 回溯函数：t 是当前已拼好的回文中段
            if len(t) == len(s):  # 长度达到原串长度，说明一个回文拼完了
                ans.append(t)  # 收进结果列表
                return  # 结束本分支
            for c, v in cnt.items():  # 遍历频次表，尝试给两侧各放一个字符
                if v > 1:  # 次数大于 1 才有资格成对放置
                    cnt[c] -= 2  # 用掉两个该字符（cnt 是外层变量，可直接修改）
                    dfs(c + t + c)  # 把字符包在 t 两侧继续递归
                    cnt[c] += 2  # 回溯：恢复次数，供其它分支使用

        cnt = Counter(s)  # 统计每个字符的出现次数
        mid = ''  # 中间字符，偶数长度时为空串
        for c, v in cnt.items():  # 找出出现奇数次的字符
            if v & 1:  # v & 1 为真说明出现奇数次
                if mid:  # 已经存在中间字符，说明无解
                    return []  # 返回空列表
                mid = c  # 记下中间字符
                cnt[c] -= 1  # 从频次里扣掉中间这个字符
        ans = []  # 结果列表
        dfs(mid)  # 从中间字符开始回溯
        return ans  # 返回全部回文排列
