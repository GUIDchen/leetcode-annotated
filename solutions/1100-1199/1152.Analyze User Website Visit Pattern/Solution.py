# 题目：1152. 用户网站访问行为分析（Analyze User Website Visit Pattern）
# 思路：先按用户分组并按时间戳排序，枚举每个用户访问序列的所有三元组并去重，统计每个三元组被多少用户使用，取次数最多且字典序最小的。
# 时间复杂度：O(U * m^3)，U 为用户数、m 为单用户访问数；空间复杂度：O(不同三元组个数)。
class Solution:  # LeetCode 约定的题解类
    def mostVisitedPattern(  # 返回出现次数最多且字典序最小的三连访问模式
        self, username: List[str], timestamp: List[int], website: List[str]  # 形参：用户列表、时间戳列表、网站列表
    ) -> List[str]:  # 返回值是长度为 3 的网站名列表
        d = defaultdict(list)  # d 记录每个用户按时间排序后的访问序列
        for user, _, site in sorted(  # 把三个平行数组按时间戳排序，保证序列按访问先后排列
            zip(username, timestamp, website), key=lambda x: x[1]  # zip 合并三个数组，key 取时间戳
        ):  # 排序结束，开始逐条分组
            d[user].append(site)  # 把当前网站追加到该用户的访问序列

        cnt = Counter()  # cnt 统计每个三元组被多少个用户访问过
        for sites in d.values():  # 逐个用户处理
            m = len(sites)  # 该用户访问的网站个数
            s = set()  # 用集合去重：同一用户重复的三元组只算一次
            if m > 2:  # 访问数不足 3 个无法组成三元组
                for i in range(m - 2):  # 枚举三元组的第一个位置
                    for j in range(i + 1, m - 1):  # 第二个位置
                        for k in range(j + 1, m):  # 第三个位置
                            s.add((sites[i], sites[j], sites[k]))  # 把 (a, b, c) 这个访问顺序加入集合
            for t in s:  # 该用户贡献的所有不同三元组
                cnt[t] += 1  # 每个不同三元组计数加一
        return list(sorted(cnt.items(), key=lambda x: (-x[1], x[0]))[0][0])  # 按「次数降序、字典序升序」排序后取第一个，并转成列表返回
