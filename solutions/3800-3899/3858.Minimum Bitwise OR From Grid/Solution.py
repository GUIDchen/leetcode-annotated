# 题目：3858. 按位或的最小值（Minimum Bitwise OR From Grid）
# 思路：从高位到低位贪心，尝试让第 i 位取 0；若每行都能选出掩码的子集（x | mask == mask），则该位可以保持 0。
# 时间复杂度：O(n * C * log V)，n 行、每行 C 列、V 为最大值；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def minimumOR(self, grid: List[List[int]]) -> int:  # grid：二维网格，每行恰好选一个数，返回按位或的最小值
        mx = max(map(max, grid))  # 先取网格中的最大值，用来确定需要考察的二进制位数
        m = mx.bit_length()  # bit_length 得到最大值 mx 的二进制位数 m
        ans = 0  # ans 逐位确定最终的最小按位或值，初值为 0
        for i in range(m - 1, -1, -1):  # 从最高位往最低位逐位决策，尽量让该位保持 0
            mask = ans | ((1 << i) - 1)  # mask：已确定的高位 + 第 i 位固定为 0 + 低 i 位放宽为全 1
            for row in grid:  # 检查每一行是否都能选出 mask 的子集数
                found = False  # 标记该行是否存在满足条件的数
                for x in row:  # 遍历该行的每一个数
                    if (x | mask) == mask:  # 等价于 x 的每个 1 位都包含在 mask 中
                        found = True  # 该行找到可用数字
                        break  # 该行已满足，无需继续检查
                if not found:  # 某一行没有可用数字，说明第 i 位不可能取 0
                    ans |= 1 << i  # 被迫把第 i 位置为 1
                    break  # 结束本行的判断，进入下一位
        return ans  # 所有位决策完毕，返回最小按位或值
