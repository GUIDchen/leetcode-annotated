# 题目：3932. 统计区间内的完全 K 次幂数量（Count K-th Roots in a Range）
# 思路：k = 1 时区间内每个整数都是 1 次幂，直接返回区间长度；否则用 count() 从小到大枚举底数 x，算 y = x^k，一旦 y > r 就停止枚举，落在 [l, r] 内则计数。
# 时间复杂度：O(r^(1/k))，底数只枚举到 r 的 k 次方根附近；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countKthRoots(self, l: int, r: int, k: int) -> int:  # l、r：闭区间端点；k：幂次，返回完全 k 次幂的个数
        if k == 1:  # 一次幂需要特判
            return r - l + 1  # 区间内每个整数都是完全 1 次幂
        ans = 0  # 完全 k 次幂的个数
        for x in count():  # 底数从 0 开始无限枚举，靠 y > r 跳出
            y = x**k  # 计算 x 的 k 次幂
            if y > r:  # 已经超过上界
                break  # 更大的底数只会更超界，枚举结束
            if l <= y <= r:  # y 落在闭区间内
                ans += 1  # 计数加一
        return ans  # 返回个数
