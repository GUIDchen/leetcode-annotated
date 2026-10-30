// 题目：2390. 从字符串中移除星号（Removing Stars From a String）
// 思路：把结果字符串当作栈；遇普通字符入栈，遇 '*' 弹出栈顶，等价于删除它左边最近的未被删除字符。
// 时间复杂度：O(n)，每个字符最多进出一次；空间复杂度：O(n)，结果字符串最多存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeStars(string s) {  // s：只含小写字母和 '*' 的字符串
        string ans;  // 用 string 充当栈，存放已保留的字符
        for (char c : s) {  // 从左到右扫描每个字符
            if (c == '*') {  // 星号：删除左边最近的未被删除字符
                ans.pop_back();  // 栈顶就是那个字符，直接弹出（题目保证不会弹空）
            } else {  // 普通字母：保留它
                ans.push_back(c);  // 压入栈顶
            }  // 分支结束
        }  // 扫描结束
        return ans;  // 栈内剩余字符按原顺序拼接即为答案
    }  // 方法结束
};