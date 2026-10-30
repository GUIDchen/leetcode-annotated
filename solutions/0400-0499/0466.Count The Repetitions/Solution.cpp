// 题目：466. 统计重复个数（Count The Repetitions）
// 思路：预处理 s2 的每个起点在「一个 s1」中能完整匹配多少个 s2、结束时落在 s2 的哪个下标；然后按 n1 份 s1 递推累加，最后除以 n2。
// 时间复杂度：O(n·m + n1)，n = |s2|、m = |s1|；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {  // 求 s1 重复 n1 次中最多包含多少个 s2 重复 n2 次
        int m = s1.size(), n = s2.size();  // m、n 分别为 s1、s2 的长度
        vector<pair<int, int>> d;  // d[i]：从 s2[i] 开始扫一个 s1，能匹配的 s2 个数与结束下标
        for (int i = 0; i < n; ++i) {  // 预处理 s2 的每个起点
            int j = i;  // 当前要匹配的 s2 下标
            int cnt = 0;  // 这一个 s1 内能匹配完成的 s2 个数
            for (int k = 0; k < m; ++k) {  // 顺序扫描一个 s1
                if (s1[k] == s2[j]) {  // 字符相同才推进 s2 的匹配位置
                    if (++j == n) {  // 匹配完一整个 s2
                        ++cnt;  // 完成一个 s2
                        j = 0;  // 下一个字符从 s2 头部重新开始
                    }  // 结束整串判断
                }  // 结束字符匹配判断
            }  // 结束 s1 扫描
            d.emplace_back(cnt, j);  // 记录该起点对应的转移结果
        }  // 结束起点预处理
        int ans = 0;  // 累计 n1 份 s1 中匹配到的 s2 总数
        for (int j = 0; n1; --n1) {  // 依次消耗 n1 份 s1
            ans += d[j].first;  // 累加这一份 s1 完成的 s2 个数
            j = d[j].second;  // 转移到下一个匹配起点
        }  // 结束 n1 循环
        return ans / n2;  // 能拼出多少份 n2 个 s2 即为答案
    }  // 结束 getMaxRepetitions
};  // 结束 Solution 类