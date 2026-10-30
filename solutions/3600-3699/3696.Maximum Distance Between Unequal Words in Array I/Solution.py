# 3696. Maximum Distance Between Unequal Words in Array I（3696. 不同单词间的最大距离 I 🔒）
# 核心思路：对每个位置 i，分别与首元素、末元素比较；只要 words[i] 与 words[0] 不同，答案至少为 i+1；只要与 words[-1] 不同，答案至少为 n-i，两者取最大即可覆盖所有不同单词对。
# 复杂度：时间 O(n)，空间 O(1)（不计输入与字符串比较开销）。
class Solution:  # 定义题解类
    def maxDistance(self, words: List[str]) -> int:  # 主函数：返回两个不同单词之间的最大距离
        n = len(words)  # n 为单词个数
        ans = 0  # ans 记录当前找到的最大距离
        for i in range(n):  # 遍历每个位置
            if words[i] != words[0]:  # 当前单词与首个单词不同
                ans = max(ans, i + 1)  # 那么它与下标 0 组成的距离为 i + 1
            if words[i] != words[-1]:  # 当前单词与最后一个单词不同
                ans = max(ans, n - i)  # 那么它与下标 n-1 组成的距离为 n - i
        return ans  # 返回最大距离
