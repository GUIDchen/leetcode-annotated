# 题目：754. 到达终点数字（Reach a Number）——中等
# 思路：先取绝对值，再贪心地累加 1+2+...+k；一旦和 s ≥ target 且 (s-target) 为偶数，就能把某个加号改成减号精确命中，此时 k 最小。
# 时间复杂度：O(sqrt(target))，因为 k 的规模约为 sqrt(2*target)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def reachNumber(self, target: int) -> int:  # target 是目标位置（可能为负）
        target = abs(target)  # 左右对称，先统一成正数处理
        s = k = 0  # s 是 1..k 的累加和，k 是当前步数
        while 1:  # 题目保证一定能到达，所以写成死循环并在内部返回
            if s >= target and (s - target) % 2 == 0:  # 已越过目标且差值可被 2 整除，翻转某一步方向即可精确命中
                return k
            k += 1  # 步数加一
            s += k  # 把新的一步累加到和里
