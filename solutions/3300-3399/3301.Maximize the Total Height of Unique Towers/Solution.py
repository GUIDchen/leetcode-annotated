# 题目：3301. 高度互不相同的最大塔高和（Maximize the Total Height of Unique Towers）
# 思路：升序排序后倒序遍历，每座塔取 min(自身上限, 上一座高度 - 1)，为后面的塔留出递减空间。
# 时间复杂度：O(n log n)，排序为主；空间复杂度：O(n)，倒序切片复制了一份数组。
class Solution:  # LeetCode 约定的题解类
    def maximumTotalSum(self, maximumHeight: List[int]) -> int:  # maximumHeight：每座塔允许的最大高度；返回高度互不相同的最大总和，做不到返回 -1
        maximumHeight.sort()  # 升序排序，配合下面的倒序切片实现从大到小遍历
        ans, mx = 0, inf  # ans 累加塔高总和；mx 记录上一座塔高，inf 表示第一座塔不受限制
        for x in maximumHeight[::-1]:  # 倒序遍历，相当于按高度上限从大到小处理
            x = min(x, mx - 1)  # 当前塔最高只能取 mx-1，保证与上一座塔高度不同
            if x <= 0:  # 高度被压到 0 或负数，说明已无法再分配合法高度
                return -1  # 按题意返回 -1
            ans += x  # 累加当前塔高
            mx = x  # 更新上界，供下一座塔使用
        return ans  # 返回最大总高度
