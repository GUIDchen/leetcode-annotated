# 题目：906. 超级回文数（Super Palindromes）
# 核心思路：超级回文数的平方根必须是回文数，先枚举回文根并镜像生成所有回文数，再平方判断是否落在区间内且仍是回文。
# 时间复杂度：O(M log R)，M≈2×10^5 个候选回文数，每个判回文 O(log R)；空间复杂度：O(M) 存储回文数。
ps = []  # 预处理结果：保存所有由回文根镜像生成的回文数
for i in range(1, 10**5 + 1):  # 枚举回文根，10^5 的上界足以覆盖 10^18 的平方范围
    s = str(i)  # 回文根的字符串形式
    t1 = s[::-1]  # 反转得到偶数长度回文的镜像部分
    t2 = s[:-1][::-1]  # 去掉末位再反转，得到奇数长度回文的镜像部分
    ps.append(int(s + t1))  # 记录偶数长度回文 s + reverse(s)
    ps.append(int(s + t2))  # 记录奇数长度回文 s + reverse(s 去掉末位)


class Solution:  # LeetCode 约定的题解类
    def superpalindromesInRange(self, left: str, right: str) -> int:  # left/right：闭区间边界，用字符串给出以免整数越界
        def is_palindrome(x: int) -> bool:  # 内部函数：判断 x 是否是回文数
            y, t = 0, x  # y 存反转结果，t 是逐位取数的临时变量
            while t:  # 只要 t 还有位就继续
                y = y * 10 + t % 10  # 把当前最低位接到 y 的末尾
                t //= 10  # 去掉最低位
            return x == y  # 反转后与原数相同即为回文数

        l, r = int(left), int(right)  # 把区间边界转成整数
        return sum(l <= x <= r and is_palindrome(x) for x in map(lambda x: x * x, ps))  # 对每个回文数求平方，统计落在区间内且仍是回文数的个数
