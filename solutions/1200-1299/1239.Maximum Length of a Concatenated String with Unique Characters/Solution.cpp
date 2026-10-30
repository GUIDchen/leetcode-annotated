// 题目：1239. 串联字符串的最大长度（Maximum Length of a Concatenated String with Unique Characters）
// 思路：用 26 位掩码表示每个字符串的字符集合，维护所有可行拼接组合的掩码列表 s，逐个字符串与无交集的组合合并并更新最大位数。
// 时间复杂度：O(n·2^m)，最坏情况组合数指数级；空间复杂度：O(2^m)，保存所有可行组合的掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxLength(vector<string>& arr) {  // arr 是候选字符串数组，返回拼接后字符互不重复的最大长度
        vector<int> s = {0};  // 可行组合的掩码列表，0 表示空串（每个整数代表一种已选字符集合）
        int ans = 0;  // 记录出现过的最大长度
        for (const string& t : arr) {  // 逐个处理候选字符串
            int x = 0;  // 用位掩码记录当前字符串用到的字符
            for (char c : t) {  // 遍历当前字符串的每个字符
                int b = c - 'a';  // 映射到 0..25 的位下标
                if ((x >> b & 1) == 1) {  // 该字符在本串中已经出现过，说明自身有重复字符
                    x = 0;  // 把 x 置 0 表示这个串作废
                    break;  // 提前跳出内层循环
                }  // if 结束
                x |= 1 << b;  // 把该字符对应的位置 1
            }  // 内层 for 结束
            if (x > 0) {  // x > 0 说明当前串自身没有重复字符，才可以参与拼接
                for (int i = s.size() - 1; i >= 0; --i) {  // 倒序遍历已有组合，避免本轮新增的组合被再次使用
                    int y = s[i];  // 取一个已有组合的掩码
                    if ((x & y) == 0) {  // 两个集合没有公共字符才能拼接
                        s.push_back(x | y);  // 并集掩码作为一个新组合加入列表
                        ans = max(ans, __builtin_popcount(x | y));  // 用并集的比特数（即长度）更新答案
                    }  // if 结束
                }  // for 结束
            }  // if (x > 0) 结束
        }  // 外层 for 结束
        return ans;  // 返回最大长度
    }  // 方法结束
};  // 类定义结束
