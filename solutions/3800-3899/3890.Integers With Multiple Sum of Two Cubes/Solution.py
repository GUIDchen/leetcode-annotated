# 题目：3890. 可由多种立方和构造的整数（Integers With Multiple Sum of Two Cubes）
# 思路：预处理所有 a³+b³ ≤ 1e9 的组合并计数，出现次数大于 1 的和即为“好数”；排序后每次查询用二分取 ≤ n 的前缀。
# 时间复杂度：预处理 O(1000²) 约 1e6，单次查询 O(log |GOOD|)；空间复杂度：O(1000²) 用于哈希表计数。
LIMIT = 10**9  # 立方和的上界

cnt = defaultdict(int)  # 哈希表：立方和 → 能被多少对 (a, b) 表示
cubes = [i**3 for i in range(1001)]  # 预存 0..1000 的立方值

for a in range(1, 1001):  # 枚举较小的那一项 a
    for b in range(a, 1001):  # 强制 b ≥ a，避免 (a,b) 与 (b,a) 被重复计数
        x = cubes[a] + cubes[b]  # 两数立方和
        if x > LIMIT:  # 超过上界
            break  # b 继续增大只会更大，直接跳出内层循环
        cnt[x] += 1  # 该立方和的表示方式数加 1

GOOD = sorted(x for x, v in cnt.items() if v > 1)  # 筛选出表示方式多于一种的好数，并排序


class Solution:  # LeetCode 约定的题解类
    def findGoodIntegers(self, n: int) -> list[int]:  # n：查询上界
        idx = bisect_right(GOOD, n)  # 二分出 ≤ n 的好数个数
        return GOOD[:idx]  # 返回前缀切片作为答案
