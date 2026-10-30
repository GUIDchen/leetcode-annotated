# 题目：763. 划分字母区间（Partition Labels）
# 思路：先记录每个字母最后出现的位置，再贪心扫描：不断扩展当前片段的右端点，走到右端点处即切分。
# 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，哈希表最多保存 26 个字母的位置。
class Solution:  # LeetCode 约定的题解类
    def partitionLabels(self, s: str) -> List[int]:  # s：待划分的小写字母字符串
        last = {c: i for i, c in enumerate(s)}  # 记录每个字母最后一次出现的下标
        mx = j = 0  # mx 是当前片段能延伸到的最远下标，j 是片段起点
        ans = []  # 保存每个片段的长度
        for i, c in enumerate(s):  # 从左到右贪心地扩展片段右端点
            mx = max(mx, last[c])  # 用当前字符的最后出现位置刷新右端点
            if mx == i:  # 右端点与当前下标重合，说明片段内字母不会再出现在后面
                ans.append(i - j + 1)  # 记录该片段长度
                j = i + 1  # 下一个片段的起点
        return ans  # 返回各片段长度
