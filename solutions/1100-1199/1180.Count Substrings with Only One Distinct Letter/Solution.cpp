// 题目：1180. 统计只含单一字母的子串（Count Substrings with Only One Distinct Letter）
// 思路：扫描出每一段连续相同字母，长度为 len 的段内只含单一字母的子串数为 len*(len+1)/2，累加即答案。
// 时间复杂度：O(n)，每个下标只被访问常数次；空间复杂度：O(1)，只用几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countLetters(string s) {  // s 为输入字符串
        int ans = 0;  // ans 累计只含单一字母的子串个数
        for (int i = 0, n = s.size(); i < n;) {  // 按“连续相同字母段”跳跃前进，i 在每轮末尾直接跳到下一段开头
            int j = i;  // j 从段起点出发，寻找当前段的右开边界
            while (j < n && s[j] == s[i]) {  // 向右扩展，直到越界或遇到不同字母
                ++j;  // 右边界后移
            }  // 当前段扩展结束，[i, j) 内全部是同一种字母
            ans += (1 + j - i) * (j - i) / 2;  // 长度 len=j-i 的段贡献 len*(len+1)/2 个子串，用等差求和公式避免逐个枚举
            i = j;  // 跳到下一段开头，段内元素不再重复访问
        }  // 所有段处理完毕
        return ans;  // 返回总数
    }  // 方法体结束
};  // 题解类结束