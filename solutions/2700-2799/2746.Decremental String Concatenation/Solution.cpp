// 题目：2746. 字符串连接删减字母（Decremental String Concatenation）
// 思路：记忆化搜索，状态为 (待处理单词下标 i, 当前拼接串首字母 a, 尾字母 b)，每次把单词接在左边或右边并减去 1 个重叠字符。
// 时间复杂度：O(n * 26 * 26)，每个状态只算一次；空间复杂度：O(n * 26 * 26)，记忆化表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 公有成员：判题器直接调用下面的方法
    int minimizeConcatenatedLength(vector<string>& words) {  // words：需要依次拼接的单词数组；返回拼接后字符串的最小长度
        int n = words.size();  // n：单词个数，同时是递归的终止边界
        int f[n][26][26];  // f[i][a][b]：从第 i 个单词开始、当前串首字母为 a、尾字母为 b 时的最小总长；0 表示尚未计算
        memset(f, 0, sizeof(f));  // 记忆化数组全部清零，用 0 当作“未访问”标记
        function<int(int, int, int)> dfs = [&](int i, int a, int b) {  // 递归 lambda：i 是待处理的单词下标，a/b 是当前拼接串的首/尾字母（0..25）
            if (i >= n) {  // 递归出口：所有单词都处理完毕
                return 0;  // 没有单词可拼，追加长度为 0
            }  // 结束递归出口分支
            if (f[i][a][b]) {  // 该状态已经算过（值非 0）
                return f[i][a][b];  // 直接返回记忆化结果，避免重复搜索
            }  // 结束查表分支
            auto s = words[i];  // 取出当前单词
            int m = s.size();  // 当前单词长度，接上去恰好增加 m 个字符
            int x = dfs(i + 1, a, s[m - 1] - 'a') - (s[0] - 'a' == b);  // 方案一：把 s 接在当前串右边；若 s 首字母等于当前串尾字母 b，则重叠 1 个字符可省掉
            int y = dfs(i + 1, s[0] - 'a', b) - (s[m - 1] - 'a' == a);  // 方案二：把 s 接在当前串左边；若 s 尾字母等于当前串首字母 a，则重叠 1 个字符可省掉
            return f[i][a][b] = m + min(x, y);  // 两种接法取较小值，加上 s 的长度 m，写入记忆化表并返回
        };  // 结束递归 lambda 的定义
        return words[0].size() + dfs(1, words[0].front() - 'a', words[0].back() - 'a');  // 第一个单词的长度无法避免，固定加上；再从第 1 个单词、以其首尾字母为状态继续拼
    }  // 结束题解方法
};  // 结束题解类
