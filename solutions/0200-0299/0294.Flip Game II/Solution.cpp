// 题目：294. 翻转游戏 II（Flip Game II）🔒
// 思路：把 '+'/'-' 的局面压缩成位掩码，做记忆化博弈搜索：只要存在一步让对手必败，当前局面就是必胜态。
// 时间复杂度：O(2^n · n)，共 2^n 个局面、每个局面枚举 n 个「++」位置；空间复杂度：O(2^n)，记忆化表最多 2^n 项。
using ll = long long;  // 用 ll 作为 long long 的别名，位掩码最多 60 位，必须用 64 位整数

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int n;  // 局面长度，供 dfs 复用而不必每层重算
    unordered_map<ll, bool> memo;  // 记忆化表：位掩码 → 当前行动方是否必胜

    bool canWin(string currentState) {  // currentState：由 '+' / '-' 组成的当前局面
        n = currentState.size();  // 记录字符串长度
        ll mask = 0;  // 位掩码：第 i 位为 1 表示 currentState[i] 是 '+'
        for (int i = 0; i < n; ++i)  // 逐位扫描，把字符局面转成二进制掩码
            if (currentState[i] == '+') mask |= 1ll << i;  // 遇到 '+' 就把第 i 位置 1
        return dfs(mask);  // 从初始掩码开始判断先手是否必胜
    }  // canWin 方法结束

    bool dfs(ll mask) {  // mask：当前局面；返回当前行动方是否必胜
        if (memo.count(mask)) return memo[mask];  // 记忆化命中：直接返回上次算过的结论
        for (int i = 0; i < n - 1; ++i) {  // 枚举所有可能被翻转的「++」的起始位置
            if ((mask & (1ll << i)) == 0 || (mask & (1ll << (i + 1))) == 0) continue;  // 第 i、i+1 位不同时为 '+'，说明这里不是「++」，跳过
            if (dfs(mask ^ (1ll << i) ^ (1ll << (i + 1)))) continue;  // 翻转这两位模拟落子；若对手在新局面下仍然必胜，则这一步不可行
            memo[mask] = true;  // 找到一步让对手必败，当前局面必胜，记入记忆化表
            return true;  // 先手必胜，立即返回
        }  // 本轮枚举结束
        memo[mask] = false;  // 所有走法都让对手必胜（或已无「++」可翻），当前局面必败
        return false;  // 先手必败
    }  // dfs 结束
};  // 类定义结束