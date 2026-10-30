# 题目：1900. 最佳运动员的比拼回合（The Earliest and Latest Rounds Where Players Compete）
# 思路：记忆化搜索。位掩码枚举每轮所有对局的胜负，强制两名指定选手本轮晋级，按晋级顺序重新编号后递归到他们相遇，统计回合数的最小值与最大值。
# 时间复杂度：O(n^2 · 2^(n/2))，每个 (l, r, n) 状态只算一次；空间复杂度：O(n^2) 记忆化缓存。
@cache  # 记忆化装饰器：同一个 (l, r, n) 只计算一次
def dfs(l: int, r: int, n: int):  # l、r：两人的当前下标；n：当前剩余人数
    if l + r == n - 1:  # 两人位置对称，本轮必然相遇
        return [1, 1]  # 只需 1 轮，最早与最晚相同
    res = [inf, -inf]  # 结果容器：[最早回合, 最晚回合]
    m = n >> 1  # 本轮对局数
    for i in range(1 << m):  # 位掩码枚举每场对局的胜者
        win = [False] * n  # win[j] 表示位置 j 的选手是否晋级
        for j in range(m):  # 逐场确定胜者
            if i >> j & 1:  # 第 j 位为 1：左侧位置 j 获胜
                win[j] = True  # 左侧选手晋级
            else:  # 否则右侧选手获胜
                win[n - 1 - j] = True  # 对称位置 n-1-j 晋级
        if n & 1:  # 人数为奇数时中间选手轮空
            win[m] = True  # 轮空者直接晋级
        win[n - 1 - l] = win[n - 1 - r] = False  # 取消两人对手的晋级
        win[l] = win[r] = True  # 两人本轮都必须获胜晋级
        a = b = c = 0  # a、b：两人新下标；c：晋级人数
        for j in range(n):  # 按位置顺序重新编号
            if j == l:  # 遇到 l
                a = c  # 记下 l 在晋级者中的序号
            if j == r:  # 遇到 r
                b = c  # 记下 r 在晋级者中的序号
            if win[j]:  # 该位置晋级
                c += 1  # 晋级人数加一
        x, y = dfs(a, b, c)  # 递归求下一轮的最早/最晚回合
        res[0] = min(res[0], x + 1)  # 加上本轮，更新最早回合
        res[1] = max(res[1], y + 1)  # 加上本轮，更新最晚回合
    return res  # 返回 [最早, 最晚]


class Solution:  # LeetCode 约定的题解类
    def earliestAndLatest(  # 公开接口：返回最早与最晚的相遇回合
        self, n: int, firstPlayer: int, secondPlayer: int  # n：选手数；两名选手编号从 1 开始
    ) -> List[int]:  # 返回长度为 2 的答案列表
        return dfs(firstPlayer - 1, secondPlayer - 1, n)  # 编号转成 0 起下标后开始搜索
