# 题目：912. 排序数组（Sort an Array）
# 核心思路：三路快速排序：随机取基准值，把区间就地划分成「小于 / 等于 / 大于」三段，等于基准的元素一次到位，再递归处理两侧。
# 时间复杂度：平均 O(n log n)、最坏 O(n^2)；空间复杂度：O(log n)，为递归栈深度。
class Solution:  # 题解类
    def sortArray(self, nums: List[int]) -> List[int]:  # 返回排序后的 nums
        def quick_sort(l, r):  # 对闭区间 [l, r] 做三路快排（就地修改 nums）
            if l >= r:  # 区间元素不超过 1 个，天然有序
                return  # 递归出口
            x = nums[randint(l, r)]  # 随机取基准值，避免有序或大量重复的数据导致退化
            i, j, k = l - 1, r + 1, l  # i 指向「小于区」末尾，j 指向「大于区」开头，k 是当前考察位置
            while k < j:  # k 追上 j 时，三段划分完成
                if nums[k] < x:  # 当前元素小于基准，应放进小于区
                    nums[i + 1], nums[k] = nums[k], nums[i + 1]  # 把小于区的下一个位置与 k 处元素交换
                    i, k = i + 1, k + 1  # 小于区右扩一格，k 也随之前进
                elif nums[k] > x:  # 当前元素大于基准，应丢到大于区
                    j -= 1  # 大于区左扩一格
                    nums[j], nums[k] = nums[k], nums[j]  # 把 k 处元素换到大于区，右侧换过来的元素还没考察所以 k 不动
                else:  # 当前元素等于基准，留在中间等于区
                    k = k + 1  # 直接跳过，等于区自然变长
            quick_sort(l, i)  # 递归排序小于区 [l, i]
            quick_sort(j, r)  # 递归排序大于区 [j, r]

        quick_sort(0, len(nums) - 1)  # 对整个数组排序
        return nums  # 返回排序结果
