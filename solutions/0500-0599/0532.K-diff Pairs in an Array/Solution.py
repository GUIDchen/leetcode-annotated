# 题目：532. 数组中的 k-diff 数对（K-diff Pairs in an Array）
# 思路：边遍历边用集合 vis 记录见过的值，用集合 ans 去重；每个数只找「更小的伙伴」，天然不会重复计数。
# 时间复杂度：O(n)，每个元素只做常数次哈希操作；空间复杂度：O(n)，两个集合最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def findPairs(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是要求的绝对差
        ans = set()  # 存放数对中较小的那个值，靠集合自动去重
        vis = set()  # 存放已经遍历过的值，用来 O(1) 判断伙伴是否存在
        for x in nums:  # 按顺序遍历每个元素
            if x - k in vis:  # 比 x 小 k 的伙伴之前出现过，(x-k, x) 是合法数对
                ans.add(x - k)  # 用较小的值 x-k 代表这个数对，重复也只算一次
            if x + k in vis:  # 比 x 大 k 的伙伴之前出现过，(x, x+k) 是合法数对
                ans.add(x)  # 同样用较小的值 x 代表这个数对
            vis.add(x)  # 当前值加入已见集合；放在最后，k=0 时就不会拿自己和自己配对
        return len(ans)  # 集合大小就是不同数对的个数
