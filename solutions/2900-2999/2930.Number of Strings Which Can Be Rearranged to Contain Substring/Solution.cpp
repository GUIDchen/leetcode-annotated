// 题目：2930. 重新排列后包含指定子字符串的字符串数目（Number of Strings Which Can Be Rearranged to Contain Substring）
// 思路：只看每种字符出现的次数。用记忆化搜索枚举长度为 n 的字符串，状态 (i, l, e, t) 记录还剩几个位置以及 l、e、t 已出现的次数（分别封顶 1、2、1），终态要求恰好 1 个 l、2 个 e、1 个 t。
// 时间复杂度：O(n * 2 * 3 * 2) = O(n)，状态数只有 12n 个；空间复杂度：O(n * 2 * 3 * 2) = O(n)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int stringCount(int n) {  // n 为字符串长度
        const int mod = 1e9 + 7;  // 答案要对 1e9+7 取模
        using ll = long long;  // 乘法容易溢出，中间结果用 64 位
        ll f[n + 1][2][3][2];  // 记忆化数组：f[i][l][e][t] 表示还剩 i 个位置时的方案数
        memset(f, -1, sizeof(f));  // 全部置 -1，表示该状态还没被计算过
        function<ll(int, int, int, int)> dfs = [&](int i, int l, int e, int t) -> ll {  // l、e、t 分别是三种字符已经出现的次数
            if (i == 0) {  // 位置已经填完
                return l == 1 && e == 2 && t == 1 ? 1 : 0;  // 恰好含 1 个 l、2 个 e、1 个 t 才合法（此时必然包含 "leet"）
            }
            if (f[i][l][e][t] != -1) {  // 这个状态算过了
                return f[i][l][e][t];  // 直接返回记忆化结果
            }
            ll a = dfs(i - 1, l, e, t) * 23 % mod;  // 放其余 23 个字母，三种计数都不变
            ll b = dfs(i - 1, min(1, l + 1), e, t) % mod;  // 放 l，次数封顶在 1，只关心是否出现过
            ll c = dfs(i - 1, l, min(2, e + 1), t) % mod;  // 放 e，次数封顶在 2，因为只需要 2 个
            ll d = dfs(i - 1, l, e, min(1, t + 1)) % mod;  // 放 t，次数封顶在 1
            return f[i][l][e][t] = (a + b + c + d) % mod;  // 四种选择求和取模，并写回记忆化数组
        };
        return dfs(n, 0, 0, 0);  // 从 n 个空位、三种字符都还没出现开始搜
    }
};
