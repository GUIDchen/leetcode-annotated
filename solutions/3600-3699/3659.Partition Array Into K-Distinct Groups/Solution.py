# 3659. Partition Array Into K-Distinct Groups（3659. 数组元素分组）
# 核心思路：每组大小固定为 k 且组内元素互不相同，故元素出现次数不能超过组数 m = n / k；先判能否均分，再统计最大频次是否超标。
# 复杂度：时间 O(n)，空间 O(不同元素个数)。
class Solution:  # 定义题解类
    def partitionArray(self, nums: List[int], k: int) -> bool:  # 判断能否把 nums 分成若干大小为 k 且组内互不相同的组
        m, mod = divmod(len(nums), k)  # m 为组数，mod 为余数（一次求出商与余数）
        if mod:  # 长度不是 k 的整数倍，无法均分
            return False  # 无法分组，直接返回假
        return max(Counter(nums).values()) <= m  # 出现次数最多的元素不超过组数，即可把每个元素分散到不同组中
