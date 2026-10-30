# 题目：1231. 分享巧克力（Divide Chocolate）
# 思路：二分答案 + 贪心校验。最小块甜度越大越难切够 k+1 块，具有单调性；对候选下限贪心切分，能切出超过 k 块即可行。
# 时间复杂度：O(n log S)，S 为甜度总和，每次校验扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maximizeSweetness(self, sweetness: List[int], k: int) -> int:  # sweetness：每块巧克力甜度；k：人数（要切成 k+1 块），返回最小块的最大可能甜度
        def check(x: int) -> bool:  # 校验函数：假设每块至少 x 甜度，判断能否切出多于 k 块
            s = cnt = 0  # s：当前累积的甜度；cnt：已切出的块数（一起初始化）
            for v in sweetness:  # 按顺序遍历，越早凑够 x 就切，把余量留给后面的块
                s += v  # 把当前这块的甜度累加进来
                if s >= x:  # 攒够 x 即切下这一块
                    s = 0  # 切完重新开始累积
                    cnt += 1  # 切出的块数加 1
            return cnt > k  # 能切出超过 k 块说明下限 x 可行

        l, r = 0, sum(sweetness)  # 二分区间：下界 0，上界为全部甜度之和
        while l < r:  # 在单调答案区间上二分，找最大的可行下限
            mid = (l + r + 1) >> 1  # 取上中位数，保证 l < mid，避免死循环
            if check(mid):  # x 可行，答案至少是 mid，抬高下界
                l = mid  # x 不可行，答案在左半区间
            else:  # 上界降下来
                r = mid - 1  # 结束二分循环
        return l  # 循环结束时 l == r，即最大可行下限
