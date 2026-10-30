// 题目：1209. 删除字符串中的所有相邻重复项 II（Remove All Adjacent Duplicates in String II）
// 思路：用栈把「当前字符 + 连续出现次数」压在一起，计数凑满 k 就立刻出栈，让左右两边重新相邻，从而一次扫描完成消除。
// 时间复杂度：O(n)，每个字符进出栈各一次，最后还原还需 O(n)；空间复杂度：O(n)，栈最坏压入 n 个分段。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeDuplicates(string s, int k) {  // s：输入字符串；k：连续重复多少个就删除；返回消除后的字符串
        vector<pair<char, int>> stk;  // 栈元素为（字符，该字符连续出现次数），栈中任意相邻两项的字符都不相同
        for (char& c : s) {  // 从左到右逐个字符扫描
            if (stk.size() && stk.back().first == c) {  // 栈非空且栈顶字符与当前字符相同，可以并入同一连续段
                stk.back().second = (stk.back().second + 1) % k;  // 计数加一并取模 k：凑满 k 个就归零，等价于把这 k 个字符就地删掉
                if (stk.back().second == 0) {  // 计数归零说明这一段已经凑满 k 个被消除
                    stk.pop_back();  // 弹出该段，使它左右两侧的字符重新相邻，后续可继续合并
                }  // 归零判断结束
            } else {  // 栈为空或栈顶字符不同，无法合并
                stk.push_back({c, 1});  // 新开一个连续段，初始计数为 1
            }  // 两种分支结束
        }  // 扫描结束
        string ans;  // 用于还原最终字符串
        for (auto [c, v] : stk) {  // 遍历栈中剩余的每个连续段
            ans += string(v, c);  // 把该字符重复出现次数拼接到答案里
        }  // 还原循环结束
        return ans;  // 返回消除后的字符串
    }  // removeDuplicates 方法结束
};  // 题解类定义结束