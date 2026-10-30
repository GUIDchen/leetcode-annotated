# 题目：2035. 将数组分成两个数组并最小化数组和的差（Partition Array Into Two Arrays to Minimize Sum Difference）
# 思路：折半枚举。前后各 n=len/2 个元素分别枚举子集，用「选中和 - 未选和」作为每半的贡献并按选中个数分类；配对 f[i] 与 g[n-i] 后用二分找最接近 -a 的值，取绝对值最小的差。
# 时间复杂度：O(n·2^(n/2))，主要来自子集枚举与二分；空间复杂度：O(2^(n/2))，两半的子集和都要保存。
class Solution:  # LeetCode 约定的题解类
    def minimumDifference(self, nums: List[int]) -> int:  # nums 是长度为偶数（2n）的输入数组，要求分成两个长度相等的数组
        n = len(nums) >> 1  # 折半长度：原数组长度是 2n
        f = defaultdict(set)  # f[k] 是前一半恰好选 k 个时的 (选中和 - 未选和) 集合
        g = defaultdict(set)  # g[k] 是后一半恰好选 k 个时的 (选中和 - 未选和) 集合
        for i in range(1 << n):  # 用 n 位二进制掩码枚举前一半的全部子集
            s = cnt = 0  # s/cnt：前一半的符号和与选中个数，一次赋值为 0
            s1 = cnt1 = 0  # s1/cnt1：后一半同一位掩码对应的符号和与选中个数
            for j in range(n):  # 逐位遍历前一半的 n 个元素
                if (i & (1 << j)) != 0:  # 该位为 1 表示元素被分到第一组
                    s += nums[j]  # 前一半元素计入正贡献
                    cnt += 1  # 前一半选中个数加一
                    s1 += nums[n + j]  # 后一半同一位也按「选中」处理，保证两半选取个数一致
                    cnt1 += 1  # 后一半选中个数加一
                else:  # 该位为 0 表示元素被分到第二组
                    s -= nums[j]  # 前一半元素计入负贡献
                    s1 -= nums[n + j]  # 后一半同一位也按「未选」处理
            f[cnt].add(s)  # 把该子集的前一半符号和按「选中个数」归档（set 自动去重）
            g[cnt1].add(s1)  # 把对应后一半符号和按「选中个数」归档

        ans = inf  # 答案初始化为正无穷，后面不断取更小的差
        for i in range(n + 1):  # 枚举前一半选中的元素个数 i，后一半就应选 n-i 个
            fi, gi = sorted(list(f[i])), sorted(list(g[n - i]))  # 把 f[i] 和 g[n-i] 转成有序列表，便于二分
            # min(abs(f[i] + g[n - i]))
            # 上式就是目标：让 f[i] 与 g[n-i] 的元素之和尽量接近 0，两组和的差才最小
            for a in fi:  # 枚举前一半每一个符号和 a
                left, right = 0, len(gi) - 1  # 在 gi 上二分：left/right 为闭区间端点
                b = -a  # 希望 b ≈ -a，使 a+b 尽量接近 0
                while left < right:  # 二分寻找第一个 gi[mid] >= b 的位置
                    mid = (left + right) >> 1  # 取中点（右移一位等价于整除 2）
                    if gi[mid] >= b:  # 中点值已经够大，答案位置不会在它右边
                        right = mid  # 收缩右边界
                    else:  # 中点太小
                        left = mid + 1  # 收缩左边界
                ans = min(ans, abs(a + gi[left]))  # 用二分落点的值更新答案（两组和的差取绝对值）
                if left > 0:  # 最接近 -a 的值也可能在落点左侧一个位置
                    ans = min(ans, abs(a + gi[left - 1]))  # 检查左侧相邻元素
        return ans  # 返回最小的两组和的差
