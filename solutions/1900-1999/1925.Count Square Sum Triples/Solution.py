# 题目：1925. 统计平方和三元组的数目（Count Square Sum Triples）
# 思路：双重循环枚举 a、b，用 int(sqrt(a²+b²)) 向下取整得到候选 c，再判断 c 是否越界以及 c² 是否恰好等于平方和。
# 时间复杂度：O(n²)，两层循环各 n 次；空间复杂度：O(1)，只用到几个整型变量。
class Solution:  # LeetCode 约定的题解类
    def countTriples(self, n: int) -> int:  # n：上界，a、b、c 都在 [1, n] 内取值
        ans = 0  # 计数器：满足条件的三元组个数
        for a in range(1, n):  # 枚举第一条直角边 a
            for b in range(1, n):  # 枚举第二条直角边 b
                x = a * a + b * b  # 两条直角边的平方和
                c = int(sqrt(x))  # 开方后向下取整，得到可能的斜边
                if c <= n and c * c == x:  # 斜边不越界且平方能还原成 x，说明 x 是完全平方数
                    ans += 1  # 找到一个合法三元组，计数加一
        return ans  # 返回三元组总数
