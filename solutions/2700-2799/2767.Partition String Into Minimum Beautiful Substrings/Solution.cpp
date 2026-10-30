// 题目：2767. 将字符串分割为最少的美丽子字符串（Partition String Into Minimum Beautiful Substrings）
// 思路：预处理 5 的幂（二进制形如 1 后跟若干 0）放入哈希集合；记忆化 DFS 从左往右尝试切出所有「值是 5 的幂」的子串，取最少段数。
// 时间复杂度：O(n^2)，状态共 n 个、每个状态枚举 O(n) 个右端点；空间复杂度：O(n)，记忆数组 f 与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumBeautifulSubstrings(string s) {  // s：只含 '0' 与 '1' 的二进制字符串，返回最少分割段数
        unordered_set<long long> ss;  // 存放所有「美丽数」（5 的幂）；用 long long 防止二进制还原时溢出
        int n = s.size();  // 字符串长度，后面反复用到
        long long x = 1;  // 从 5^0 = 1 开始枚举 5 的幂
        for (int i = 0; i <= n; ++i) {  // 子串最长 n 位，所以最多只需要 n+1 个 5 的幂
            ss.insert(x);  // 把当前 5 的幂加入集合，供 DFS 判断子串是否美丽
            x *= 5;  // 递推下一个 5 的幂
        }  // 预处理结束
        int f[n];  // 记忆数组：f[i] 表示从下标 i 开始切完剩余后缀的最少段数
        memset(f, -1, sizeof(f));  // 全部置为 -1，表示该状态还没有被计算过
        function<int(int)> dfs = [&](int i) {  // 用 std::function 包一层，让 lambda 可以递归调用自己
            if (i >= n) {  // 已经切到字符串末尾，没有字符需要处理
                return 0;  // 剩余后缀需要 0 段
            }  // 边界处理结束
            if (s[i] == '0') {  // 美丽数的二进制首位一定是 1，以 '0' 开头的子串绝不可能是 5 的幂
                return n + 1;  // 返回比任何可能答案都大的哨兵值，表示这条分支不可行
            }  // 剪枝结束
            if (f[i] != -1) {  // 该状态之前已经算过
                return f[i];  // 直接返回记忆化的结果
            }  // 查表结束
            long long x = 0;  // 滚动还原 s[i..j] 的二进制数值，初值为空串的 0
            int ans = n + 1;  // 段数最多为 n 段，用 n+1 表示「暂时无解」
            for (int j = i; j < n; ++j) {  // 枚举当前这一段的右端点 j
                x = x << 1 | (s[j] - '0');  // 左移一位并拼上当前位，得到 s[i..j] 的数值
                if (ss.count(x)) {  // 这一段的值是 5 的幂，即它本身就是美丽子串
                    ans = min(ans, 1 + dfs(j + 1));  // 用 1 段加上切完后缀的最优解来更新答案
                }  // 可行性判断结束
            }  // 右端点枚举结束
            return f[i] = ans;  // 先写入记忆数组再返回，避免重复搜索同一状态
        };  // 递归 lambda 定义结束
        int ans = dfs(0);  // 从下标 0 开始切整个字符串
        return ans > n ? -1 : ans;  // 结果仍大于 n 说明无解，按题目要求返回 -1
    }  // 方法结束
};  // 类定义结束