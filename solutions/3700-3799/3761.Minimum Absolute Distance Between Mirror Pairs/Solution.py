# 3761. 镜像对之间最小绝对距离（Minimum Absolute Distance Between Mirror Pairs）
# 核心思路：一次遍历，把当前元素的镜像值 reverse(x) 与下标存入哈希表；下一个元素若命中表中键，说明它与之前某元素互为镜像，用下标差更新最小距离。
# 复杂度：时间 O(n × 数字位数)，空间 O(n)。
class Solution:  # 定义解法类
    def minMirrorPairDistance(self, nums: List[int]) -> int:  # 接口：返回镜像对之间的最小绝对距离
        def reverse(x: int) -> int:  # 内部函数：求一个整数的十进制逆序值
            y = 0  # y 累积逆序结果
            while x:  # 不断取最低位并右移原数
                v = x % 10  # 取出当前最低位
                y = y * 10 + v  # 把该位接到 y 的末尾
                x //= 10  # 原数去掉最低位
            return y  # 返回逆序后的数

        pos = {}  # pos 记录“镜像值 -> 最近下标”
        ans = inf  # ans 初始化为无穷大，表示尚未找到镜像对
        for i, x in enumerate(nums):  # 从左到右枚举每个元素及其下标
            if x in pos:  # 当前值若出现在表中，说明它等于之前某元素的镜像值
                ans = min(ans, i - pos[x])  # 用下标差更新最小距离
            pos[reverse(x)] = i  # 把当前元素的镜像值与下标登记，供后续元素匹配
        return -1 if ans == inf else ans  # 仍是无穷大说明不存在镜像对，返回 -1，否则返回最小距离
