# 题目：1218. 最长定差子序列（Longest Arithmetic Subsequence of Given Difference）
# 思路：以序列末项的值作为状态，f[x] = f[x-difference] + 1；一次遍历按原数组顺序递推即可。
# 时间复杂度：O(n)，每项只做一次哈希查找与写入；空间复杂度：O(n)，哈希表最多保存 n 个不同的值。
class Solution:  # LeetCode 约定的题解类
    def longestSubsequence(self, arr: List[int], difference: int) -> int:  # arr：原数组；difference：要求的公差（可正可负）
        f = defaultdict(int)  # 缺省值为 0 的字典：f[x] 表示以值 x 结尾的最长定差子序列长度，省去判空
        for x in arr:  # 按原数组顺序遍历，天然保证了子序列的下标递增
            f[x] = f[x - difference] + 1  # 接在值 x-difference 结尾的序列后面；键不存在时 defaultdict 返回 0，正好得到长度 1
        return max(f.values())  # arr 非空，最长子序列一定以某个 x 结尾，取所有状态的最大值即可
