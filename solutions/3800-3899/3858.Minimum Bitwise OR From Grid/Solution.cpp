// 题目：3858. 按位或的最小值（Minimum Bitwise OR From Grid）
// 思路：从高位到低位贪心，尝试让第 i 位取 0；若每行都能选出掩码的子集（x | mask == mask），则该位可以保持 0。
// 时间复杂度：O(n * C * log V)，n 行、每行 C 列、V 为最大值；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumOR(vector<vector<int>>& grid) {  // grid：二维网格，每行恰好选一个数，使按位或结果最小
        int mx = 0;  // 全局最大值，用来确定结果需要考察的二进制位数
        for (auto& row : grid) {  // 逐行统计最大值
            mx = max(mx, ranges::max(row));  // ranges::max 求该行最大值，再与全局最大值取较大者
        }

        int m = 32 - __builtin_clz(mx);  // __builtin_clz 数前导 0 的个数，32 减去它得到 mx 的二进制位数 m
        int ans = 0;  // ans 逐位确定最终的最小按位或值，初值为 0

        for (int i = m - 1; i >= 0; i--) {  // 从最高位往最低位逐位决策，尽量让该位保持 0
            int mask = ans | ((1 << i) - 1);  // mask：已确定的高位 + 第 i 位固定为 0 + 低 i 位放宽为全 1
            for (auto& row : grid) {  // 检查每一行是否都能选出 mask 的子集数
                bool found = false;  // 标记该行是否存在满足条件的数
                for (int x : row) {  // 遍历该行的每一个数
                    if ((x | mask) == mask) {  // 等价于 x 的每个 1 位都包含在 mask 中，即 x 是 mask 的子集
                        found = true;  // 该行找到可用数字
                        break;  // 该行已满足，无需继续检查
                    }
                }
                if (!found) {  // 某一行没有可用数字，说明第 i 位不可能取 0
                    ans |= 1 << i;  // 被迫把第 i 位置为 1
                    break;  // 结束本行的判断，进入下一位
                }
            }
        }

        return ans;  // 所有位决策完毕，返回最小按位或值
    }
};
