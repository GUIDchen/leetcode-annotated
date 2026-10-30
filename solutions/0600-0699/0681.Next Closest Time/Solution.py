# 题目：681. 最近时刻（Next Closest Time）
# 思路：用原时刻里的数字（可重复使用）枚举全部 4 位组合，挑出严格晚于当前时刻且时间差最小的合法时刻；若都不合法，回退到用最小数字拼成的时刻。
# 时间复杂度：O(4^4)=O(1)，数字集合最多 4 个、组合数固定为常数级；空间复杂度：O(1)，递归深度固定为 4。
class Solution:  # LeetCode 约定的题解类
    def nextClosestTime(self, time: str) -> str:  # time 是形如 "HH:MM" 的字符串
        def check(t):  # 内部函数：判断 4 位数字串 t（HHMM）是否是合法时刻
            h, m = int(t[:2]), int(t[2:])  # 拆出前两位小时与后两位分钟
            return 0 <= h < 24 and 0 <= m < 60  # 小时落在 0..23、分钟落在 0..59 才合法

        def dfs(curr):  # 内部递归函数：逐位拼出一个 4 位数字串
            if len(curr) == 4:  # 已拼够 4 位，可以判定这个时刻
                if not check(curr):  # 不是合法时刻就直接丢弃
                    return
                nonlocal ans, d  # 声明要修改外层函数里的 ans 与 d
                p = int(curr[:2]) * 60 + int(curr[2:])  # 换算成「距 0 点的分钟数」，便于比较大小
                if t < p < t + d:  # 必须严格晚于原时刻，且比当前最优解更接近
                    d = p - t  # 更新目前的最小时间差
                    ans = curr[:2] + ':' + curr[2:]  # 按 "HH:MM" 格式记下这个更优答案
                return
            for c in s:  # 每一位都可以取集合里的任意数字（允许重复使用）
                dfs(curr + c)  # 递归拼接下一位

        s = {c for c in time if c != ':'}  # 去掉冒号，得到原时刻用到的数字集合
        t = int(time[:2]) * 60 + int(time[3:])  # 原时刻换算成分钟数，作为比较基准
        d = inf  # 最小时间差先设为无穷大，表示还未找到候选
        ans = None  # 答案先置空，用来标记「没有更晚的合法时刻」
        dfs('')  # 从空串开始深度优先枚举所有组合
        if ans is None:  # 说明找不到更晚的合法时刻，只能跨到次日
            mi = min(int(c) for c in s)  # 取数字集合中的最小值
            ans = f'{mi}{mi}:{mi}{mi}'  # 用这个数字拼出次日最早的时刻
        return ans  # 返回最近的时刻
