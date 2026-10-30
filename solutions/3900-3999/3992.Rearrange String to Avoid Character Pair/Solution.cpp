// 题目：3992. Rearrange String to Avoid Character Pair（3992. 重新排列字符串以避免字符对）
// 核心思路：双指针把所有的 y 依次交换到字符串前部，于是 y 全部位于所有 x 之前，任意排列都满足题意；交换过程中每个字符只是换了位置，结果仍是原串的排列。
// 复杂度：时间 O(n)，空间 O(1)（原地交换）。
class Solution {  // 定义题解类
public:  // 公开接口
    string rearrangeString(string s, char x, char y) {  // 重排 s，使所有 y 都排在所有 x 之前，返回任意合法排列
        int i = 0;  // i 指向下一个 y 应该被放置的位置
        for (int j = 0; j < s.size(); j++) {  // j 从左到右扫描整个字符串
            if (s[j] == y) {  // 遇到字符 y
                swap(s[i], s[j]);  // 把 y 交换到前部 y 区间的下一个空位
                i++;  // 前部 y 区间扩大一位
            }  // if 分支结束
        }  // 扫描结束
        return s;  // 返回重排后的字符串
    }  // 方法结束
};  // 类定义结束