// 题目：481. 神奇字符串（Magical String）
// 思路：神奇字符串自描述：第 i 个数字本身就是“接下来要连续写几个字符”的长度。用双指针边读长度边交替生成 1/2，直到长度达到 n。
// 时间复杂度：O(n)，每个字符只生成一次；空间复杂度：O(n)，需要保存生成的字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的题解方法
    int magicalString(int n) {  // n 是需要的字符个数，返回前 n 位中 '1' 的个数
        vector<int> s = {1, 2, 2};  // 1 和 2 分别代表字符 '1' 与 '2'；开头固定为 1 2 2
        for (int i = 2; s.size() < n; ++i) {  // i 指向“当前该按第 i 个数字决定生成长度”的位置；长度不足 n 就继续生成
            int pre = s.back();  // pre 是已生成部分的最后一个字符
            int cur = 3 - pre;  // 相邻两段字符必然交替，所以新字符 = 3 - pre（1 变 2，2 变 1）
            for (int j = 0; j < s[i]; ++j) {  // 第 i 个数字 s[i] 表示紧接着要连续写几个 cur
                s.emplace_back(cur);  // 把 cur 追加到字符串尾部
            }  // 结束内层生成
        }  // 结束外层生成
        return count(s.begin(), s.begin() + n, 1);  // 统计前 n 位里有多少个 1
    }  // 结束题解方法
};  // 结束题解类