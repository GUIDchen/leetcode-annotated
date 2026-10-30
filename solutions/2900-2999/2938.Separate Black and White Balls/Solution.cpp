// 题目：2938. 区分黑球与白球（Separate Black and White Balls）
// 思路：目标是把所有 1 挪到右边；从右往左数第 cnt 个 1 应落到位置 n-cnt，需要交换 (n-cnt)-i 次。
// 时间复杂度：O(n)，从右到左一次扫描；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumSteps(string s) {  // s：由 '0'（白球）与 '1'（黑球）组成的字符串
        long long ans = 0;  // ans：累计的交换次数，可能达到 O(n^2)，必须用 long long
        int cnt = 0;  // cnt：已经扫描过的 1 的个数，也就是右侧已经就位的黑球数量
        int n = s.size();  // n：字符串长度
        for (int i = n - 1; i >= 0; --i) {  // 从右往左扫描，因为最右边的 1 应当留在最右边
            if (s[i] == '1') {  // 当前位置是黑球，需要把它往右挪
                ++cnt;  // 这是从右往左数的第 cnt 个 1
                ans += n - i - cnt;  // 它最终应落在下标 n-cnt，与当前位置 i 的距离就是交换次数
            }  // 黑球分支结束
        }  // 反向扫描结束
        return ans;  // 返回最少交换次数
    }  // 方法结束
};  // 类定义结束