# 题目：493. 翻转对（Reverse Pairs）
# 思路：归并排序统计；每次合并前用双指针数出「左半段元素 > 右半段元素 × 2」的对数（左右两段各自有序，指针可单调前移），再正常合并两段。
# 时间复杂度：O(n log n)，归并 O(log n) 层、每层线性统计与合并；空间复杂度：O(n)，辅助列表 t 与递归栈。
class Solution:  # LeetCode 约定的题解类
    def reversePairs(self, nums: List[int]) -> int:  # nums：输入数组；返回满足 i < j 且 nums[i] > 2 * nums[j] 的数对个数
        def merge_sort(l, r):  # 内部归并排序：处理区间 [l, r]，返回该区间内的翻转对数量
            if l >= r:  # 区间长度 ≤ 1，没有数对
                return 0  # 递归出口返回 0
            mid = (l + r) >> 1  # 取中点，(l + r) >> 1 等价于向下取整的 (l + r) / 2
            ans = merge_sort(l, mid) + merge_sort(mid + 1, r)  # 先分别排好左右两段，并累加两段内部的翻转对
            t = []  # 归并用的临时列表（每层新建，用于局部合并）
            i, j = l, mid + 1  # i 指向左段、j 指向右段
            while i <= mid and j <= r:  # 双指针统计跨段翻转对：两段都有序，所以 j 单调右移
                if nums[i] <= 2 * nums[j]:  # 左段元素还不够大（不大于右段元素的 2 倍）
                    i += 1  # 左指针右移，继续找更大的左段元素
                else:  # 否则 nums[i] > 2 * nums[j]，右段这个元素对左段 i..mid 全部成立
                    ans += mid - i + 1  # 左段从 i 到 mid 共 mid - i + 1 个元素都能与 nums[j] 配对
                    j += 1  # 右指针右移，处理下一个候选
            i, j = l, mid + 1  # 重置双指针，开始真正的归并
            while i <= mid and j <= r:  # 标准归并：两段都还有元素时取较小的追加到 t
                if nums[i] <= nums[j]:  # 左段当前元素较小
                    t.append(nums[i])  # 把左段元素追加到临时列表
                    i += 1  # 左指针后移
                else:  # 否则取右段元素
                    t.append(nums[j])  # 把右段元素追加到临时列表
                    j += 1  # 右指针后移
            t.extend(nums[i : mid + 1])  # 左段剩余部分整体接到末尾
            t.extend(nums[j : r + 1])  # 右段剩余部分整体接到末尾
            nums[l : r + 1] = t  # 把合并好的有序区间整体写回原数组
            return ans  # 返回本段的翻转对总数

        return merge_sort(0, len(nums) - 1)  # 对整个数组做归并排序并返回答案
