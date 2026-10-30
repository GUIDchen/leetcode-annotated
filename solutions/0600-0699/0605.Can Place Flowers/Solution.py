# 题目：605. 种花问题（Can Place Flowers）
# 思路：在花坛两端各补一个 0 当作虚拟空地，然后从第二个位置扫到倒数第二个，只要相邻三个位置之和为 0 就种花。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，两端补 0 生成了新列表。
class Solution:  # LeetCode 约定的题解类
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:  # flowerbed 是 0/1 花坛，n 是要种下的花朵数量
        flowerbed = [0] + flowerbed + [0]  # 两端各补一个虚拟空地，省去对首尾越界的特判
        for i in range(1, len(flowerbed) - 1):  # 只遍历原来的真实位置，跳过两个虚拟边界
            if sum(flowerbed[i - 1 : i + 2]) == 0:  # 左、中、右三个位置之和为 0，说明可以种花
                flowerbed[i] = 1  # 就地种花，供后续位置判断是否相邻
                n -= 1  # 待种数量减一
        return n <= 0  # 待种数量减到 0 或以下，说明能全部种完
