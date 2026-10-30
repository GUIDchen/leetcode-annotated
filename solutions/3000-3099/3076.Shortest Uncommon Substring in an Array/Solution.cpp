// 题目：3076. 数组中的最短非公共子字符串（Shortest Uncommon Substring in an Array）
// 思路：对每个字符串按子串长度从小到大、同长度按字典序枚举全部子串，逐个检查它是否出现在别的字符串中，第一个合法的就是答案。
// 时间复杂度：O(n^2 * L^3)，n 为字符串个数、L 为最大长度（枚举子串并对每个子串做包含判断）；空间复杂度：O(n * L)，答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> shortestSubstrings(vector<string>& arr) {  // arr：输入的非空字符串数组；返回每个位置的最短非公共子字符串
        int n = arr.size();  // 字符串个数
        vector<string> ans(n);  // 答案数组，长度与输入一致，默认空串表示不存在合法子串
        for (int i = 0; i < n; ++i) {  // 逐个字符串独立求解
            int m = arr[i].size();  // 当前字符串长度
            for (int j = 1; j <= m && ans[i].empty(); ++j) {  // 按子串长度 j 从小到大枚举；一旦已有答案就停下，保证取到最短
                for (int l = 0; l <= m - j; ++l) {  // 枚举长度为 j 的子串的起始下标 l
                    string sub = arr[i].substr(l, j);  // 取出当前要检验的子串
                    if (ans[i].empty() || sub < ans[i]) {  // 答案为空，或者新子串字典序更小（同长度时取字典序最小），才值得替换
                        bool ok = true;  // 先假设该子串没有出现在别的字符串中
                        for (int k = 0; k < n && ok; ++k) {  // 遍历其余字符串做检查；ok 一旦为假就没必要继续
                            if (k != i && arr[k].find(sub) != string::npos) {  // 在别的字符串里找到了 sub，说明它不是非公共子串
                                ok = false;  // 标记为不合法
                            }
                        }
                        if (ok) {  // 全部其他字符串都不包含它，说明这个子串合法
                            ans[i] = sub;  // 记录为当前最优答案（长度最小且字典序最小）
                        }
                    }
                }
            }
        }
        return ans;  // 返回全部字符串的答案
    }
};