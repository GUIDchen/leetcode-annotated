// 题目：2138. 将字符串拆分为若干长度为 k 的组（Divide a String Into Groups of Size k）
// 思路：长度不是 k 的整数倍时先用 fill 字符补齐，再从头每 k 个字符切一段。
// 时间复杂度：O(n)，一次补齐 + 一次切分；空间复杂度：O(n)，存放结果数组与补齐后的字符串。
class Solution {  // LeetCode 约定的题解类
public:
    vector<string> divideString(string s, int k, char fill) {  // s：原字符串；k：每组长度；fill：末组不足时使用的填充字符
        int n = s.size();  // 记录原串长度，后面判断余数要用
        if (n % k) {  // 长度不是 k 的整数倍时，最后一段需要补齐
            s += string(k - n % k, fill);  // 追加 (k - n % k) 个 fill，使总长度变成 k 的整数倍
        }
        vector<string> ans;  // 存放切分出来的每一组
        for (int i = 0; i < s.size() / k; ++i) {  // 共 s.size() / k 组，按下标依次切分
            ans.push_back(s.substr(i * k, k));  // 取从 i*k 开始、长度为 k 的子串
        }
        return ans;  // 返回全部切分结果
    }
};  // 题解类结束