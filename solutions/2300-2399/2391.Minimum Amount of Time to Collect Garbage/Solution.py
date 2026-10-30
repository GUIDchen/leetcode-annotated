# 题目：2391. 收集垃圾的最少总时间（Minimum Amount of Time to Collect Garbage）
# 思路：垃圾总件数必捡；每种垃圾只需让车开到最后一次出现它的房子，用行驶时间前缀和累加。
# 时间复杂度：O(n + L)，L 为垃圾字符总数；空间复杂度：O(1)，last 最多只有 3 个键。
class Solution:  # LeetCode 约定的题解类
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:  # garbage：每间房子的垃圾字符串；travel：相邻房子之间的行驶耗时
        last = {}  # 字典「垃圾种类 → 最后一次出现的房子下标」，用来确定车最远要开到哪里
        ans = 0  # 答案：捡垃圾的件数（每件 1 单位时间）+ 车辆行驶耗时
        for i, s in enumerate(garbage):  # 第一遍：同时取得房子下标 i 与该房子的垃圾字符串 s
            ans += len(s)  # 每件垃圾都要停留 1 单位时间，直接累加字符个数
            for c in s:  # 逐字符扫描，字符本身就是垃圾种类 'M' / 'P' / 'G'
                last[c] = i  # 不断覆盖，循环结束后 last[c] 就是该种垃圾最后一次出现的房子下标
        ts = 0  # 车辆行驶时间的累计前缀和：从 0 号房开到当前房子 i 的总耗时
        for i, t in enumerate(travel, 1):  # 第二遍：enumerate 从 1 开始，i 号房对应 travel[i-1] 这段路
            ts += t  # 前缀和累加，ts 表示从 0 号房开到 i 号房的总时间
            ans += sum(ts for j in last.values() if i == j)  # 若 i 号房正是某种垃圾最后出现的位置，就把这趟车程计入答案
        return ans  # 返回捡垃圾的总时间
