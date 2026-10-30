// 题目：2376. 统计特殊整数（Count Special Integers）
// 思路：数位 DP，用 mask 记录已经出现过的数字，lead 标记前导零、limit 标记是否贴着上界，记忆化复用无约束状态。
// 时间复杂度：O(位数 × 2^10 × 10)，每个状态最多枚举 10 个数字；空间复杂度：O(位数 × 2^10)，即 f 数组大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSpecialNumbers(int n) {  // n 是上界，要求统计 [1, n] 内各位数字互不相同的整数个数
        string s = to_string(n);  // 转成字符串，便于逐位读取上界数字
        int m = s.size();  // 上界 n 的十进制位数
        int f[m][1 << 10];  // f[i][mask]：从第 i 位起、已用数字集合为 mask 时的方案数
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示该状态尚未计算
        auto dfs = [&](this auto&& dfs, int i, int mask, bool lead, bool limit) -> int {  // C++23 显式对象参数，使 Lambda 能递归调用自身
            if (i >= m) {  // 所有位都填完了
                return lead ^ 1;  // 全是前导零（数字 0）不算，其余各算一个合法整数
            }
            if (!limit && !lead && f[i][mask] != -1) {  // 不受上界约束、无前导零且算过，直接复用
                return f[i][mask];
            }
            int up = limit ? s[i] - '0' : 9;  // 当前位的取值上限：贴上界时取 s[i]，否则 9
            int ans = 0;  // 累计当前状态下的方案数
            for (int j = 0; j <= up; ++j) {  // 枚举当前位填入的数字 j
                if (mask >> j & 1) {  // j 之前已经用过，违反「互不相同」
                    continue;
                }
                if (lead && j == 0) {  // 仍在前导零阶段且继续填 0，等于没使用任何数字
                    ans += dfs(i + 1, mask, true, limit && j == up);  // mask 不变，仍是前导零状态
                } else {  // 正式使用数字 j
                    ans += dfs(i + 1, mask | (1 << j), false, limit && j == up);  // 把 j 加入集合并取消前导零
                }
            }
            if (!limit && !lead) {  // 只有无上界、无前导零的状态才可以被记忆化复用
                f[i][mask] = ans;
            }
            return ans;  // 返回当前状态的方案数
        };
        return dfs(0, 0, true, true);  // 从最高位、空集合、前导零、贴住上界开始搜索
    }
};
