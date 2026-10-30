# 题目：755. 倒水（Pour Water）——中等（付费题）
# 思路：一滴一滴模拟。每滴水先尽量向左流、再尽量向右流，落到路径上最低且最靠边的格子；两边都流不动就落在 k 处。
# 时间复杂度：O(volume * n)，每滴水最多把整个数组扫描一遍；空间复杂度：O(1)，直接在原数组上累加高度。
class Solution:  # LeetCode 约定的题解类
    def pourWater(self, heights: List[int], volume: int, k: int) -> List[int]:  # heights 是地形高度，volume 是水量，k 是倒水位置
        for _ in range(volume):  # 逐滴处理：每轮倒一滴水
            for d in (-1, 1):  # 先向左（d=-1）找，再向右（d=1）找
                i = j = k  # i 是扫描位置，j 记录路径上最低的位置（初始认为原地最低）
                while 0 <= i + d < len(heights) and heights[i + d] <= heights[i]:  # 下一格在界内且不比当前格高，水就能继续流
                    if heights[i + d] < heights[i]:  # 遇到严格更低的格子
                        j = i + d  # 更新最低落点（取最靠外的那个更低位置）
                    i += d  # 朝该方向前进一格
                if j != k:  # 找到了比 k 处更低的落点
                    heights[j] += 1  # 在最低处把高度加一，等价于落下一滴水
                    break  # 这一滴已安排好，不必再尝试另一侧
            else:  # for-else：左右都流不动才会执行到这里
                heights[k] += 1  # 只能堆在倒水位置 k 上
        return heights  # 返回最终地形
