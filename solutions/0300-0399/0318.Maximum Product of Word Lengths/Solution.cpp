// 题目：318. 最大单词长度乘积（Maximum Product of Word Lengths）
// 思路：把每个单词压成 26 位掩码，两个掩码按位与为 0 说明没有公共字母，此时用长度乘积更新答案。
// 时间复杂度：O(L + n^2)，L 为所有单词的字符总数；空间复杂度：O(n)，只额外保存每个单词的掩码。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxProduct(vector<string>& words) {  // words：待选单词列表；返回合法单词对的最大长度乘积
        int n = words.size();  // 单词个数，后面的循环与掩码数组都要用到
        int mask[n];  // 每个单词对应一个 26 位掩码，第 b 位为 1 表示含字母 'a'+b
        memset(mask, 0, sizeof(mask));  // 掩码全部清零，避免在随机初值上做按位或
        int ans = 0;  // 记录最大长度乘积，初始 0 表示还没有合法单词对
        for (int i = 0; i < n; ++i) {  // 枚举第一个单词的下标 i
            for (char& c : words[i]) {  // 按引用遍历第 i 个单词的每个字符，省去字符拷贝
                mask[i] |= 1 << (c - 'a');  // 把字符 c 对应的那一位设为 1，得到该单词的字母集合
            }  // 单词内字符遍历结束
            for (int j = 0; j < i; ++j) {  // 再枚举 i 之前的单词，每对只比较一次
                if ((mask[i] & mask[j]) == 0) {  // 掩码按位与为 0：两个单词没有任何公共字母
                    ans = max(ans, (int) (words[i].size() * words[j].size()));  // 合法配对，用两边长度的乘积去更新最大值
                }  // 配对判断结束
            }  // 下标 j 的枚举结束
        }  // 下标 i 的枚举结束
        return ans;  // 返回最大乘积；没有合法单词对时就是 0
    }  // 方法结束
};  // 类定义结束