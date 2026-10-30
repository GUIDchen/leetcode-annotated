# 题目：821. 字符的最短距离（Shortest Distance to a Character）
# 思路：两次扫描。左扫记录最近一次出现 c 的位置，得到向左的最短距离；右扫同理得到向右的距离，两轮取较小值即为答案。
# 时间复杂度：O(n)，只扫描两遍；空间复杂度：O(n)，返回所用列表。
class Solution:  # LeetCode 约定的题解类
    def shortestToChar(self, s: str, c: str) -> List[int]:  # s：给定字符串；c：目标字符
        n = len(s)  # 字符串长度
        ans = [n] * n  # ans[i] 表示位置 i 到最近 c 的距离，先用上界 n 填满
        pre = -inf  # 左侧最近一次出现 c 的下标，初始为负无穷
        for i, ch in enumerate(s):  # 从左往右扫描
            if ch == c:  # 当前位置就是目标字符
                pre = i  # 更新最近出现的位置
            ans[i] = min(ans[i], i - pre)  # 与左侧最近的 c 的距离
        suf = inf  # 右侧最近一次出现 c 的下标，初始为无穷大
        for i in range(n - 1, -1, -1):  # 从右往左扫描
            if s[i] == c:  # 当前位置就是目标字符
                suf = i  # 更新最近出现的位置
            ans[i] = min(ans[i], suf - i)  # 与右侧最近的 c 的距离，取左右两侧的较小值
        return ans  # 返回每个位置的最短距离
