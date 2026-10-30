// 题目：2729. 判断一个数是否迷人（Check if The Number is Fascinating）
// 思路：把 n、2n、3n 拼成一个字符串后排序，判断是否恰好等于 "123456789"。
// 时间复杂度：O(log n)（拼接长度固定为 9，排序是常数级）；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isFascinating(int n) {  // 判断 n 是否为迷人数字
        string s = to_string(n) + to_string(n * 2) + to_string(n * 3);  // 把 n、2n、3n 依次转成字符串并拼接
        sort(s.begin(), s.end());  // 排序后方便直接与 1~9 的升序串比较
        return s == "123456789";  // 恰好由 1~9 每个数字各出现一次组成才是迷人数字
    }
};