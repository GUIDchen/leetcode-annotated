// 题目：4036. 字符对转换后字典序最大的字符串 / Lexicographically Largest String After Pair Transformations
// 核心思路：每个数字的二进制位 j 就代表字母 ('a'+j) 能取几次，从字母 z 往 a 依次取出对应个数并抹掉高位
// 复杂度：时间复杂度 O(26 + 输出总长度)，空间复杂度 O(输出总长度)
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    vector<string> largestString(vector<int>& nums) {  // 对每个数字构造字典序最大的字符串，返回结果数组
        vector<string> ans;  // 保存每个数字对应的构造结果
        ans.reserve(nums.size());  // 预留容量，避免反复扩容
        for (int x : nums) {  // 逐个处理数字 x
            string s;  // 当前数字对应的字符串
            for (int j = 25; j >= 0; --j) {  // 从最大字母（索引 25，即 z）向下枚举到 a
                for (int t = x >> j; t > 0; --t) {  // x >> j 表示字母 ('a'+j) 还能取多少个
                    s.push_back('a' + j);  // 追加一个对应字母
                }  // 结束该字母的追加
                x &= (1 << j) - 1;  // 抹掉已使用的高位，只保留更低位供下一轮使用
            }  // 结束字母枚举
            ans.push_back(s);  // 把构造结果加入答案
        }  // 结束数字遍历
        return ans;  // 返回所有构造结果
    }  // 结束方法
};  // 结束类定义
