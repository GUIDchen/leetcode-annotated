// 题目：761. 特殊的二进制字符串（Special Binary String）
// 思路：递归拆出所有平衡的「1...0」子串，其内部部分递归求最大字典序后再包回 1/0，最后把子串降序拼接。
// 时间复杂度：O(n^2 log n)，每层递归 O(n) 且需排序；空间复杂度：O(n^2)，递归栈与子串存储。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string makeLargestSpecial(string s) {  // s：只含 '0' 与 '1' 的特殊二进制字符串
        if (s == "") {  // 空串是递归出口
            return s;  // 直接返回空串
        }
        vector<string> ans;  // 收集当前层拆出的每一个特殊子串
        int cnt = 0;  // 平衡计数：'1' 记 +1、'0' 记 -1，归零处即为子串边界
        for (int i = 0, j = 0; i < s.size(); ++i) {  // i 是扫描指针，j 记录当前子串起点
            cnt += s[i] == '1' ? 1 : -1;  // 根据当前字符更新平衡计数
            if (cnt == 0) {  // 计数归零，说明 s[j..i] 是一段平衡特殊串
                ans.push_back("1" + makeLargestSpecial(s.substr(j + 1, i - j - 1)) + "0");  // 剥掉外层 1/0，递归求内部最大串，再包回来
                j = i + 1;  // 起点移到下一段子串
            }
        }
        sort(ans.begin(), ans.end(), greater<string>{});  // 子串按字典序降序排列，使拼接结果最大
        return accumulate(ans.begin(), ans.end(), ""s);  // 从左到右拼接全部子串
    }
};  // 类定义结束（源文件末尾无换行）