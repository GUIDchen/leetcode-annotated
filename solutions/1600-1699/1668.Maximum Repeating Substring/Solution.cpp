// 题目：1668. 最大重复子字符串（Maximum Repeating Substring）
// 思路：把 word 不断重复拼成 t（共 k 个 word），从 k=1 枚举到 n/m，只要 t 是 sequence 的子串就记录答案。
// 时间复杂度：O(n²/m)，每轮 find 最坏 O(n·k)；空间复杂度：O(n)，拼接串 t 最长约 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxRepeating(string sequence, string word) {  // sequence：主串；word：要重复的子串，返回最大重复次数
        int ans = 0;  // 记录满足条件的最大重复次数
        string t = word;  // t 是 word 重复 k 次的结果，先从 k=1 开始
        int x = sequence.size() / word.size();  // 重复次数最多不超过这个上界（总长度除以单词长度）
        for (int k = 1; k <= x; ++k) {  // 从小到大枚举重复次数 k
            // C++ 这里从小到大枚举重复值
            if (sequence.find(t) != string::npos) {  // t 出现在 sequence 中，说明 k 次重复是可行的
                ans = k;  // 记录当前可行的 k；k 递增，最后留下的就是最大值
            }  // if 分支结束
            t += word;  // 末尾再追加一个 word，为下一轮 k+1 做准备
        }  // for 循环结束
        return ans;  // 返回最大重复次数
    }  // 方法结束
};  // 类定义结束