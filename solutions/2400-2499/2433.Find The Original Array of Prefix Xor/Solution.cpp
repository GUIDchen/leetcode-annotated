// 题目：2433. 找出前缀异或的原始数组（Find The Original Array of Prefix Xor）
// 思路：由 pref[i] = pref[i-1] ^ arr[i] 两边同异或 pref[i-1]，得 arr[i] = pref[i-1] ^ pref[i]；arr[0] 就等于 pref[0]。
// 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(n)，用于存放返回的答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findArray(vector<int>& pref) {  // pref：题目给出的前缀异或数组
        int n = pref.size();  // 数组长度，也就是答案长度
        vector<int> ans = {pref[0]};  // 首元素：arr[0] 就等于 pref[0]，用它给答案数组开个头
        for (int i = 1; i < n; ++i) {  // 从第二个元素开始逐个还原
            ans.push_back(pref[i - 1] ^ pref[i]);  // 异或的自反性：相邻前缀异或相消，剩下 arr[i]
        }
        return ans;  // 返回还原出来的原始数组
    }
};