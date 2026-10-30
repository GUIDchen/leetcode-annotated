# 题目：2747. 统计没有收到请求的服务器数目（Count Zero Request Servers）
# 思路：日志按时间排序，询问与自增下标 zip 后按时间排序，双指针维护窗口 [r-x, r]，Counter 统计窗口内服务器数。
# 时间复杂度：O((m + q) log(m + q))，排序主导；空间复杂度：O(n + q)，计数器与结果数组。
class Solution:  # LeetCode 约定的题解类
    def countServers(  # n：服务器总数；logs：日志数组；x：时间窗口长度；queries：询问的时间点
        self, n: int, logs: List[List[int]], x: int, queries: List[int]  # 原题解把参数写成多行，这里保持原有换行
    ) -> List[int]:  # 返回每个询问对应的“没收到请求的服务器数目”
        cnt = Counter()  # 计数器：窗口内每个服务器出现的日志条数
        logs.sort(key=lambda x: x[1])  # 日志按时间（下标 1）升序排序
        ans = [0] * len(queries)  # 结果数组，先按询问个数占位
        j = k = 0  # j：窗口左指针；k：窗口右指针
        for r, i in sorted(zip(queries, count())):  # 询问与自增编号 zip 后按询问时间排序；count() 依次产生 0,1,2,... 作为原始下标
            l = r - x  # 窗口左边界
            while k < len(logs) and logs[k][1] <= r:  # 右端扩张：时间 ≤ r 的日志计入窗口
                cnt[logs[k][0]] += 1  # 该服务器日志条数加一
                k += 1  # 右指针后移
            while j < len(logs) and logs[j][1] < l:  # 左端收缩：时间 < r-x 的日志移出窗口
                cnt[logs[j][0]] -= 1  # 该服务器日志条数减一
                if cnt[logs[j][0]] == 0:  # 条数降为 0
                    cnt.pop(logs[j][0])  # 删除键，使 len(cnt) 等于窗口内出现的服务器数
                j += 1  # 左指针后移
            ans[i] = n - len(cnt)  # 总数减去窗口内出现的服务器数
        return ans  # 按原询问顺序返回
