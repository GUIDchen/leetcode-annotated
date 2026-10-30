# 题目：2191. 将杂乱无章的数字排序（Sort the Jumbled Numbers）
# 思路：用映射函数把每个数逐位替换成新数，再按 (新值, 原下标) 排序，最后按顺序取回原数字。
# 时间复杂度：O(n log n + n log M)，M 为最大位数；空间复杂度：O(n)，额外保存二元组与结果。
class Solution:  # LeetCode 约定的题解类
    def sortJumbled(self, mapping: List[int], nums: List[int]) -> List[int]:  # mapping：数字映射表；nums：待排序的数组
        def f(x: int) -> int:  # 内部函数：把整数 x 的每一位按 mapping 替换后拼回整数
            if x == 0:  # 特判 0，否则下面的 while 一次都不执行、拿不到结果
                return mapping[0]  # 0 的映射值就是 mapping[0]
            y, k = 0, 1  # y 是映射结果，k 是当前位的权重
            while x:  # 从最低位开始逐位处理，x 变成 0 时结束
                x, v = divmod(x, 10)  # divmod 同时得到商（去掉最低位）和余数（最低位数字）
                v = mapping[v]  # 用映射表替换这一位上的数字
                y = k * v + y  # 把新数字放到权重为 k 的位置上
                k *= 10  # 权重进位，准备处理更高一位
            return y  # 返回映射后的整数

        arr = sorted((f(x), i) for i, x in enumerate(nums))  # 按 (映射值, 下标) 升序排序，下标参与比较保证结果稳定
        return [nums[i] for _, i in arr]  # 按下标把原来的数字取回来
