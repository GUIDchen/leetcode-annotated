# 题目：830. 较大分组的位置（Positions of Large Groups）
# 思路：双指针扫描。i 是当前分组起点，j 一直右移找分组末尾，长度 >= 3 就记录 [i, j-1]，再把 i 移到 j 处理下一组。
# 时间复杂度：O(n)，每个字符只被访问一次；空间复杂度：O(1)（不计返回结果占用的空间）。
class Solution:  # LeetCode 约定的题解类
    def largeGroupPositions(self, s: str) -> List[List[int]]:  # s 是只含小写字母的字符串，返回所有长度 >= 3 的分组的起止下标
        i, n = 0, len(s)  # i 是当前分组起点，n 是字符串长度
        ans = []  # 结果列表，元素为 [start, end]
        while i < n:  # 还没扫完就处理一个分组
            j = i  # j 从分组起点出发，用来找分组末尾的下一位
            while j < n and s[j] == s[i]:  # 字符仍然与分组首字符相同就继续右移
                j += 1  # 末尾后移一格
            if j - i >= 3:  # 长度 j-i 达到 3 才是较大分组
                ans.append([i, j - 1])  # 记录起止下标，右端是 j-1（j 已经指向下一组的首字符）
            i = j  # i 跳到下一个分组的起点
        return ans  # 返回所有较大分组的位置
