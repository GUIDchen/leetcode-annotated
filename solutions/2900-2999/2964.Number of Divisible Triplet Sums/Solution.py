# 题目：2964. 可被整除的三元组数量（Number of Divisible Triplet Sums）
# 思路：枚举中间下标 j，用 defaultdict 记录 j 左侧所有数字 mod d 的余数个数，对每个 k 直接查补余数累加答案。
# 时间复杂度：O(n^2)，枚举 j 与 k 两层循环；空间复杂度：O(min(n, d))，字典最多保存 d 种不同的余数。
class Solution:  # LeetCode 约定的题解类
    def divisibleTripletCount(self, nums: List[int], d: int) -> int:  # nums 是输入数组，d 是除数，返回下标 i<j<k 且三数之和能被 d 整除的三元组个数
        cnt = defaultdict(int)  # 默认字典：余数 -> 下标小于当前 j 的这类数字的个数（缺省为 0）
        ans, n = 0, len(nums)  # ans 统计答案；n 是数组长度，一行同时赋值
        for j in range(n):  # 枚举三元组的中间下标 j
            for k in range(j + 1, n):  # 枚举右侧下标 k，保证 i<j<k
                x = (d - (nums[j] + nums[k]) % d) % d  # nums[i] % d 需要等于这个补余数，三数之和才能被 d 整除
                ans += cnt[x]  # 把左侧满足该余数条件的数字个数累加进答案
            cnt[nums[j] % d] += 1  # j 处理完后再入表，供后面更大的 j 当作左侧下标 i 使用
        return ans  # 返回三元组总数
