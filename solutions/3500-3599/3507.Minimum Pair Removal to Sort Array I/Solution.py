# 题目：3507. 移除最小数对使数组有序 I（Minimum Pair Removal to Sort Array I）
# 思路：按题意直接模拟。每轮先判断数组是否已非递减，否则在全部相邻对中找和最小（和相同时取最靠左）的一对，用它的和替换左端元素并删掉右端元素，直到数组非递减为止。
# 时间复杂度：O(n²)，每轮扫描相邻对与删除元素都是 O(n)，最多合并 n-1 轮；空间复杂度：O(n)，额外拷贝了一份数组。
class Solution:  # LeetCode 约定的题解类
    def minimumPairRemoval(self, nums: List[int]) -> int:  # nums：待处理数组；返回使数组非递减所需的最少合并次数
        arr = nums[:]  # 浅拷贝数组，避免修改输入
        ans = 0  # 记录已执行的合并次数

        def is_non_decreasing(a: List[int]) -> bool:  # 内部函数：判断数组是否已非递减
            for i in range(1, len(a)):  # 从第二个元素开始与前一元素比较
                if a[i] < a[i - 1]:  # 出现下降
                    return False  # 立即判定不满足
            return True  # 全程无下降，数组已非递减

        while not is_non_decreasing(arr):  # 还不是非递减就继续合并
            k = 0  # k 记录最小相邻对的左端下标
            s = arr[0] + arr[1]  # 以最左边一对之和作为初始最小值
            for i in range(1, len(arr) - 1):  # 枚举其余的相邻对
                t = arr[i] + arr[i + 1]  # 当前相邻对之和
                if s > t:  # 出现更小的和
                    s = t  # 更新最小和
                    k = i  # 记录它的左端下标
            arr[k] = s  # 用数对之和替换左端元素
            arr.pop(k + 1)  # 删除被合并掉的右端元素
            ans += 1  # 合并次数加一
        return ans  # 返回最少合并次数
