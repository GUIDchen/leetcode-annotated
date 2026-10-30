# 题目：2731. 移动机器人（Movement of Robots）
# 思路：机器人相撞等价于互相穿过，先算出每个机器人的最终坐标并排序，再用前缀和求所有点对距离之和。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n) 或 O(1) 取决于是否原地修改。
class Solution:  # LeetCode 约定的题解类
    def sumDistance(self, nums: List[int], s: str, d: int) -> int:  # nums 是初始坐标，s 是方向串，d 是移动秒数
        mod = 10**9 + 7  # 取模常量
        for i, c in enumerate(s):  # 逐个机器人按其方向更新最终坐标
            nums[i] += d if c == "R" else -d  # 向右走加 d，向左走减 d
        nums.sort()  # 排序后才能按位置顺序线性统计点对距离
        ans = s = 0  # ans 累计点对距离和；s 复用为前缀和变量（方向串已用完）
        for i, x in enumerate(nums):  # 从小到大遍历，每个点只需与它左边的所有点算距离
            ans += i * x - s  # x 与左侧 i 个点的距离和 = i*x - 前缀和
            s += x  # 把当前坐标并入前缀和
        return ans % mod  # 返回点对距离总和取模
