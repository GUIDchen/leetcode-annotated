// 题目：1067. 范围内的数字计数（Digit Count in Range）
// 思路：数位 DP，f(n) 统计 d 在 [0, n] 的十进制表示中出现多少次，答案用前缀和相减 f(high) - f(low - 1)。
// 时间复杂度：O(位数 × 计数 × 10)，记忆化后状态数为 O(位数²)；空间复杂度：O(位数²)。
class Solution {  // LeetCode 约定的题解类
public:  // 成员对外可见（判题器直接调用 digitsCount）
    int d;  // 要统计的目标数字 d，存成成员变量，递归时不必层层传参
    int a[11];  // a[1..len] 从低位到高位保存当前 n 的每一位数字
    int dp[11][11];  // 记忆化数组：dp[pos][cnt] 表示剩余 pos 位、已计 cnt 个时的增量；-1 表示尚未计算

    int digitsCount(int d, int low, int high) {  // 统计区间 [low, high] 内数字 d 出现的总次数
        this->d = d;  // 形参 d 遮蔽了成员 d，用 this 显式写入成员变量供 dfs 使用
        return f(high) - f(low - 1);  // 前缀和差分：[0, high] 的次数减去 [0, low-1] 的次数
    }  // end method

    int f(int n) {  // 统计 d 在 [0, n] 所有数字的十进制表示中出现的总次数
        memset(dp, -1, sizeof dp);  // 换了一个 n，记忆化结果全部失效，先清空
        int len = 0;  // 当前拆出的位数
        while (n) {  // 逐位拆解 n
            a[++len] = n % 10;  // 取最低位，从 a[1] 开始按低位到高位存放
            n /= 10;  // 去掉已经拆出的最低位
        }  // end while
        return dfs(len, 0, true, true);  // 从最高位开始深搜：已计 0 个、处于前导零状态、贴着上界
    }  // end method

    int dfs(int pos, int cnt, bool lead, bool limit) {  // pos：当前填到第几位；cnt：已确定部分中 d 的个数；lead：是否仍全是前导零；limit：是否贴着上界
        if (pos <= 0) {  // 所有位都填完，累计值就是这一支路对整个计数的贡献
            return cnt;  // 返回该支路的 d 的个数
        }  // end if
        if (!lead && !limit && dp[pos][cnt] != -1) {  // 只缓存与具体上界无关的通用状态（无前导零、不贴上界）
            return dp[pos][cnt];  // 命中缓存，直接返回已算好的结果
        }  // end if
        int up = limit ? a[pos] : 9;  // 贴上界时当前位最多取 a[pos]，否则可以取到 9
        int ans = 0;  // 累计当前状态下的总贡献
        for (int i = 0; i <= up; ++i) {  // 枚举当前位可填的数字
            if (i == 0 && lead) {  // 仍处于前导零：这个 0 不构成数字的一部分，不能计入
                ans += dfs(pos - 1, cnt, lead, limit && i == up);  // 保持前导零标记继续下一位，计数不变
            } else {  // 已经进入有效数字位
                ans += dfs(pos - 1, cnt + (i == d), false, limit && i == up);  // 填的就是 d 则计数加一，同时解除前导零标记；只有与上界前缀完全相同时 limit 才继续为真
            }  // end if
        }  // end for：当前位所有取值分支都累加完毕
        if (!lead && !limit) {  // 只给通用状态做记忆化，贴上界的状态换 n 后会失效
            dp[pos][cnt] = ans;  // 保存结果供后续复用
        }  // end if
        return ans;  // 返回本状态的总贡献
    }  // end method
};  // end class