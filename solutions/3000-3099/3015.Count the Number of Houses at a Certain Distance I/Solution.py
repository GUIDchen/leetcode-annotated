# 题目：3015. 按距离统计房屋对数目 I（Count the Number of Houses at a Certain Distance I）
# 思路：房屋沿一条链排列，另外只有一条额外边 (x, y)，所以任意两点间最短距离只有三种候选：只走链、先到 x 跨边到 y 再走、或反向跨边。枚举每一对房屋取三者最小值，统计到 1..n 的距离桶里；一对房屋有正反两种排列，所以每次加 2。
# 时间复杂度：O(n^2)，枚举所有房屋对；空间复杂度：O(n)，答案数组长度为 n。
class Solution:  # LeetCode 约定的题解类
    def countOfPairs(self, n: int, x: int, y: int) -> List[int]:  # n 是房屋数量；x、y 是额外边两端（1-indexed）；返回距离 1..n 的房屋对数目
        x, y = x - 1, y - 1  # 题目下标从 1 开始，统一转成从 0 开始，方便直接用差值算距离
        ans = [0] * n  # ans[d-1] 存放距离为 d 的房屋对数目，长度 n 覆盖距离 1..n
        for i in range(n):  # 枚举房屋对的左端点 i
            for j in range(i + 1, n):  # 只枚举 j > i，每对房屋只算一次，稍后用 +2 补上对称方向
                a = j - i  # 方案一：只沿主链走，距离是 j - i
                b = abs(i - x) + 1 + abs(j - y)  # 方案二：i 走到 x，跨过额外边算 1 步，再从 y 走到 j
                c = abs(i - y) + 1 + abs(j - x)  # 方案三：反向使用额外边，i 到 y、跨边到 x、再到 j
                ans[min(a, b, c) - 1] += 2  # 三种走法取最小距离 d，计入 ans[d-1]；一对房屋对应正反两种排列，所以加 2
        return ans  # 返回按距离统计的房屋对数目
