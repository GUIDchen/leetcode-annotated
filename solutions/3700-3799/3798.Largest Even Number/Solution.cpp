// 3798. 最大的偶数 / Largest Even Number
// 核心思路：偶数必须以 2 结尾，而字符只有 1 和 2，因此删掉末尾所有 1 后剩下的字符串就是最大的偶数。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 定义 LeetCode 题解类
public:  // 公开接口
    string largestEven(string s) {  // 返回能表示偶数的最大结果字符串
        while (!s.empty() && s.back() == '1') {  // 只有 2 能作偶数结尾，因此不断去掉末尾的 1
            s.pop_back();  // 删除末尾字符
        }  // 结束去除
        return s;  // 剩余部分即为最大偶数
    }  // 结束函数
};  // 结束类
