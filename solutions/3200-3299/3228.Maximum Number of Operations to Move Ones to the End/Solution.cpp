// 题目：3228. 将 1 移动到末尾的最大操作次数（Maximum Number of Operations to Move Ones to the End）
// 思路：一次扫描统计已扫过的 1 的个数 cnt；每遇到一段连续 0 的开头，这 cnt 个 1 各能与这段 0 交换一次，把 cnt 累加进答案。
// 时间复杂度：O(n)，只遍历字符串一次；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxOperations(string s) {  // s：只含 '0' 和 '1' 的字符串；返回最大操作次数
        int ans = 0, cnt = 0;  // ans：累计操作次数；cnt：当前已经扫过的 1 的个数
        int n = s.size();  // 先取出长度，避免循环中重复调用 size()
        for (int i = 0; i < n; ++i) {  // 从左到右逐字符扫描
            if (s[i] == '1') {  // 遇到字符 1，就把 1 的计数加一
                ++cnt;  // 这个 1 之后每遇到一段 0，都能与它交换一次
            } else if (i && s[i - 1] == '1') {  // 遇到一段连续 0 的开头（前一个字符是 1）
                ans += cnt;  // 这段 0 左边的 cnt 个 1 各能跨过它一次，累加进答案
            }  // 单次判断结束
        }  // 循环结束
        return ans;  // 返回最大操作次数
    }  // 方法结束
};  // 类定义结束