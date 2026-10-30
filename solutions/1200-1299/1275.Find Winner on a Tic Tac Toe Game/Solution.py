class Solution:  # LeetCode 约定的题解类
    def tictactoe(self, moves: List[List[int]]) -> str:  # moves：按时间顺序的落子坐标，A 先手
        n = len(moves)  # 总落子步数
        cnt = [0] * 8  # 8 个计数器：0~2 三行、3~5 三列、6 主对角线、7 副对角线
        for k in range(n - 1, -1, -2):  # 倒序遍历、步长 -2，只看同一玩家落下的格子
            i, j = moves[k]  # 取出这一步的行 i 与列 j
            cnt[i] += 1  # 第 i 行的计数加一（行 i 对应计数器 i）
            cnt[j + 3] += 1  # 第 j 列的计数加一（第 j 列映射到 j+3）
            if i == j:  # 落子在主对角线上
                cnt[6] += 1  # 主对角线计数加一
            if i + j == 2:  # 落子在副对角线上（i + j == 2）
                cnt[7] += 1  # 副对角线计数加一
            if any(v == 3 for v in cnt):  # 任意一条线已经凑满 3 个
                return "B" if k & 1 else "A"  # k 为奇数说明这一步是 B 下的，否则是 A
        return "Draw" if n == 9 else "Pending"  # 下满 9 步还没人赢就是平局，否则仍在进行
