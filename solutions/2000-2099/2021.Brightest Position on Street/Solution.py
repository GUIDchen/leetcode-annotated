# 题目：2021. 街上最亮的位置（Brightest Position on Street）
# 思路：把每盏灯的照亮区间 [位置 - 半径, 位置 + 半径] 记录成差分表，按坐标升序扫描前缀和；用严格大于更新，即可在同一亮度下保留更小的坐标。
# 时间复杂度：O(n log n)，排序端点占主导；空间复杂度：O(n)，差分表最多 2n 个键。
class Solution:  # LeetCode 约定的题解类
    def brightestPosition(self, lights: List[List[int]]) -> int:  # lights 的每项是 [位置, 半径]，返回最亮位置的编号
        d = defaultdict(int)  # 差分表：未出现的坐标默认亮度变化量为 0
        for i, j in lights:  # 逐盏灯处理：i 是位置，j 是光照半径
            l, r = i - j, i + j  # 该灯照亮的闭区间 [l, r]
            d[l] += 1  # 区间左端点亮度加一
            d[r + 1] -= 1  # 右端点之后亮度减一，前缀和即可还原覆盖数
        ans = s = mx = 0  # ans 是答案坐标，s 是当前亮度，mx 是历史最大亮度
        for k in sorted(d):  # 按坐标升序扫描所有差分端点
            s += d[k]  # 累加差分值得到当前位置的亮度
            if mx < s:  # 严格更亮才更新，保证同亮度时答案坐标更小
                mx = s  # 记录新的最大亮度
                ans = k  # 记录取得最大亮度的坐标
        return ans  # 返回最亮位置（同亮度时取编号最小者）
