// 题目：17. 电话号码的字母组合（Letter Combinations of a Phone Number）
// 思路：逐位做字符串的笛卡尔积，ans 保存所有已拼接的前缀，每处理一位就把每个前缀与每个候选字母组合成新串。
// 时间复杂度：O(4^n · n)，每个组合长度为 n，分支因子最多 4；空间复杂度：O(4^n · n)，用于存放全部结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> letterCombinations(string digits) {  // digits 是数字串
        if (digits.empty()) {  // 空输入
            return {};  // 直接返回空列表，避免返回一个空串
        }
        vector<string> d = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};  // 下标 0..7 对应数字 2..9
        vector<string> ans = {""};  // 初始只有一个空前缀，作为笛卡尔积的单位元
        for (auto& i : digits) {  // 逐位处理数字
            string s = d[i - '2'];  // 取出该数字对应的候选字母，'2' 映射到下标 0
            vector<string> t;  // 存放这一层扩展出的新组合
            for (auto& a : ans) {  // 遍历上一层每个前缀
                for (auto& b : s) {  // 遍历本位的每个候选字母
                    t.push_back(a + b);  // 前缀接上字母，形成一个新组合
                }
            }
            ans = move(t);  // 用新一层替换旧一层，move 避免整体拷贝
        }
        return ans;  // 返回所有字母组合
    }
};
