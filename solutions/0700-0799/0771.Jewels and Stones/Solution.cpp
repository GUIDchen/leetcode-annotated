// 题目：771. 宝石与石头（Jewels and Stones）
// 核心思路：用长度为 128 的桶数组标记哪些字符属于宝石，再统计 stones 中落在桶里的字符个数。
// 时间复杂度 O(|jewels| + |stones|)；空间复杂度 O(1)（字符集大小固定为 128）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对判题器可见
    int numJewelsInStones(string jewels, string stones) {  // jewels：宝石类型；stones：拥有的石头；返回其中宝石的个数
        int s[128] = {0};  // 桶数组：下标为字符 ASCII 码，值 1 表示是宝石；{0} 把数组全部清零
        for (char c : jewels) {  // 范围 for 遍历 jewels 中的每个字符
            s[c] = 1;  // 标记该字符为宝石
        }  // for 循环结束
        int ans = 0;  // ans 统计宝石个数
        for (char c : stones) {  // 范围 for 遍历 stones 中的每个字符
            ans += s[c];  // 是宝石时桶里为 1，答案加一；否则加 0
        }  // for 循环结束
        return ans;  // 返回宝石数量
    }  // 方法结束
};  // 类定义结束
