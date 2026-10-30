// 题目：2052. 将句子分隔成行的最低成本（Minimum Cost to Separate Sentence Into Rows）
// 思路：按空格切词并求单词长度前缀和；记忆化搜索 dfs(i) 表示从第 i 个单词开始排版的最小代价，本行放 [i, j) 时代价为剩余空格的平方，最后一行不计代价。
// 时间复杂度：O(n^2)，每个起点最多枚举 n 个断行位置；空间复杂度：O(n)，前缀和数组与记忆化数组。
class Solution {  // 题解类
public:  // 对外接口
    int minimumCost(string sentence, int k) {  // sentence 是原句，k 是每行宽度上限
        istringstream iss(sentence);  // 用字符串流按空格切词
        vector<int> s = {0};  // 前缀和：s[i] 表示前 i 个单词的总长度（不含空格）
        string w;  // 存放当前读到的单词
        while (iss >> w) {  // 逐个单词读取，读到末尾自然结束
            s.push_back(s.back() + w.size());  // 累加长度：新前缀和 = 旧前缀和 + 当前单词长度
        }  // 切词结束
        int n = s.size() - 1;  // 单词个数
        int f[n];  // f[i] 记忆化：从第 i 个单词开始排版的最小代价
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示尚未计算
        auto dfs = [&](this auto&& dfs, int i) -> int {  // dfs(i)：从第 i 个单词开始的最小代价；this auto&& 是 C++23 显式对象参数，用来递归自身
            if (s[n] - s[i] + n - i - 1 <= k) {  // 剩余单词全放一行也不超宽，说明这是最后一行
                return 0;  // 最后一行不计代价
            }  // 判断结束
            if (f[i] != -1) {  // 已经计算过
                return f[i];  // 直接用记忆化结果
            }  // 判断结束
            int ans = INT_MAX;  // 用大值初始化，方便取 min
            for (int j = i + 1; j < n && s[j] - s[i] + j - i - 1 <= k; ++j) {  // 枚举下一行首单词 j（本行放 [i, j)），条件保证本行长度不超过 k
                int m = s[j] - s[i] + j - i - 1;  // 本行长度 = 单词长度和 + 词间空格数
                ans = min(ans, dfs(j) + (k - m) * (k - m));  // 本行代价是剩余空格的平方，加上从 j 开始的最优代价
            }  // 本行枚举结束
            return f[i] = ans;  // 记忆化写入并返回
        };  // lambda 定义结束
        return dfs(0);  // 从第 0 个单词开始求解
    }  // 方法结束
};  // 类定义结束
