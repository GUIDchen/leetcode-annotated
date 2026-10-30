# 题目：4032. 至多 K 个不同质因数集合的最长子数组 / Longest Subarray With at Most K Distinct Prime Factors
# 核心思路：先用埃氏筛预处理 1e5 以内每个数的全部不同质因数，再用滑动窗口配哈希表维护窗口内不同质因数的个数
# 复杂度：时间复杂度 O(MX log log MX + n·ω(max))，空间复杂度 O(MX log log MX)
mx = 100001  # 预处理上界，题目保证 nums[i] <= 100000
primes = [[] for _ in range(mx)]  # primes[x] 存放 x 的所有不同质因数
for i in range(2, mx):  # 枚举 2 到 mx-1 的每个数
    if not primes[i]:  # primes[i] 为空说明 i 是质数
        for j in range(i, mx, i):  # 把质数 i 登记到它的所有倍数上（埃氏筛思想）
            primes[j].append(i)  # j 含有质因数 i，记录下来


class Solution:  # 定义 LeetCode 题解类
    def longestSubarray(self, nums: list[int], k: int) -> int:  # 返回至多包含 k 个不同质因数的最长子数组长度
        cnt = defaultdict(int)  # 滑动窗口内每种质因数的出现次数
        ans = l = 0  # ans 记录答案，l 是窗口左端点
        for r, x in enumerate(nums):  # 右端点 r 从左到右扩张窗口
            for y in primes[x]:  # 把新加入元素 x 的质因数全部计入窗口
                cnt[y] += 1  # 质因数 y 的计数加一
            while len(cnt) > k:  # 不同质因数超过 k 个时收缩左端点
                for y in primes[nums[l]]:  # 扣除即将移出窗口的 nums[l] 的质因数
                    cnt[y] -= 1  # 计数减一
                    if cnt[y] == 0:  # 计数归零说明该质因数已离开窗口
                        cnt.pop(y)  # 删除该键，保证 len(cnt) 等于不同质因数个数
                l += 1  # 左端点右移
            ans = max(ans, r - l + 1)  # 用当前合法窗口长度更新答案
        return ans  # 返回最长子数组长度
