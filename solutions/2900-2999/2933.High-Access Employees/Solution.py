# 题目：2933. 高访问员工（High-Access Employees）
# 思路：把每条访问时间换算成分钟数并按员工分组，组内排序后用长度为 3 的滑动窗口检查是否存在 1 小时内访问 3 次。
# 时间复杂度：O(n log n)，主要是各员工时间列表的排序；空间复杂度：O(n)，字典保存全部访问时间。
class Solution:  # LeetCode 约定的题解类
    def findHighAccessEmployees(self, access_times: List[List[str]]) -> List[str]:  # access_times：每项是 [姓名, "HHMM"]
        d = defaultdict(list)  # 字典：姓名 -> 该员工所有访问时间（分钟数），缺失的键会自动建成空列表
        for name, t in access_times:  # 逐条解包访问记录
            d[name].append(int(t[:2]) * 60 + int(t[2:]))  # "HHMM" 的前两位是小时、后两位是分钟，统一换算成分钟数
        ans = []  # 保存所有高访问员工的姓名
        for name, ts in d.items():  # 逐个员工独立判断
            ts.sort()  # 时间升序排序，便于用间隔为 2 的窗口判断是否在 1 小时内
            if any(ts[i] - ts[i - 2] < 60 for i in range(2, len(ts))):  # 只要存在连续三次访问跨度小于 60 分钟，就满足条件
                ans.append(name)  # 该员工是高访问员工，加入答案（每个员工只会加一次）
        return ans  # 返回高访问员工名单
