// 题目：1119. 删去字符串中的元音（Remove Vowels from a String）
// 思路：一次遍历，把不是 a/e/i/o/u 的字符按原顺序追加到结果串，相对次序自然保持不变。
// 时间复杂度：O(n)，每个字符只判断一次；空间复杂度：O(n)，结果串最多与原串等长。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeVowels(string s) {  // 返回删除全部元音后的新字符串
        string ans;  // 结果串：按原顺序累积保留下来的字符
        for (char& c : s) {  // 用引用遍历，避免逐个字符拷贝
            if (!(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) {  // 只要不是 a/e/i/o/u 之一就保留（题目只含小写字母）
                ans += c;  // 把非元音字符追加到结果末尾
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回累积好的结果
    }  // 方法结束
};  // 类定义结束