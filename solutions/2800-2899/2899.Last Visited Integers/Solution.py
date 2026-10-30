# 题目：2899. 上一个遍历的整数（Last Visited Integers）
# 思路：按出现顺序记录遇到的正整数；每遇到一个 -1 就把连续计数 k 加一，再取倒数第 k 个记录，不足则记 -1；遇到正整数时把 k 清零。
# 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，seen 最多存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def lastVisitedIntegers(self, nums: List[int]) -> List[int]:  # nums：由正整数与 -1 组成的数组
        seen = []  # seen：按出现顺序保存遇到的正整数
        ans = []  # ans：保存每个 -1 对应的答案
        k = 0  # k：当前连续出现的 -1 的个数
        for x in nums:  # 从左到右扫描数组
            if x == -1:  # 遇到 -1，表示要回溯访问
                k += 1  # 连续计数加一
                ans.append(-1 if k > len(seen) else seen[-k])  # 记录不够则记 -1，否则取倒数第 k 个正整数
            else:  # 遇到正整数
                k = 0  # 连续 -1 的计数清零
                seen.append(x)  # 把这个数追加到历史记录
        return ans  # 返回所有 -1 的答案
