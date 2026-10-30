# 题目：1643. 第 K 条最小指令（Kth Smallest Instructions）
# 思路：逐位贪心，先用 comb 算出「这一位放 H」的方案数，若小于 k 则放 V 并令 k 减去这些方案，否则放 H。
# 时间复杂度：O((h+v)·h)，每一步组合数计算量级为 O(h)；空间复杂度：O(h+v)，结果列表长度。
class Solution:  # LeetCode 约定的题解类
    def kthSmallestPath(self, destination: List[int], k: int) -> str:  # destination = [行数, 列数]；k 是 1-based 的字典序序号，返回第 k 小的指令串
        v, h = destination  # v：还需走的 V（纵向）步数；h：还需走的 H（横向）步数
        ans = []  # ans 逐位收集指令
        for _ in range(h + v):  # 一共要走 h + v 步
            if h == 0:  # 剩余步数里没有 H 了，后面只能全填 V
                ans.append("V")  # 追加字符 "V"
            else:  # 否则需要比较「以 H 开头」的方案数
                x = comb(h + v - 1, h - 1)  # comb(n, r) 即 C(n, r)：先放 H，再从剩余 h + v - 1 步里挑 h - 1 个 H
                if k > x:  # k 比这些方案多，说明答案不以 H 开头
                    ans.append("V")  # 这一位确定为 "V"
                    v -= 1  # 消耗一个 V 步
                    k -= x  # 跳过 x 个以 H 开头的串，把 k 换算到本层序号
                else:  # 否则答案以 H 开头
                    ans.append("H")  # 这一位确定为 "H"
                    h -= 1  # 消耗一个 H 步
        return "".join(ans)  # 把逐位结果拼成字符串返回
