# 题目：1520. 最多的不重叠子字符串（Maximum Number of Non-Overlapping Substrings）
# 核心思路：记录每个字符的首末位置，把每个字符的区间向右「闭包扩张」成合法区间；再按右端点排序，贪心选取互不重叠的区间。
# 时间复杂度：O(n log n)，扩张扫描 O(n) + 排序；空间复杂度：O(n)，候选区间与答案。
class Solution:  # LeetCode 约定的题解类
    def maxNumOfSubstrings(self, s: str) -> List[str]:  # s：只含小写字母的字符串
        first, last = {}, {}  # first/last：每个字符首次、最后一次出现的下标
        for i, c in enumerate(s):  # 从左到右扫描字符串
            if c not in first:  # 第一次遇到该字符
                first[c] = i  # 记录首次出现位置
            last[c] = i  # 持续更新最后出现位置（不在 if 里，每次都要更新）
        segs = []  # 候选区间列表
        for l in first.values():  # 以每个字符的首次出现位置作为区间左端点
            r, i = last[s[l]], l  # r 从该字符最后位置起步，i 从 l 开始扫描
            while i <= r:  # 扫描当前区间，区间可能随时向右扩张
                if first[s[i]] < l:  # 区间内字符在 l 左边还有出现
                    break  # 说明左端点必须更靠左，该字符无法单独成段，直接放弃这个候选
                r = max(r, last[s[i]])  # 否则把右端点扩张到该字符的最后一次出现
                i += 1  # 继续检查下一个字符
            if i > r:  # i > r 表示区间完整闭合
                segs.append((l, r))  # 收集这个合法区间
        segs.sort(key=lambda x: x[1])  # 按右端点排序，便于后面的贪心
        ans, end = [], -1  # ans 存答案，end 记录已选区间的最右端
        for l, r in segs:  # 按右端点从小到大遍历候选区间
            if l > end:  # 与上一个被选区间不重叠
                ans.append(s[l : r + 1])  # 截取 s[l..r] 加入答案
                end = r  # 更新最右端
        return ans  # 返回这些子串组成的答案列表
