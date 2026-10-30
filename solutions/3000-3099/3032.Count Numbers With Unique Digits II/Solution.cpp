// 题目：3032. 统计各位数字都不同的数字个数 II（Count Numbers With Unique Digits II）
// 思路：数位 DP。dfs(pos, mask, limit) 表示填到第 pos 位、已用数字集合为 mask、是否贴着上界的方案数；分别求出 [0, b] 与 [0, a-1] 的个数再相减。
// 时间复杂度：O(位数 × 2^10 × 10)，状态数为 pos × mask；空间复杂度：O(位数 × 2^10)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberCount(int a, int b) {  // a、b：闭区间 [a, b] 的左右端点
        string num = to_string(b);  // 先把上界转成字符串，方便按位枚举
        int f[num.size()][1 << 10];  // 记忆化数组 f[pos][mask]：mask 用二进制记录哪些数字已经用过
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示该状态还没有计算过
        function<int(int, int, bool)> dfs = [&](int pos, int mask, bool limit) {  // 数位 DP：pos 当前位置，mask 已用数字集合，limit 表示是否贴着上界
            if (pos >= num.size()) {  // 所有数位都填完了
                return mask ? 1 : 0;  // mask 非 0 说明填出的是正数，合法；全前导零的 0 不计入
            }
            if (!limit && f[pos][mask] != -1) {  // 不贴上限时，同状态的结果与前面的位无关，可以复用
                return f[pos][mask];  // 直接返回缓存值
            }
            int up = limit ? num[pos] - '0' : 9;  // 当前位能填的最大数字：贴上限就受 num[pos] 限制
            int ans = 0;  // ans：当前状态下的合法方案数
            for (int i = 0; i <= up; ++i) {  // 枚举当前位可以填的数字
                if (mask >> i & 1) {  // 该数字此前已经用过
                    continue;  // 会造成重复数字，直接跳过
                }
                int nxt = mask == 0 && i == 0 ? 0 : mask | 1 << i;  // 仍是前导零就不记录 0，否则把数字 i 并入集合
                ans += dfs(pos + 1, nxt, limit && i == up);  // 递归下一位；只有贴着上限且取到上界时下一位才继续受限
            }
            if (!limit) {  // 只有不贴上限的状态才具有通用性，可以缓存
                f[pos][mask] = ans;  // 记录答案，后续相同状态直接取用
            }
            return ans;  // 返回当前状态的方案数
        };

        int y = dfs(0, 0, true);  // y：[0, b] 内各位数字互不相同的数字个数
        num = to_string(a - 1);  // 上界换成 a-1，用于统计前缀
        memset(f, -1, sizeof(f));  // 上界变了，清空记忆化数组避免脏数据
        int x = dfs(0, 0, true);  // x：[0, a-1] 内各位数字互不相同的数字个数
        return y - x;  // 两个前缀结果相减，得到 [a, b] 的答案
    }
};