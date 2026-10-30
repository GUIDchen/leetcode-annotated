// 题目：943. 最短超级串（Find the Shortest Superstring）
// 思路：先预处理任意两词的最大重叠长度 g[i][j]，再用状压 DP 求「已用集合 mask、以 j 结尾」时的最大总重叠量并记录前驱，回溯出顺序后按重叠长度拼接。
// 时间复杂度：O(n²·2ⁿ)，n 为单词个数（另加 O(n³L) 的重叠预处理）；空间复杂度：O(n·2ⁿ)，dp 与父指针数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string shortestSuperstring(vector<string>& words) {  // words 是单词列表，返回包含全部单词的最短超级串
        int n = words.size();  // 单词个数
        vector<vector<int>> g(n, vector<int>(n));  // g[i][j] 表示把单词 j 接在单词 i 后面时，能重叠掉的最大字符数
        for (int i = 0; i < n; ++i) {  // 枚举作为前驱的单词下标 i
            auto a = words[i];  // 取出单词 a（拷贝一份便于反复使用）
            for (int j = 0; j < n; ++j) {  // 枚举作为后继的单词下标 j
                auto b = words[j];  // 取出单词 b
                if (i != j) {  // 同一个单词不和自己计算重叠
                    for (int k = min(a.size(), b.size()); k > 0; --k) {  // 从理论最长重叠长度开始向下试，保证第一次命中的就是最大重叠
                        if (a.substr(a.size() - k) == b.substr(0, k)) {  // 判断 a 的后 k 个字符是否等于 b 的前 k 个字符
                            g[i][j] = k;  // 记录这个最大重叠长度
                            break;  // 长度由大到小枚举，找到即可结束本对单词的搜索
                        }
                    }
                }
            }
        }
        vector<vector<int>> dp(1 << n, vector<int>(n));  // dp[mask][j]：已用单词集合为 mask、且以 j 结尾时能得到的最大重叠总量
        vector<vector<int>> p(1 << n, vector<int>(n, -1));  // p[mask][j]：该最优状态的前一个单词下标，-1 表示没有前驱
        for (int i = 0; i < 1 << n; ++i) {  // 枚举所有子集状态（1 << n 个）
            for (int j = 0; j < n; ++j) {  // 枚举该状态下的最后一个单词 j
                if ((i >> j) & 1) {  // j 不在集合 mask 中时该状态无意义，跳过
                    int pi = i ^ (1 << j);  // 把 j 从集合中去掉，得到前驱状态
                    for (int k = 0; k < n; ++k) {  // 枚举前驱状态下的最后一个单词 k
                        if ((pi >> k) & 1) {  // k 必须属于去掉 j 之后的集合
                            int v = dp[pi][k] + g[k][j];  // 在 k 之后接上 j 所能累积的总重叠量
                            if (v > dp[i][j]) {  // 发现更优的重叠方案
                                dp[i][j] = v;  // 更新该状态的最大重叠量
                                p[i][j] = k;  // 记录前驱，供最后回溯拼接顺序
                            }
                        }
                    }
                }
            }
        }
        int j = 0;  // 用来记录全集中作为结尾的最优单词
        for (int i = 0; i < n; ++i) {  // 遍历所有单词，尝试让它作为最后一词
            if (dp[(1 << n) - 1][i] > dp[(1 << n) - 1][j]) {  // 比较全集状态下以 i 结尾与当前最优 j 结尾的总重叠量
                j = i;  // 记下更优的结尾单词
            }
        }
        vector<int> arr = {j};  // 从最优结尾开始回溯，arr 里先存逆序的访问顺序
        for (int i = (1 << n) - 1; p[i][j] != -1;) {  // 沿父指针一路回溯，直到某个状态没有前驱为止
            int k = i;  // 先暂存当前集合，因为下一步 i 就会被改写
            i ^= (1 << j);  // 从集合中去掉当前结尾单词 j，得到前驱状态
            j = p[k][j];  // 跳到前驱状态的最后一个单词
            arr.push_back(j);  // 把前一个单词加入路径（此时整体是逆序）
        }
        unordered_set<int> vis(arr.begin(), arr.end());  // 记录回溯路径上已经出现过的单词下标
        for (int i = 0; i < n; ++i) {  // 处理可能因为重叠量为 0 而没被纳入路径的孤立单词
            if (!vis.count(i)) {  // 该单词还没出现在路径里
                arr.push_back(i);  // 直接补到路径末尾，后续拼接时不会产生重叠损失
            }
        }
        reverse(arr.begin(), arr.end());  // 翻转成从前往后的真正拼接顺序
        string ans = words[arr[0]];  // 以排列中的第一个单词作为答案的初始串
        for (int i = 1; i < n; ++i) {  // 依次把后面的单词接上
            int k = g[arr[i - 1]][arr[i]];  // 查询相邻两词的重叠长度
            ans += words[arr[i]].substr(k);  // 只追加不重叠的后缀部分，保证串最短
        }
        return ans;  // 返回构造出的最短超级串
    }
};  // 类定义结束