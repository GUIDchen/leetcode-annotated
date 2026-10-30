# 题目：1733. 需要教语言的最少人数（Minimum Number of People to Teach）
# 思路：先把“与好友没有任何共同语言”的人放进集合去重，再统计这些人已会语言的频次；选最普及的一种统一教，答案即集合大小减去最大频次。
# 时间复杂度：O(m·L² + k)，m 为好友对数、L 为每人语言数；空间复杂度：O(k + 25)，集合与计数器开销。
class Solution:  # LeetCode 约定的题解类
    def minimumTeachings(  # 返回使所有好友都能沟通所需教的最少人数
        self, n: int, languages: List[List[int]], friendships: List[List[int]]  # n 是语言总数，languages[i] 是第 i+1 人会说的语言，friendships 是好友对
    ) -> int:  # 形参列表结束，返回最少需要教的人数
        def check(u: int, v: int) -> bool:  # 判断 u、v 两人之间是否存在共同语言
            for x in languages[u - 1]:  # 枚举 u 会说的每一种语言
                for y in languages[v - 1]:  # 枚举 v 会说的每一种语言
                    if x == y:  # 找到相同的语言
                        return True  # 两人可以直接沟通
            return False  # 没有任何交集，说明这一对需要被教

        s = set()  # 需要被覆盖的人，集合自动去重
        for u, v in friendships:  # 逐个检查好友关系
            if not check(u, v):  # 只有无法沟通的一对才需要处理
                s.add(u)  # 记录前者
                s.add(v)  # 记录后者
        cnt = Counter()  # 统计集合 s 中每种语言的掌握人数
        for u in s:  # 遍历所有需要被覆盖的人
            for l in languages[u - 1]:  # 遍历他会说的语言
                cnt[l] += 1  # 该语言的计数加一
        return len(s) - max(cnt.values(), default=0)  # 选众数语言统一教，其他人各改学一次；default=0 兼容集合为空
