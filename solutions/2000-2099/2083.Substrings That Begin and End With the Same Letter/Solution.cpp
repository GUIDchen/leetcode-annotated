// 题目：2083. 求以相同字母开头和结尾的子串总数（Substrings That Begin and End With the Same Letter）
// 思路：顺序扫描，统计每个字母已出现次数；当前字符每与之前一个同字母位置配对就多出一个合法子串，累加即可。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只需 26 个计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfSubstrings(string s) {  // s 为小写字母串，返回首尾字母相同的子串总数
        int cnt[26]{};  // cnt[26]：每个字母到目前为止出现的次数，{} 保证零初始化
        long long ans = 0;  // 答案最坏可达 O(n^2)，用 long long 防溢出
        for (char& c : s) {  // 按字符引用遍历字符串，避免拷贝
            ans += ++cnt[c - 'a'];  // 先把该字母计数加一，再累加：它就是能与当前字符配对的左端点个数
        }  // 结束遍历
        return ans;  // 返回子串总数
    }  // 关闭方法
};  // 关闭类
