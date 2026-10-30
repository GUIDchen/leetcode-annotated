// 题目：2269. 找到一个数字的 K 美丽值（Find the K-Beauty of a Number）
// 思路：把 num 转成字符串，枚举所有长度为 k 的子串，转回整数后判断它是否非零且整除 num，统计个数。
// 时间复杂度：O(d·k)，d 为数字位数、每段子串转换与取模为 O(k)；空间复杂度：O(d)，字符串副本。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int divisorSubstrings(int num, int k) {  // num：原数字；k：子串长度；返回 K 美丽值的个数
        int ans = 0;  // 合法子串计数
        string s = to_string(num);  // 转成字符串，方便按下标截取固定长度的子串
        for (int i = 0; i < s.size() - k + 1; ++i) {  // 枚举每个长度为 k 的子串的左端点，右端点不越界
            int t = stoi(s.substr(i, k));  // 截取长度 k 的子串并转成整数
            ans += t && num % t == 0;  // 子串非零（短路避免除零）且能整除 num 时，计数加一
        }  // 枚举结束
        return ans;  // 返回美丽值个数
    }  // 解题方法结束
};  // 题解类结束