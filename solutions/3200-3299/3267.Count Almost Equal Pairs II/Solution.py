# 题目：3267. 统计近似相等数对 II（Count Almost Equal Pairs II）
# 思路：在 I 的基础上把「至多交换两次」也枚举进来：先交换 (i, j)，再在剩余位上交换 (p, q)，把所有可达数值去重后按从小到大用哈希表累计匹配数。
# 时间复杂度：O(n·L⁴)，n 为数组长度、L 为数字位数（每个数枚举两对下标共 O(L⁴) 次，每次转整数 O(L)）；空间复杂度：O(n + L⁴)，用于哈希表与去重集合。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, nums: List[int]) -> int:  # nums：输入数组；返回近似相等数对的数目
        nums.sort()  # 先排序，保证每一对近似相等的数只被其中较小的那个统计到
        ans = 0  # ans：累计的近似相等数对数目
        cnt = defaultdict(int)  # cnt：已经遍历过的数的出现次数
        for x in nums:  # 按非递减顺序依次处理每个数 x
            vis = {x}  # vis：x 自身以及至多交换两次后能得到的所有数，用于去重
            s = list(str(x))  # 转成字符列表，方便按下标交换任意两位
            m = len(s)  # m：数字的字符长度
            for j in range(m):  # 枚举第一次交换的右下标 j
                for i in range(j):  # 枚举第一次交换的左下标 i，只取 i<j
                    s[i], s[j] = s[j], s[i]  # 第一次交换第 i、j 位
                    vis.add(int("".join(s)))  # 只交换一次的方案也要计入
                    for q in range(i + 1, m):  # 枚举第二次交换的右下标 q，必须避开已参与第一次交换的位置
                        for p in range(i + 1, q):  # 枚举第二次交换的左下标 p，取 i<p<q 以避免重复枚举
                            s[p], s[q] = s[q], s[p]  # 执行第二次交换
                            vis.add(int("".join(s)))  # 至多交换两次得到的新数去重收集
                            s[p], s[q] = s[q], s[p]  # 还原第二次交换
                    s[i], s[j] = s[j], s[i]  # 还原第一次交换，保证枚举其他下标对时状态正确
            ans += sum(cnt[x] for x in vis)  # 哈希表中这些数的已有出现次数之和，就是能与 x 配对的数目
            cnt[x] += 1  # 把 x 的计数加一，供后面的数匹配
        return ans  # 返回数对总数
