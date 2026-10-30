# 题目：1488. 避免洪水泛滥（Avoid Flood in The City）
# 核心思路：贪心。湖泊再次下雨前，用上次下雨之后最早的晴天抽干它；用有序集合支持二分查找与删除。
# 时间复杂度：O(n log n)；空间复杂度：O(n)，有序集合与哈希表。
class Solution:  # LeetCode 约定的题解类
    def avoidFlood(self, rains: List[int]) -> List[int]:  # rains[i] 为第 i 天降雨的湖编号，0 表示晴天
        n = len(rains)  # 总天数
        ans = [-1] * n  # 结果数组，雨天先填 -1
        sunny = SortedList()  # 有序集合：保存所有未使用的晴天日期，支持二分与删除
        rainy = {}  # 哈希表：湖编号 → 最近一次下雨的日期
        for i, v in enumerate(rains):  # 逐天模拟
            if v:  # 非 0 即下雨天
                if v in rainy:  # 该湖之前下过雨，必须在两次降雨之间抽干
                    idx = sunny.bisect_right(rainy[v])  # 找上一个雨天之后的第一个可用晴天
                    if idx == len(sunny):  # 后面没有晴天可用
                        return []  # 返回空列表表示无法避免洪水
                    ans[sunny[idx]] = v  # 用这个晴天抽干湖 v
                    sunny.discard(sunny[idx])  # 移除已占用的晴天
                rainy[v] = i  # 更新该湖最近的下雨日期
            else:  # 否则是晴天
                sunny.add(i)  # 记入可用晴天集合，留待以后抽水
                ans[i] = 1  # 空闲晴天填任意正数即可，这里填 1
        return ans  # 返回合法的抽水方案
