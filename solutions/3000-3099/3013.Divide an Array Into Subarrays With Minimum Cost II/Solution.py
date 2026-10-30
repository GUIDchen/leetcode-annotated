# 题目：3013. 将数组分成最小总代价的子数组 II（Divide an Array Into Subarrays With Minimum Cost II）
# 思路：首元素固定计入代价，其余 k-1 个切点只能落在下标 1..dist+1 的滑动窗口内。用两个 SortedList 维护窗口（l 存最小的 k-1 个数、r 存其余候选），窗口右移时左端删一个、右端加一个，再把 l 的大小调回 k-1，s 始终等于首元素加 l 之和。
# 时间复杂度：O(n log n)，每次窗口移动做常数次 SortedList 操作；空间复杂度：O(dist)，两个有序表合计保存窗口内的元素。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, nums: List[int], k: int, dist: int) -> int:  # nums：输入数组；k：要切成的子数组个数；dist：相邻两个切点下标之差的上限
        def l2r():  # 辅助函数：把左侧最大元素挪到右侧，并同步总和
            nonlocal s  # 声明 s 来自外层函数，闭包内要修改它
            x = l.pop()  # pop() 默认弹出 SortedList 的最大元素
            s -= x  # 该元素不再被选中，总和减去它
            r.add(x)  # 放入右侧候选集合

        def r2l():  # 辅助函数：把右侧最小元素补进左侧，并同步总和
            nonlocal s  # 同样需要修改外层的 s
            x = r.pop(0)  # pop(0) 弹出最小的元素
            l.add(x)  # 放入左侧选中集合
            s += x  # 计入总和

        k -= 1  # 子数组个数 k 减 1，变成「除首元素外还需要挑的切点个数」
        s = sum(nums[: dist + 2])  # 先把首元素与整个窗口的元素全部求和，后续再剔除多余的大元素
        l = SortedList(nums[1 : dist + 2])  # 左侧选中集合：窗口 nums[1..dist+1]，SortedList 来自 sortedcontainers 库
        r = SortedList()  # 右侧候选集合：暂未被选中的元素
        while len(l) > k:  # 左侧超过 k 个，说明多选了大元素，逐个挪到右侧
            l2r()  # 每次把当前左侧的最大值挪出去
        ans = s  # 第一个窗口的最小代价作为当前最优解
        for i in range(dist + 2, len(nums)):  # 窗口右端点从 dist+2 开始向右滑动
            x = nums[i - dist - 1]  # 即将滑出窗口左端的元素
            if x in l:  # 用 in 判断它是否在左侧被选中（SortedList 的存在性判断是 O(log n)）
                l.remove(x)  # 在左侧：删除一个该值
                s -= x  # 总和同步减去
            else:  # 不在左侧，就必然在右侧候选里
                r.remove(x)  # 从右侧删除一个该值
            y = nums[i]  # 从窗口右端新进入的元素
            if y < l[-1]:  # 比左侧最大值 l[-1] 还小，说明它应该被选中（数量失衡交给后面的循环修）
                l.add(y)  # 放进左侧选中集合
                s += y  # 计入总和
            else:  # 否则它暂时不值得被选中
                r.add(y)  # 放进右侧候选集合
            while len(l) < k:  # 删掉左端元素后左侧可能不足 k 个，从右侧补最小的进来
                r2l()  # 补齐一个
            while len(l) > k:  # 若新加入元素让左侧超过 k 个，就把最大的挤回右侧
                l2r()  # 挤出最大的一个
            ans = min(ans, s)  # 用当前窗口的最小代价更新全局答案
        return ans  # 返回所有窗口中的最小总代价
