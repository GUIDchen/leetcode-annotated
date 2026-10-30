# 题目：3134. 找出唯一性数组的中位数（Find the Median of the Uniqueness Array）
# 思路：二分答案 mx，用滑动窗口统计「不同元素个数不超过 mx」的子数组个数，与中位数位置比较后收缩区间。
# 时间复杂度：O(n log n)，二分 O(log n) 次、每次滑窗 O(n)；空间复杂度：O(n)，哈希表最多保存 n 个不同的值。
class Solution:  # LeetCode 约定的题解类
    def medianOfUniquenessArray(self, nums: List[int]) -> int:  # nums 是原数组；List 由判题环境提供，注解不补 import
        def check(mx: int) -> bool:  # 内部函数：判断值不超过 mx 的子数组是否已达到中位数位置
            cnt = defaultdict(int)  # defaultdict 统计窗口内各元素出现次数（由判题环境提供）
            k = l = 0  # k 累计合法子数组个数，l 是窗口左边界
            for r, x in enumerate(nums):  # 右端点 r 逐步右移，同时取出元素 x
                cnt[x] += 1  # 新元素计入窗口
                while len(cnt) > mx:  # 不同元素个数超过上限，需要收缩左边界
                    y = nums[l]  # 左边界元素
                    cnt[y] -= 1  # 它的计数减一
                    if cnt[y] == 0:  # 该元素计数减到 0
                        cnt.pop(y)  # 从字典删除，让 len(cnt) 恰好等于不同元素个数
                    l += 1  # 左边界右移
                k += r - l + 1  # 以 r 结尾的合法子数组共有 r-l+1 个
                if k >= (m + 1) // 2:  # 已达到中位数位置（闭包引用外层的 m）
                    return True  # 可以提前判定 mx 可行
            return False  # 全部扫完仍不够，说明中位数大于 mx

        n = len(nums)  # 数组长度
        m = (1 + n) * n // 2  # 唯一性数组的长度等于子数组总数 n*(n+1)/2
        return bisect_left(range(n), True, key=check)  # 在 range(n) 上二分第一个使 check 为真的值（bisect_left 的 key 用法，bisect 由判题环境提供）
