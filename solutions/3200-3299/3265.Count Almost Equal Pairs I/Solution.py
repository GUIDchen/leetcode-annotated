# 题目：3265. 统计近似相等数对 I（Count Almost Equal Pairs I）
# 思路：排序后按从小到大枚举 x，先枚举交换 x 的任意两位得到它能变成的所有去重数值，再累加哈希表中这些数此前已出现的次数。
# 时间复杂度：O(n·L³)，n 为数组长度、L 为数字位数（每个数的交换枚举为 O(L²) 次、每次转整数 O(L)）；空间复杂度：O(n + L²)，用于哈希表与去重集合。
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, nums: List[int]) -> int:  # nums：输入数组；返回近似相等数对的数目
        nums.sort()  # 先排序，保证每一对近似相等的数只被其中较小的那个统计到
        ans = 0  # ans：累计的近似相等数对数目
        cnt = defaultdict(int)  # cnt：已经遍历过的数的出现次数
        for x in nums:  # 按非递减顺序依次处理每个数 x
            vis = {x}  # vis：x 自身以及交换两位后能得到的所有数，用于去重
            s = list(str(x))  # 转成字符列表，方便按下标交换任意两位
            for j in range(len(s)):  # 枚举交换的右下标 j
                for i in range(j):  # 枚举交换的左下标 i，只取 i<j 以避免同一对下标被处理两次
                    s[i], s[j] = s[j], s[i]  # 交换第 i、j 位，构造出一个新的数
                    vis.add(int("".join(s)))  # 转回整数并加入去重集合
                    s[i], s[j] = s[j], s[i]  # 把字符列表还原，保证枚举其他下标对时状态正确
            ans += sum(cnt[x] for x in vis)  # 哈希表中这些数的已有出现次数之和，就是能与 x 配对的数目
            cnt[x] += 1  # 把 x 的计数加一，供后面的数匹配
        return ans  # 返回数对总数
