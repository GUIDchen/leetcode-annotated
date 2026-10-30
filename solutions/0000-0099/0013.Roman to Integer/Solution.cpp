// 题目：13. 罗马数字转整数（Roman to Integer）
// 思路：用哈希表把字符映射成数值；最后一位必取正，其余每位若小于右邻即减法组合则取负，否则取正。
// 时间复杂度：O(n)，n 为字符串长度，一次线性扫描；空间复杂度：O(1)，哈希表只有 7 个固定键。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int romanToInt(string s) {  // s 是合法的罗马数字字符串
        unordered_map<char, int> nums{  // 字符 → 数值的查找表
            {'I', 1},  // I = 1
            {'V', 5},  // V = 5
            {'X', 10},  // X = 10
            {'L', 50},  // L = 50
            {'C', 100},  // C = 100
            {'D', 500},  // D = 500
            {'M', 1000},  // M = 1000
        };
        int ans = nums[s.back()];  // 最右一位不会构成减法组合，直接取正作为基准
        for (int i = 0; i < s.size() - 1; ++i) {  // 扫描到倒数第二位，每次与右邻比较
            int sign = nums[s[i]] < nums[s[i + 1]] ? -1 : 1;  // 小于右邻说明是减法组合，该位取负
            ans += sign * nums[s[i]];  // 按符号把当前位的数值计入答案
        }
        return ans;  // 返回换算出的整数
    }
};
