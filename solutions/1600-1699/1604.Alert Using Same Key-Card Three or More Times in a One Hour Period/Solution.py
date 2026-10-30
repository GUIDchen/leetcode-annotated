# 题目：1604. 警告一小时内使用相同员工卡大于等于三次的人（Alert Using Same Key-Card Three or More Times in a One Hour Period）
# 思路：把刷卡时间转成分钟并按人名分组，各组排序后检查连续三次的时间差是否 ≤ 60 分钟。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，按人保存全部时间。
class Solution:  # 题解类
    def alertNames(self, keyName: List[str], keyTime: List[str]) -> List[str]:  # keyName 是员工名数组，keyTime 是对应的 "HH:MM" 时间数组
        d = defaultdict(list)  # 按员工分组保存刷卡时间；defaultdict 省去「键不存在」的判断
        for name, t in zip(keyName, keyTime):  # 同时遍历名字与时间
            t = int(t[:2]) * 60 + int(t[3:])  # 把 "HH:MM" 换算成从 0 点开始的分钟数
            d[name].append(t)  # 追加到这位员工的记录列表
        ans = []  # 结果列表
        for name, ts in d.items():  # 遍历每位员工及其刷卡时间列表
            if (n := len(ts)) > 2:  # 海象运算符：先求出刷卡次数 n，再判断是否超过 2 次
                ts.sort()  # 排序后才能用连续三次的时间跨度判断
                for i in range(n - 2):  # 以 i 作为连续三次中的第一次，考察 i、i+1、i+2
                    if ts[i + 2] - ts[i] <= 60:  # 第 1 次与第 3 次间隔 ≤ 60 分钟，即一小时内刷了三次
                        ans.append(name)  # 记录该员工
                        break  # 同一员工只记录一次
        ans.sort()  # 结果按字典序排序
        return ans  # 返回需要警告的员工
