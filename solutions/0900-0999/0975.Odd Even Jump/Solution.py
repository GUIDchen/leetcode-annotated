# 题目：975. 奇偶跳（Odd Even Jump）
# 思路：逆序扫描有序字典预处理出每个位置奇/偶跳的落点，再记忆化搜索每个起点能否跳到末尾。
# 时间复杂度：O(n log n)，建表 O(n log n) + 记忆化 O(n)；空间复杂度：O(n)，两个转移表与缓存。
class Solution:  # LeetCode 约定的题解类
    def oddEvenJumps(self, arr: List[int]) -> int:  # arr：输入数组，返回能跳到末尾的下标个数
        @cache  # 记忆化装饰器：同一个 (i, k) 只计算一次
        def dfs(i: int, k: int) -> bool:  # 记忆化搜索：i 为当前位置，k=1 表示下一步是奇数跳，k=0 表示偶数跳
            if i == n - 1:  # 已经到达末尾，说明这条跳法成功
                return True  # 成功返回 True
            if g[i][k] == -1:  # 该跳法没有落点，无法继续
                return False  # 失败返回 False
            return dfs(g[i][k], k ^ 1)  # 落点确定后换另一种跳法继续搜索（k ^ 1 在 0/1 间切换）

        n = len(arr)  # n 为数组长度
        g = [[0] * 2 for _ in range(n)]  # g[i][k] 记录从 i 出发、k 类跳的落点下标，-1 表示跳不了
        sd = SortedDict()  # 有序字典：值 → 下标，逆序扫描时保存右侧已处理的元素
        for i in range(n - 1, -1, -1):  # 从右往左遍历，保证查表时右侧元素都已就位
            j = sd.bisect_left(arr[i])  # 奇数跳要跳到右侧不小于 arr[i] 的最小值，bisect_left 给出第一个 >= 的位置
            g[i][1] = sd.values()[j] if j < len(sd) else -1  # 位置合法则取对应的下标，否则记 -1 表示无法跳
            j = sd.bisect_right(arr[i]) - 1  # 偶数跳要跳到右侧不大于 arr[i] 的最大值，bisect_right 减一落到 <= 的位置
            g[i][0] = sd.values()[j] if j >= 0 else -1  # 位置合法则取对应的下标，否则记 -1 表示无法跳
            sd[arr[i]] = i  # 把当前值及其下标放入有序字典，供更左侧的元素查询
        return sum(dfs(i, 1) for i in range(n))  # 从每个下标出发、第一步为奇数跳，求和即能跳到末尾的起点个数
