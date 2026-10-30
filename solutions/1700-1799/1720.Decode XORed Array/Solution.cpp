// 题目：1720. 解码异或后的数组（Decode XORed Array）难度：简单
// 思路：已知 encoded[i] = arr[i] ^ arr[i+1] 且 arr[0] = first，利用异或的自反性（a ^ b ^ b = a），
// 从前往后逐个推出 arr[i+1] = arr[i] ^ encoded[i]，把结果依次追加到答案数组即可。
// 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，除返回值外只需常数级额外空间（答案数组本身）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> decode(vector<int>& encoded, int first) {  // encoded：相邻元素的异或值；first：arr[0]
        vector<int> ans = {{first}};  // 答案数组以已知的 arr[0] = first 起始
        for (int x : encoded) {  // 按顺序取出每个异或值
            ans.push_back(ans.back() ^ x);  // 由 a ^ b = c 推出 arr[i+1] = arr[i] ^ encoded[i]
        }
        return ans;  // 返回完整的解码数组
    }  // decode 方法结束
};  // Solution 类结束