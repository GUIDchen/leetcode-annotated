# 题目：1095. 山脉数组中查找目标值（Find in Mountain Array）
# 思路：先二分出峰值，再用 k = 1 / k = -1 把升序段与降序段统一成升序二分，各查一次。
# 时间复杂度：O(log n)，两次二分；空间复杂度：O(1)，只用常数个变量。
# 下面是被注释掉的 MountainArray 接口说明：判题器会提供该类型，我们只调用 get / length。
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
# class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:


class Solution:  # LeetCode 约定的题解类
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:  # target 是目标值，mountain_arr 是只暴露 get / length 的山脉数组对象
        def search(l: int, r: int, k: int) -> int:  # 内部通用二分函数：k = 1 查升序段，k = -1 查降序段
            while l < r:  # 在当前区间 [l, r] 上二分
                mid = (l + r) >> 1  # 取中点，>> 1 等价于向下取整除以 2
                if k * mountain_arr.get(mid) >= k * target:  # 乘以 k 把降序段翻成升序，>= 表示答案在左半部分
                    r = mid  # 收缩右边界
                else:  # 否则答案在右半部分
                    l = mid + 1  # 排除 mid，收缩左边界
            return -1 if mountain_arr.get(l) != target else l  # 循环结束时 l 是第一个满足条件的位置；等于 target 才返回下标，否则返回 -1

        n = mountain_arr.length()  # 山脉数组长度
        l, r = 0, n - 1  # 二分区间 [l, r] 覆盖整个数组
        while l < r:  # 第一次二分：定位峰值下标
            mid = (l + r) >> 1  # 取中点
            if mountain_arr.get(mid) > mountain_arr.get(mid + 1):  # 右侧开始下降，峰值在 mid 或更左
                r = mid  # 峰值上界收缩到 mid
            else:  # 否则仍在上升，峰值在右侧
                l = mid + 1  # 峰值下界跳到 mid + 1
        ans = search(0, l, 1)  # 先在升序段（含峰值）里找，优先返回更小的下标
        return search(l + 1, n - 1, -1) if ans == -1 else ans  # 升序段没找到再去降序段找；都没有则返回 -1
