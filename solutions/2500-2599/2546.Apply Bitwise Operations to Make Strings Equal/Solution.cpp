// 题目：2546. 执行逐位运算使字符串相等（Apply Bitwise Operations to Make Strings Equal）
// 思路：两个串都含 1 时可以互相变换，都不含 1 时本来就相等；所以只需比较「是否含 1」。
// 时间复杂度：O(n)，两次 count 扫描；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool makeStringsEqual(string s, string target) {  // 判断 s 能否通过逐位运算变成 target
        auto a = count(s.begin(), s.end(), '1') > 0;  // a 表示 s 中是否存在字符 '1'
        auto b = count(target.begin(), target.end(), '1') > 0;  // b 表示 target 中是否存在字符 '1'
        return a == b;  // 两边都含 1 或都不含 1 才可转换，否则无解
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，保持原样）