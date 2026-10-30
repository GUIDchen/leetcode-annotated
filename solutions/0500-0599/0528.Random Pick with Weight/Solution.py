# 题目：528. 按权重随机选择（Random Pick with Weight）
# 思路：构造前缀和数组 s，然后在 [1, s[-1]] 里随机取一个落点，二分出第一个 s[mid] >= 落点的下标。
# 时间复杂度：构造函数 O(n)，pickIndex 每次 O(log n)；空间复杂度：O(n)，存前缀和。
class Solution:  # LeetCode 约定的题解类
    def __init__(self, w: List[int]):  # 构造函数：w 是权重数组
        self.s = [0]  # 前缀和数组的哨兵位 s[0] = 0，让后面的累加写法统一
        for c in w:  # 依次累加每个权重
            self.s.append(self.s[-1] + c)  # 新元素 = 之前所有元素之和 + 当前权重，构成前缀和

    def pickIndex(self) -> int:  # 按权重随机返回一个下标
        x = random.randint(1, self.s[-1])  # 在 [1, 权重总和] 上均匀取整数，权重越大覆盖的区间越长
        left, right = 1, len(self.s) - 1  # 在真实下标区间 [1, len-1] 上二分
        while left < right:  # 左右端点相遇时二分结束
            mid = (left + right) >> 1  # 取中点，>> 1 等价于整除 2
            if self.s[mid] >= x:  # 落点落在 mid 的前缀和以内
                right = mid  # 答案在左半段（含 mid）
            else:  # 落点比 mid 的前缀和还大
                left = mid + 1  # 答案在右半段（不含 mid）
        return left - 1  # 前缀和下标 1 对应原数组下标 0，所以减一


# Your Solution object will be instantiated and called as such:
# obj = Solution(w)
# param_1 = obj.pickIndex()
