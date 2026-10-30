// 题目：2515. 到目标字符串的最短距离（Shortest Distance to Target String in a Circular Array）
// 思路：枚举所有等于 target 的下标，环形数组上两点距离为 min(|i-start|, n-|i-start|)，在所有候选中取最小。
// 时间复杂度：O(n)，一遍扫描；空间复杂度：O(1)，只用常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int closestTarget(vector<string>& words, string target, int startIndex) {  // words 为环形字符串数组，target 是目标串，startIndex 是起点
        int n = words.size();  // 环形数组长度
        int ans = n;  // 初值取最大可能距离 n，同时作为「未找到」的哨兵
        for (int i = 0; i < n; i++) {  // 遍历每个位置
            if (words[i] == target) {  // 找到与目标串相等的位置
                int t = abs(i - startIndex);  // 两个下标差的绝对值
                ans = min({ans, t, n - t});  // 取「原答案、正向距离、反向绕行距离」三者的最小值
            }
        }
        return ans == n ? -1 : ans;  // ans 未被更新过说明目标串不存在，返回 -1；否则返回最短距离
    }
};
