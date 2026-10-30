# 题目：2249. 统计圆内格点数目（Count Lattice Points Inside a Circle）
# 思路：所有坐标非负，枚举 [0, maxX] × [0, maxY] 的每个整点，判断是否落在任一圆内（dx²+dy² ≤ r²），命中即计数并跳出，避免重复计数。
# 时间复杂度：O(maxX·maxY·n)，n 为圆的个数；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countLatticePoints(self, circles: List[List[int]]) -> int:  # circles 的每个元素为 [圆心x, 圆心y, 半径r]
        ans = 0  # ans：被至少一个圆覆盖的格点数量
        mx = max(x + r for x, _, r in circles)  # 横坐标上界：所有圆中「圆心x + 半径」的最大值
        my = max(y + r for _, y, r in circles)  # 纵坐标上界：所有圆中「圆心y + 半径」的最大值
        for i in range(mx + 1):  # 遍历 0..mx 的每个横坐标（range 右端开区间，故写 mx + 1）
            for j in range(my + 1):  # 遍历 0..my 的每个纵坐标，与 i 组合成一个候选格点
                for x, y, r in circles:  # 逐个圆检查当前格点 (i, j) 是否在圆内
                    dx, dy = i - x, j - y  # 格点相对圆心的横、纵偏移
                    if dx * dx + dy * dy <= r * r:  # 距离平方不超过半径平方，说明格点在圆内
                        ans += 1  # 该格点被覆盖，计数加一
                        break  # 已确认被覆盖，跳出内层循环，防止被多个圆重复计数
        return ans  # 返回最终统计到的格点数目
