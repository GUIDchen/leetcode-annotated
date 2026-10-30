// 题目：1784. 检查二进制字符串字段（Check if Binary String Has at Most One Segment of Ones）
// 思路：字符串以 1 开头，所以「1 的连续段最多一段」等价于任意位置都不出现 "01" 这种由 0 回到 1 的转折。
// 时间复杂度：O(n)，find 扫描一遍字符串；空间复杂度：O(1)，只做查找不额外分配空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkOnesSegment(string s) {  // s 是首字符为 1 的二进制字符串
        return s.find("01") == -1;  // 找不到 "01" 说明 1 段之后再没有新的 1 段
    }
};