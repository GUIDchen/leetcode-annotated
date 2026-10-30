# 题目：2094. 找出 3 位偶数（Finding 3-Digit Even Numbers）
# 思路：用 Counter 统计 digits 里每个数字的可用次数，再枚举 100~999 的所有偶数，逐一检查其数位需求是否被满足。
# 时间复杂度：O(n + 900·10)，枚举 900 个三位偶数；空间复杂度：O(1)，只有两个长度至多 10 的计数器。
class Solution:  # LeetCode 约定的题解类
    def findEvenNumbers(self, digits: List[int]) -> List[int]:  # digits：可以使用的数字，每个数字用一次就少一次
        cnt = Counter(digits)  # cnt[d] 记录数字 d 的可用次数
        ans = []  # 结果从小到大收集
        for x in range(100, 1000, 2):  # 枚举所有三位偶数（步长 2 保证末位为偶）
            cnt1 = Counter()  # cnt1 统计当前数 x 用掉了各数字多少次
            y = x  # 用副本 y 逐位拆解，保留 x 本身
            while y:  # 直到所有数位都处理完
                y, v = divmod(y, 10)  # 同时取出最低位 v 并去掉最低位
                cnt1[v] += 1  # 该数位的需求次数加一
            if all(cnt[i] >= cnt1[i] for i in range(10)):  # 每个数字的需求量都不超过可用量
                ans.append(x)  # x 合法，按升序加入答案
        return ans  # 返回所有能拼出的三位偶数
