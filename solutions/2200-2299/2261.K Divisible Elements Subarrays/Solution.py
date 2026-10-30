# 题目：2261. 含最多 K 个可整除元素的子数组（K Divisible Elements Subarrays）
# 思路：枚举左端点并向右扩展右端点，计数器保证可被 p 整除的元素不超过 k 个，同时滚动计算双哈希，用集合对子数组签名去重。
# 时间复杂度：O(n^2)，每个左端点最多向右扩展 n 步；空间复杂度：O(n^2)，集合最多存 O(n^2) 个签名。
class Solution:  # LeetCode 约定的题解类
    def countDistinct(self, nums: List[int], k: int, p: int) -> int:  # nums 是原数组，k 是可被 p 整除元素的上限，返回本质不同且合法的子数组个数
        s = set()  # 集合存放子数组的双哈希签名，利用集合自动去重
        n = len(nums)  # 数组长度，作为两层循环的上界
        base1, base2 = 131, 13331  # 两组不同的哈希基数，降低两个哈希同时碰撞的概率
        mod1, mod2 = 10**9 + 7, 10**9 + 9  # 两个大质数模数，把哈希值控制在 32 位以内
        for i in range(n):  # 枚举子数组的左端点 i
            h1 = h2 = cnt = 0  # 两个哈希都从空子数组的 0 开始；cnt 记录可被 p 整除的元素个数
            for j in range(i, n):  # 枚举右端点 j，逐个把 nums[j] 接进当前子数组
                cnt += nums[j] % p == 0  # 布尔值可以当 0/1 累加，统计可整除元素
                if cnt > k:  # 可整除元素已超过上限，再延长只会更多
                    break  # 提前结束本轮扩张
                h1 = (h1 * base1 + nums[j]) % mod1  # 滚动哈希：在已有哈希末尾追加新元素
                h2 = (h2 * base2 + nums[j]) % mod2  # 第二组哈希换一个基数同步滚动
                s.add(h1 << 32 | h2)  # 两个哈希拼成一个 64 位整数加入集合，实现按内容去重
        return len(s)  # 集合大小就是答案
