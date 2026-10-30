# 题目：1840. 最高建筑高度（Maximum Building Height）
# 思路：加入 {1, 0} 与 {n, n-1} 两个哨兵后排序，先左后右各扫一遍传播"相邻楼高差不超过 1"的约束，再在每对相邻约束点之间取峰顶 (h1+h2+距离)//2。
# 时间复杂度：O(m log m)，m 为限制点个数，主要来自排序；空间复杂度：O(m)，就地修改 restrictions 列表。
class Solution:  # LeetCode 约定的题解类
    def maxBuilding(self, n: int, restrictions: List[List[int]]) -> int:  # n：建筑总数；restrictions：{位置, 最大高度} 限制列表
        r = restrictions  # 直接引用传入列表，后续原地修改（不额外拷贝）
        r.append([1, 0])  # 哨兵：第 1 栋高度必为 0，所以它的上限就是 0
        r.sort()  # 按位置升序排序，方便从左往右传播约束
        if r[-1][0] != n:  # 最后一个位置不是 n，说明第 n 栋没有限制
            r.append([n, n - 1])  # 补哨兵：最多每层涨 1，故 hn 的上限是 n-1
        m = len(r)  # 补完哨兵后的约束点个数
        for i in range(1, m):  # 从左往右扫一遍
            r[i][1] = min(r[i][1], r[i - 1][1] + r[i][0] - r[i - 1][0])  # 高差不超过位置差，取更紧的上限
        for i in range(m - 2, 0, -1):  # 从右往左扫一遍，跳过 0 号哨兵（它已经是 0）
            r[i][1] = min(r[i][1], r[i + 1][1] + r[i + 1][0] - r[i][0])  # 用右侧约束回头看能否把当前点压得更低
        ans = 0  # 记录全局最高可达高度
        for i in range(m - 1):  # 枚举每一对相邻约束点之间的空隙
            t = (r[i][1] + r[i + 1][1] + r[i + 1][0] - r[i][0]) // 2  # 两端各自爬升后平分剩余距离，得到这段的峰顶高度
            ans = max(ans, t)  # 更新最大值
        return ans  # 返回可达到的最高建筑高度
